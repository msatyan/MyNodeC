#include "addon_api.h"
#include "cpp_util.h"


//////////////////////////////////////////////////////////////
// Receive parameters from JavaScript and return a Value to JavaScript
// We can use this for SPEED TEST between Node and C
// Find the number of prime numbers between X and Y
napi_value SpeedTest_CPrimeCount(napi_env env, napi_callback_info info)
{
	napi_status status;
	napi_value argv[2];

	// [in-out] argc: Specifies the size of the provided argv array and
	// receives the actual count of arguments
	size_t argc = 2;
	int32_t x = 0;
	int32_t y = 0;

	int32_t PrimeCount = 0;
	napi_value rcValue;

	napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (argc != 2)
	{
		napi_throw_error(env, "EINVAL", "arguments missmatch");
		return NULL;
	}

	if ((status = napi_get_value_int32(env, argv[0], &x)) != napi_ok)
	{
		napi_throw_error(env, "EINVAL", "parm 1: int32 expected");
		return NULL;
	}

	if ((status = napi_get_value_int32(env, argv[1], &y)) != napi_ok)
	{
		napi_throw_error(env, "EINVAL", "parm 2: int32 expected");
		return NULL;
	}

	// Calculate number of prims between x and y
	PrimeCount = CPrimeCount(x, y);

	if ((status = napi_create_int32(env, PrimeCount, &rcValue)) != napi_ok)
	{
		napi_throw_error(env, "OUT", "Failed to set value-1");
		return(NULL);
	}

	// printf(" [%d] ", PrimeCount);
	return (rcValue);
}



