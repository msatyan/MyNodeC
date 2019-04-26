#include <node_api.h>
#include <assert.h>

#include "cpp_util.h"
#include <stdio.h>
#include "extutil.h"
napi_value CMycallEmit(napi_env env, const napi_callback_info info)
{
  napi_status status;

  size_t argc = 1;
  napi_value args[1];
  status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
  assert(status == napi_ok);

  // The only  parameter passed to the function is 
  napi_value emit = args[0];

  napi_value result;
  //status = napi_get_property_names(env, emit, &result);
  //assert(status == napi_ok);


  status = napi_get_named_property(env, emit, "sensor1", &result);
  assert(status == napi_ok);


  MyPrintType( env, emit, "emit" );

  //napi_valuetype xtype;
  //napi_typeof(env, emit, &xtype );
  // Check for the correct calling of the function.
  //if (xtype == napi_function)
  //{
	 // printf("\n napi_typeof value is %d", xtype);
  //}


  


//   napi_value aParams2cbJsFunc[1];
//   status = napi_create_string_utf8(env, "Hello World from CMyCallback1", NAPI_AUTO_LENGTH, aParams2cbJsFunc);
//   assert(status == napi_ok);

//   napi_value global;
//   status = napi_get_global(env, &global);
//   assert(status == napi_ok);

//   napi_value result;
//   // Invoke JS callback function
//   status = napi_call_function(env, global, cbJsFunc, 1, aParams2cbJsFunc, &result);
//   assert(status == napi_ok);

  return nullptr;
}


