
#ifndef _ADDON_API_
#define _ADDON_API_

#include <node_api.h>
#include <stdio.h>
#include "MyNativeObj.h"

napi_value MyC_SayHello(napi_env env, napi_callback_info info);
napi_value MyC_GetValueFromC (napi_env env, napi_callback_info info);
napi_value MyC_Print (napi_env env, napi_callback_info info);
napi_value MyC_PrintJsonObject (napi_env env, napi_callback_info info);
napi_value MyCpp_PrintJsonObject (napi_env env, napi_callback_info info);
napi_value SpeedTest_CPrimeCount (napi_env env, napi_callback_info info);
napi_value MyC_CreateJsonObject(napi_env env, const napi_callback_info info);
napi_value MyPromise1(napi_env env, napi_callback_info info);
napi_value CMyCallback1(napi_env env, const napi_callback_info info);
napi_value CMyCallback2(napi_env env, const napi_callback_info info);

#endif  // _ADDON_API_



