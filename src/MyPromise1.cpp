// napi_create_promise()
// napi_resolve_deferred()
// napi_reject_deferred()
// napi_create_async_work();
// napi_queue_async_work();
// napi_delete_async_work()

#include <node_api.h>
#include <stdlib.h>
#include <stdio.h>
#include "cpp_util.h"


// A data structure to exchange information during async operation
typedef struct
{
    int32_t x;
	int32_t y;
    int32_t PrimeCount;

    int asynchronous_action_status;
    napi_deferred deferred;
    napi_async_work work;
} prom_data_ex_t;



// Execute the asynchronous work.
void ExecuteMyPromise1(napi_env env, void *data)
{
    prom_data_ex_t *promDataEx = (prom_data_ex_t *)data;

    // Calculate prime count
    promDataEx->PrimeCount = CPrimeCount( promDataEx->x, promDataEx->y );

    // Set the status as asynchronous_action is success
    promDataEx->asynchronous_action_status = 0;
    //sleep(3);
}

// Handle the completion of the asynchronous work.
void CompleteMyPromise1(napi_env env, napi_status status, void *data)
{
    napi_value rcValue;

    prom_data_ex_t *promDataEx = (prom_data_ex_t *)data;

	napi_create_int32(env, promDataEx->PrimeCount, &rcValue);

    // Resolve or reject the promise associated with the deferred depending on
    // whether the asynchronous action succeeded.
    if ( promDataEx->asynchronous_action_status == 0) // Success
    {
        status = napi_resolve_deferred(env, promDataEx->deferred, rcValue);
    }
    else
    {
        napi_value undefined;

        status = napi_get_undefined(env, &undefined);
        status = napi_reject_deferred(env, promDataEx->deferred, undefined );
    }
    if (status != napi_ok)
    {
        napi_throw_error(env, NULL, "Unable to create promise result.");
    }

    napi_delete_async_work(env, promDataEx->work);
    free(promDataEx);
}



// The function called by javascript to get a promise returned.
napi_value MyPromise1(napi_env env, napi_callback_info info)
{
    napi_value promise;
	napi_status status;
	napi_value argv[2];

	// [in-out] argc: Specifies the size of  argv array and receives the actual count of arguments
	size_t argc = 2;
	status =  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if ( status != napi_ok || argc != 2  )
	{
		napi_throw_error(env, "EINVAL", "arguments missmatch or Unable to get javacript data");
		return NULL;
	}

    // Allocate storage space for passing informaiton to the Async operation
    prom_data_ex_t *promDataEx = (prom_data_ex_t *)malloc(sizeof(prom_data_ex_t));
	if (promDataEx == NULL)
	{
		napi_throw_error(env, NULL, "Memory allocation error");
		return NULL;
	}

    promDataEx->asynchronous_action_status = 1;


	if ((status = napi_get_value_int32(env, argv[0], &promDataEx->x)) != napi_ok)
	{
		napi_throw_error(env, "EINVAL", "parm 1: int32 expected");
		return NULL;
	}

	if ((status = napi_get_value_int32(env, argv[1], &promDataEx->y)) != napi_ok)
	{
		napi_throw_error(env, "EINVAL", "parm 2: int32 expected");
		return NULL;
	}

    // Create a promise object.
    status = napi_create_promise(env, &promDataEx->deferred, &promise);
    if (status != napi_ok)
    {
        napi_throw_error(env, NULL, "Unable to create promise.");
    }

    napi_valuetype x_type;
    napi_valuetype y_type;

    napi_typeof(env, argv[0], &x_type );
    napi_typeof(env, argv[1], &y_type );
    // Check for the correct calling of the function.
    if ( x_type != napi_number   ||   y_type != napi_number )
    {
        // Reject the promise (at least one of the param is not a number)
        napi_value str;
        napi_create_string_utf8(env, "Promise rejected: Argument not a number.", NAPI_AUTO_LENGTH, &str);
        napi_reject_deferred(env, promDataEx->deferred, str);
        free(promDataEx);
    }
    else
    {
        // Create the async function.
        napi_value resource_name;
        napi_create_string_utf8(env, "MyPromise1", -1, &resource_name);
        napi_create_async_work(env, NULL, resource_name, ExecuteMyPromise1, CompleteMyPromise1, promDataEx, &promDataEx->work);
        napi_queue_async_work(env, promDataEx->work);
    }

    return promise;
}


