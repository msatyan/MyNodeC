
#include <node_api.h>
#include <assert.h>
#include "addon_api.h"
#include <stdlib.h>
#include <stdio.h>
#include <thread>

#define NUM_OBJECTS_TO_REPORT 4

#define BIRD "Bird"
#define CAT "Cat"
#define DOG "Dog"
#define CAR "Car"
#define BICYCLE "Bicycle"

typedef enum
{
  bird = 0,
  cat,
  dog,
  car,
  bicycle
} SearchObjects;

typedef struct
{
  int frame;
  SearchObjects obj;
} ObjectFindInfo;

void VideoSearchFindNext(ObjectFindInfo *obj)
{
  static int frame = 0;

  obj->obj = static_cast<SearchObjects>(rand() % NUM_OBJECTS_TO_REPORT);
  frame += rand() % 1000;
  obj->frame = frame;
  // Provide some delay to simulate work
  std::this_thread::sleep_for(std::chrono::milliseconds(150));
}

const char *GetObjName(SearchObjects obj)
{
  const char *cp = "unknown";
  switch (obj)
  {
  case bird:
    cp = BIRD;
    break;

  case cat:
    cp = CAT;
    break;

  case dog:
    cp = DOG;
    break;

  case car:
    cp = CAR;
    break;

  case bicycle:
    cp = BICYCLE;
    break;
  }
  return (cp);
}

// This function is responsible for converting data coming in from the worker
// thread to napi_value items that can be passed into JavaScript, and for
// calling the JavaScript function.
static void CThreadSafeFun4CallingJS(napi_env env, napi_value js_cb, void *context, void *data)
{
  // This parameter is not used.
  (void)context;

  // Retrieve the prime from the item created by the worker thread.
  ObjectFindInfo *pObjList = (ObjectFindInfo *)data;

  // env and js_cb may both be NULL if Node.js is in its cleanup phase, and
  // items are left over from earlier thread-safe calls from the worker thread.
  // When env is NULL, we simply skip over the call into Javascript and free the
  // items.
  if (env != NULL)
  {
    napi_value undefined;
    napi_value js_result_array;

    assert(napi_create_array_with_length(env,
        NUM_OBJECTS_TO_REPORT, &js_result_array) == napi_ok);

    for (int i = 0; i < NUM_OBJECTS_TO_REPORT; ++i)
    {
      napi_value js_obj;
      napi_value val_obj;
      napi_value val_frame;
      const char *obj_name = GetObjName((pObjList + i)->obj);
      napi_create_object(env, &js_obj);
      assert(napi_create_string_utf8(env, obj_name, NAPI_AUTO_LENGTH, &val_obj) == napi_ok);
      assert(napi_create_int32(env, (pObjList + i)->frame, &val_frame) == napi_ok);

      assert(napi_set_named_property(env, js_obj, "obj", val_obj) == napi_ok);
      assert(napi_set_named_property(env, js_obj, "f", val_frame) == napi_ok);

      // Add the object to the array
      assert(napi_set_element(env, js_result_array, i, js_obj) == napi_ok);
    }

    // Retrieve the JavaScript `undefined` value so we can use it as the `this`
    // value of the JavaScript function call.
    assert(napi_get_undefined(env, &undefined) == napi_ok);

    // Call the JavaScript function and pass it the prime that the secondary
    // thread found.
    assert(napi_call_function(env,
                              undefined,
                              js_cb,
                              1,
                              &js_result_array,
                              NULL) == napi_ok);
  }

  // Free the item created by the worker thread.
  free(data);
}

// This function runs on a worker thread. It has no access to the JavaScript
// environment except through the thread-safe function.
static void ExecuteWork(napi_env env, void *data)
{
  AddonData *addon_data = (AddonData *)data;
  // int idx_inner, idx_outer;

  // We bracket the use of the thread-safe function by this thread by a call to
  // napi_acquire_threadsafe_function() here, and by a call to
  // napi_release_threadsafe_function() immediately prior to thread exit.
  assert(napi_acquire_threadsafe_function(addon_data->tsfn_StreamSearch) == napi_ok);

  int MaxNumReport = 6;
  for (int rCout = 0; rCout < MaxNumReport; ++rCout)
  {
    int num_obj = NUM_OBJECTS_TO_REPORT;

    // This memory will be free after processing of the C callback
    ObjectFindInfo *pObjList = (ObjectFindInfo *)malloc(num_obj * sizeof(ObjectFindInfo));

    for (int i = 0; i < num_obj; ++i)
    {
      VideoSearchFindNext(pObjList + i);
    }
    assert(napi_call_threadsafe_function(addon_data->tsfn_StreamSearch, pObjList,
                                         napi_tsfn_blocking) == napi_ok);
  }

  // Indicate that this thread will make no further use of the thread-safe function.
  assert(napi_release_threadsafe_function(addon_data->tsfn_StreamSearch,
                                          napi_tsfn_release) == napi_ok);
}

