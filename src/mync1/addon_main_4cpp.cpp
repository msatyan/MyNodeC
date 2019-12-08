
#include "MyEventEmit.h"
#include <node_api.h>

napi_value Init_MyNodeAddonApiSession1( napi_env c_env, napi_value c_exports)
{
  // Create a C++ wrapper objects to be used with node-addon-api
  Napi::Env    env     = Napi::Env(c_env);
  Napi::Object exports = Napi::Object(c_env, c_exports);

  exports.Set(Napi::String::New(env, "CallEmit1"), Napi::Function::New(env, CCallEmit1));

  return c_exports;
}

