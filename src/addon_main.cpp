// napi_status napi_create_function(napi_env env,
//                                  const char* utf8name,
//                                  size_t length,
//                                  napi_callback cb,
//                                  void* data,
//                                  napi_value* result);
// [in] env: The environment that the API is invoked under.
// [in] utf8Name: The name of the function encoded as UTF8. This is visible within JavaScript as the new function object's name property.
// [in] length: The length of the utf8name in bytes, or NAPI_AUTO_LENGTH if it is null-terminated.
// [in] cb: The native function which should be called when this function object is invoked.
// [in] data: User-provided data context. This will be passed back into the function when invoked later.
// [out] result: napi_value representing the JavaScript function object for the newly created function.
// Returns napi_ok if the API succeeded.


// napi_status napi_set_named_property(napi_env env,
//                                     napi_value object,
//                                     const char* utf8Name,
//                                     napi_value value);
// [in] env: The environment that the N-API call is invoked under.
// [in] object: The object on which to set the property.
// [in] utf8Name: The name of the property to set.
// [in] value: The property value.
// Returns napi_ok if the API succeeded.

// This method is equivalent to calling napi_set_property with a
// napi_value created from the string passed in as utf8Name.


#include "addon_api.h"
#include "addon_api_4cpp.h"

napi_value Init(napi_env env, napi_value exports)
{
	napi_status status;
	napi_value fn;

	// MyC_SayHello -> sayHello
	if ((status = napi_create_function(env, "sayHello", NAPI_AUTO_LENGTH, MyC_SayHello, NULL, &fn)) != napi_ok)
		return NULL;
	if ((status = napi_set_named_property(env, exports, "sayHello", fn)) != napi_ok)
		return NULL;


	// MyC_GetValueFromC -> GetValueFromC
	if ((status = napi_create_function(env, "GetValueFromC", NAPI_AUTO_LENGTH, MyC_GetValueFromC, NULL, &fn)) != napi_ok)
		return NULL;
	if ((status = napi_set_named_property(env, exports, "GetValueFromC", fn)) != napi_ok)
		return NULL;


	// MyC_Print -> CPrint
	if ((status = napi_create_function(env, "CPrint", NAPI_AUTO_LENGTH, MyC_Print, NULL, &fn)) != napi_ok)
		return NULL;
	if ((status = napi_set_named_property(env, exports, "CPrint", fn)) != napi_ok)
		return NULL;

	// SpeedTest_CPrimeCount -> CPrimeCount
	if ((status = napi_create_function(env, "SpeedTest_CPrimeCount", NAPI_AUTO_LENGTH, SpeedTest_CPrimeCount, NULL, &fn)) != napi_ok)
		return NULL;
	if ((status = napi_set_named_property(env, exports, "SpeedTest_CPrimeCount", fn)) != napi_ok)
		return NULL;

	// CreateJsonObject -> MyC_CreateJsonObject
	if ((status = napi_create_function(env, "CreateJsonObject", NAPI_AUTO_LENGTH, MyC_CreateJsonObject, NULL, &fn)) != napi_ok)
		return NULL;
	if ((status = napi_set_named_property(env, exports, "CreateJsonObject", fn)) != napi_ok)
		return NULL;

	// MyPromise1SpeedTest -> MyPromise1
	if ((status = napi_create_function(env, "MyPromise1SpeedTest", NAPI_AUTO_LENGTH, MyPromise1, NULL, &fn)) != napi_ok)
		return NULL;
	if ((status = napi_set_named_property(env, exports, "MyPromise1SpeedTest", fn)) != napi_ok)
		return NULL;

	// MyCallback1 -> CMyCallback1
	if ((status = napi_create_function(env, "MyCallback1", NAPI_AUTO_LENGTH, CMyCallback1, NULL, &fn)) != napi_ok)
		return NULL;
	if ((status = napi_set_named_property(env, exports, "MyCallback1", fn)) != napi_ok)
		return NULL;

	// MyCallback2 -> CMyCallback2
	if ((status = napi_create_function(env, "MyCallback2", NAPI_AUTO_LENGTH, CMyCallback2, NULL, &fn)) != napi_ok)
		return NULL;
	if ((status = napi_set_named_property(env, exports, "MyCallback2", fn)) != napi_ok)
		return NULL;

	MyObject::Init(env, exports);

	// FOR node-addon-api
	AllCppInit( env, exports );

	return exports;
}

// NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
NAPI_MODULE( mync1, Init )


