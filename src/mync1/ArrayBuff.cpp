#include <assert.h>
#include "addon_api.h"
#include "cpp_util.h"
#include "stdio.h"
#include "stdlib.h"

void FreeExternalArrayBufferMemory(napi_env env, void* data, void* hint)
{
    // externally-owned data is ready to be cleaned up
    // the object with which it was associated with, has been garbage-collected
    printf("C-Free : AB External Memory Address: %p\n", data);
    free(data);
}


// Receive an ArrayBuffer from JavaScript
// Print the values of ArrayBuffer and then modify value at native layer.
// Then JavaScript print the modified value
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




/////////////////////////////////////////////////////////////////////////
// Create ArrayBuffer at native layer and return it to JavaScript
// It take two parameters 's' and 'm' and return an array buffer.
// s is the size of the int32 array
// m multiplication factor against the index value.
napi_value CArrayBuffer_GetMultiplicationTable(napi_env env, napi_callback_info info)
{
	napi_status status;
	napi_value argv[2];

	// [in-out] argc: Specifies the size of the provided argv array and
	// receives the actual count of arguments
	size_t argc = 2;
	int32_t s = 0;
	int32_t m = 0;

	napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (argc != 2)
	{
		napi_throw_error(env, "EINVAL", "arguments missmatch");
		return NULL;
	}

    // First parm is size of the array
	if ((status = napi_get_value_int32(env, argv[0], &s)) != napi_ok)
	{
		napi_throw_error(env, "EINVAL", "parm 1: int32 expected");
		return NULL;
	}

    // Second parameter multiplication factor.
	if ((status = napi_get_value_int32(env, argv[1], &m)) != napi_ok)
	{
		napi_throw_error(env, "EINVAL", "parm 2: int32 expected");
		return NULL;
	}

	napi_value rcValue;
    int32_t *buff_data = NULL;
    // Create an array buffer
    status = napi_create_arraybuffer(env, (s * sizeof(int32_t)), (void **)&buff_data, &rcValue);
    assert(status == napi_ok);
    for( int i=0; i<s; ++i )
    {
        *(buff_data + i)  = i * m;
    }

	return (rcValue);
}



/////////////////////////////////////////////////////////////////////////
// Create TypedArray of Int32 at native layer and return it to JavaScript
// It take two parameters 's' and 'm' and return an array buffer.
// s is the size of the int32 array
// m multiplication factor against the index value.
napi_value CInt32TypedArray_GetMultiplicationTable(napi_env env, napi_callback_info info)
{
	napi_status status;
	napi_value argv[2];

	// [in-out] argc: Specifies the size of the provided argv array and
	// receives the actual count of arguments
	size_t argc = 2;
	int32_t s = 0;
	int32_t m = 0;

	napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (argc != 2)
	{
		napi_throw_error(env, "EINVAL", "arguments missmatch");
		return NULL;
	}

    // First parm is size of the array
	if ((status = napi_get_value_int32(env, argv[0], &s)) != napi_ok)
	{
		napi_throw_error(env, "EINVAL", "parm 1: int32 expected");
		return NULL;
	}

    // Second parameter multiplication factor.
	if ((status = napi_get_value_int32(env, argv[1], &m)) != napi_ok)
	{
		napi_throw_error(env, "EINVAL", "parm 2: int32 expected");
		return NULL;
	}

	napi_value rcValue;
    napi_value napi_arraybuffer;
    int32_t *buff_data = NULL;
    // Create an array buffer
    status = napi_create_arraybuffer(env, (s * sizeof(int32_t)), (void **)&buff_data, &napi_arraybuffer);
    assert(status == napi_ok);

    // Create a TypedArray by consuming the original Array Buffer.
    size_t byte_offset = 0; // Let it be from the starting of the original array with full length
    status = napi_create_typedarray( env, napi_int32_array, (size_t)s, napi_arraybuffer, byte_offset, &rcValue);
    assert(status == napi_ok);
    for( int i=0; i<s; ++i )
    {
        *(buff_data + i)  = i * m;
    }

	return (rcValue);
}


/////////////////////////////////////////////////////////////////////////
// Create ArrayBuffer at native layer with externally allocated memory and return it to JavaScript
// This function expects two parameters 's' and 'm' and return an array buffer.
// s is the size of the int32 array
// m multiplication factor against the index value.
napi_value CArrayBufferExternalMem_GetMultiplicationTable(napi_env env, napi_callback_info info)
{
	napi_status status;
	napi_value argv[2];

	// [in-out] argc: Specifies the size of the provided argv array and
	// receives the actual count of arguments
	size_t argc = 2;
	int32_t s = 0;
	int32_t m = 0;

	napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (argc != 2)
	{
		napi_throw_error(env, "EINVAL", "arguments missmatch");
		return NULL;
	}

    // First parm is size of the array
	if ((status = napi_get_value_int32(env, argv[0], &s)) != napi_ok)
	{
		napi_throw_error(env, "EINVAL", "parm 1: int32 expected");
		return NULL;
	}

    // Second parameter multiplication factor.
	if ((status = napi_get_value_int32(env, argv[1], &m)) != napi_ok)
	{
		napi_throw_error(env, "EINVAL", "parm 2: int32 expected");
		return NULL;
	}

    size_t byte_length = sizeof(int32_t)*s;
    int32_t *external_data = (int32_t *) malloc( byte_length );
    printf("C-Alloc: AB External Memory Address: %p\n", (void*)external_data);

	napi_value rcValue;
    // Create array buffer with externally allocated memory.
    // When the item is GCed, it will call FreeExternalArrayBufferMemory
    status = napi_create_external_arraybuffer( env, (void *)external_data, byte_length,
                FreeExternalArrayBufferMemory, NULL, &rcValue);

    assert(status == napi_ok);
    for( int i=0; i<s; ++i )
    {
        *(external_data + i)  = i * m;
    }

	return (rcValue);
}

