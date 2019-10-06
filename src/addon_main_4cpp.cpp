
#include "MyEventEmit.h"
#include <node_api.h>

napi_value AllCppInit( napi_env c_env, napi_value c_exports)
{
  Napi::Env    env     = Napi::Env::Env(c_env);
  Napi::Object exports = Napi::Object::Object	(	c_env, c_exports );

  exports.Set(Napi::String::New(env, "callEmit"), Napi::Function::New(env, CallEmit));

  // The exports
  return c_exports;
}