// This function runs on the main thread after `ExecuteWork` exits.
static void WorkComplete(napi_env env, napi_status status, void *data)
{
  AddonData *addon_data = (AddonData *)data;

  // Clean up the thread-safe function and the work item associated with this
  assert(napi_release_threadsafe_function(addon_data->tsfn_StreamSearch,
                                          napi_tsfn_release) == napi_ok);
  assert(napi_delete_async_work(env, addon_data->work_StreamSearch) == napi_ok);

  // Set both values to NULL so JavaScript can order a new run of the thread.
  addon_data->work_StreamSearch = NULL;
  addon_data->tsfn_StreamSearch = NULL;
}

// Create a thread-safe function and an async queue work item. We pass the
// thread-safe function to the async queue work item so the latter might have a
// chance to call into JavaScript from the worker thread on which the
// ExecuteWork callback runs.
napi_value CAsyncStreamSearch(napi_env env, napi_callback_info info)
{
  const size_t MaxArgExpected = 2;
  napi_value args[MaxArgExpected];
  size_t argc = sizeof(args) / sizeof(napi_value);

  int32_t MaxSearchTime = 0;
  napi_value js_cb;

  napi_value work_name;
  AddonData *addon_data;

  // Retrieve the JavaScript callback we should call with items generated by the
  // worker thread, and the per-addon data.
  assert(napi_get_cb_info(env,
                          info,
                          &argc,
                          args,
                          NULL,
                          (void **)(&addon_data)) == napi_ok);
  if (argc != 2)
  {
    napi_throw_error(env, "EINVAL", "AsyncStreamSearch: Argument count mismatch");
  }

  // Process the parameters
  // First argument is time it need to search, in sec
  assert(napi_get_value_int32(env, args[0], &MaxSearchTime) == napi_ok);
  js_cb = args[1]; // Second param, the JS callback function

  // Ensure that no work is currently in progress.
  assert(addon_data->work_StreamSearch == NULL && "Only one StreamSearch work item must exist at a time");

  // Create a string to describe this asynchronous operation.
  assert(napi_create_string_utf8(env,
                                 "N-API Thread-safe Call from AsyncStreamSearch Work Item",
                                 NAPI_AUTO_LENGTH,
                                 &work_name) == napi_ok);

  // Convert the callback retrieved from JavaScript into a thread-safe function
  // which we can call from a worker thread.
  assert(napi_create_threadsafe_function(env,
                                         js_cb,
                                         NULL,
                                         work_name,
                                         0,
                                         1,
                                         NULL,
                                         NULL,
                                         NULL,
                                         CThreadSafeFun4CallingJS,
                                         // The asynchronous thread-safe JavaScript function
                                         &(addon_data->tsfn_StreamSearch)) == napi_ok);

  // Create an async work item, passing in the addon data, which will give the
  // worker thread access to the above-created thread-safe function.
  assert(napi_create_async_work(env,
                                NULL,
                                work_name,
                                ExecuteWork,
                                WorkComplete,
                                addon_data,
                                &(addon_data->work_StreamSearch)) == napi_ok);

  // Queue the work item for execution.
  assert(napi_queue_async_work(env, addon_data->work_StreamSearch) == napi_ok);

  // This causes `undefined` to be returned to JavaScript.
  return NULL;
}

napi_value Init_AsyncStreamSearch(napi_env env, napi_value exports)
{
  // Define addon-level data associated with this instance of the addon.
  AddonData *addon_data = (AddonData *)malloc(sizeof(*addon_data));
  addon_data->work_StreamSearch = NULL;

  // Define the properties that will be set on exports.
  napi_property_descriptor start_work = {
      "AsyncStreamSearch",
      NULL,
      CAsyncStreamSearch,
      NULL,
      NULL,
      NULL,
      napi_default,
      addon_data};

  // Decorate exports with the above-defined properties.
  assert(napi_define_properties(env, exports, 1, &start_work) == napi_ok);

  // Associate the addon data with the exports object, to make sure that when
  // the addon gets unloaded our data gets freed.
  assert(napi_wrap(env,
                   exports,
                   addon_data,
                   addon_getting_unloaded,
                   NULL,
                   NULL) == napi_ok);

  // Return the decorated exports object.
  return exports;
}
