#include <node_api.h>
#include <assert.h>

#include "cpp_util.h"

napi_value CMyCallback1(napi_env env, const napi_callback_info info)
{
  napi_status status;

  size_t argc = 1;
  napi_value args[1];
  status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
  assert(status == napi_ok);

  // The first parameter is a JS callback function
  napi_value cbJsFunc = args[0];

  napi_value aParams2cbJsFunc[1];
  status = napi_create_string_utf8(env, "Hello World from CMyCallback1", NAPI_AUTO_LENGTH, aParams2cbJsFunc);
  assert(status == napi_ok);

  napi_value global;
  status = napi_get_global(env, &global);
  assert(status == napi_ok);

  napi_value result;
  // Invoke JS callback function
  status = napi_call_function(env, global, cbJsFunc, 1, aParams2cbJsFunc, &result);
  assert(status == napi_ok);

  return nullptr;
}


// This function takes three arguments, x, y, and a JS function for callback
napi_value CMyCallback2(napi_env env, const napi_callback_info info)
{
	int32_t x = 0;
	int32_t y = 0;

	napi_status status;
	napi_value argv[3];
	// [in-out] argc: Specifies the size of  argv array and receives the actual count of arguments
	size_t argc = 3;

	status =  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if ( status != napi_ok || argc != 3  )
	{
		napi_throw_error(env, "EINVAL", "arguments missmatch");
		return NULL;
	}

	status = napi_get_value_int32(env, argv[0], &x);
  assert(status == napi_ok);

	status = napi_get_value_int32(env, argv[1], &y);
	assert(status == napi_ok);

  // The third argument to this function is JS callback function
  napi_value cbJsFunc = argv[2];

  // Calculate the PrimeCount
  int PrimeCount = CPrimeCount( x,  y);

  const int NumParams2Jsf = 2;
  napi_value aParams2cbJsFunc[NumParams2Jsf];

  ///////// Create parameter for the callback JS function /////////
  // Param1: String type
  status = napi_create_string_utf8(env, "Hello World from CMyCallback2", NAPI_AUTO_LENGTH, &aParams2cbJsFunc[0]);
  assert(status == napi_ok);

  //Param2: int32 type
	status = napi_create_int32(env, PrimeCount, &aParams2cbJsFunc[1]);
  assert(status == napi_ok);

  napi_value global;
  status = napi_get_global( env, &global );
  assert(status == napi_ok);

  napi_value return_val;

  // See also
  // napi_async_execute_callback
  // napi_async_complete_callback
  // Invoke JS callback function
  status = napi_call_function( env, global, cbJsFunc, NumParams2Jsf, aParams2cbJsFunc, &return_val );
  assert(status == napi_ok);

  return nullptr;
}

