#include <assert.h>
#include "addon_api.h"
#include "stdio.h"

napi_value CArrayBuffSum(napi_env env, napi_callback_info info)
{
    napi_status status;
    const size_t MaxArgExpected = 1;
    napi_value args[MaxArgExpected];
    size_t argc = sizeof(args) / sizeof(napi_value);

    status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    assert(status == napi_ok);
    if (argc < 1)
        napi_throw_error(env, "EINVAL", "Too few arguments");

    napi_value buff = args[0];
    napi_valuetype valuetype;
    status = napi_typeof(env, buff, &valuetype);
    assert(status == napi_ok);

    if (valuetype == napi_object)
    {
        bool isArrayBuff = 0;
        status = napi_is_arraybuffer(env, buff, &isArrayBuff);
        assert(status == napi_ok);

        if (isArrayBuff != true)
            napi_throw_error(env, "EINVAL", "Expected an ArrayBuffer");
    }

    int32_t *buff_data = NULL;
    size_t byte_length = 0;
    int32_t sum = 0;

    napi_get_arraybuffer_info(env, buff, (void **)&buff_data, &byte_length);
    assert(status == napi_ok);

    printf("\nC:  Int32Array size = %d,  (ie: bytes=%d)",
           (int)(byte_length / sizeof(int32_t)), (int)byte_length);
    for (int i = 0; i < byte_length / sizeof(int32_t); ++i)
    {
        sum += *(buff_data + i);
        printf("\nC:  i32array[%d] = %d", i, *(buff_data + i));
    }

    napi_value rcValue;
    napi_create_int32(env, sum, &rcValue);

    // ArrayBuff share the same memory buffer at native and JS
    // To verify this let us change the value here and access it at JS
    for (int i = 0; i < byte_length / sizeof(int32_t); ++i)
    {
        *(buff_data + i)  = i * 10;
    }

    return (rcValue);
}