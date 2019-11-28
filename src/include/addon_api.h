
#ifndef _ADDON_API_
#define _ADDON_API_

#include <node_api.h>
#include <stdio.h>
#include "MyNativeObj.h"

typedef struct
{
  napi_async_work work;
  napi_threadsafe_function tsfn;
} AddonData;

void addon_getting_unloaded(napi_env env, void *data, void *hint);

napi_value MyC_SayHello(napi_env env, napi_callback_info info);
napi_value MyC_GetValueFromC (napi_env env, napi_callback_info info);
napi_value MyC_Print (napi_env env, napi_callback_info info);
napi_value CMyPrintJSObject (napi_env env, napi_callback_info info);
napi_value CppMyPrintJSObject (napi_env env, napi_callback_info info);
napi_value SpeedTest_CPrimeCount (napi_env env, napi_callback_info info);
napi_value CMyCreateJSObject(napi_env env, const napi_callback_info info);
napi_value MyPromise1(napi_env env, napi_callback_info info);
napi_value CMyCallback1(napi_env env, const napi_callback_info info);
napi_value CMyCallback2(napi_env env, const napi_callback_info info);
napi_value CArrayBuffSum(napi_env env, napi_callback_info info);
napi_value CArrayBuffer_GetMultiplicationTable(napi_env env, napi_callback_info info);
napi_value CInt32TypedArray_GetMultiplicationTable(napi_env env, napi_callback_info info);


///////////////////////
napi_value Init_ThreadSafeAsyncStream(napi_env env, napi_value exports);

#endif  // _ADDON_API_



