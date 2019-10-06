
#include "MyEventEmit.h"
#include <node_api.h>

napi_value MyNodeAddonApiInitSession1( napi_env c_env, napi_value c_exports)
{
  // Create a C++ wrapper objects to be used with node-addon-api
  Napi::Env    env     = Napi::Env(c_env);
  Napi::Object exports = Napi::Object(c_env, c_exports);

  exports.Set(Napi::String::New(env, "callEmit"), Napi::Function::New(env, CallEmit));

  return c_exports;
}

