#ifndef MY_NATIVE_OBJ_H
#define MY_NATIVE_OBJ_H

#include <node_api.h>

class MyNativeObj
{
public:
  static napi_value Init(napi_env env, napi_value exports);
  static void Destructor(napi_env env, void *nativeObject, void *finalize_hint);

private:
  explicit MyNativeObj(double value_ = 0);
  ~MyNativeObj();

  static napi_value New(napi_env env, napi_callback_info info);
  static napi_value GetValue(napi_env env, napi_callback_info info);
  static napi_value SetValue(napi_env env, napi_callback_info info);
  static napi_value PlusOne(napi_env env, napi_callback_info info);
  static napi_value Multiply(napi_env env, napi_callback_info info);
  static napi_ref constructor;
  double value_;
  napi_env env_;
  napi_ref wrapper_;
};

#endif // MY_NATIVE_OBJ_H
