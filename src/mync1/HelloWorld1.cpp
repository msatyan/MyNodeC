

# include <assert.h>
#include "addon_api.h"
#include "extutil.h"

// Call a C Function from JavaScript
napi_value MyC_SayHello(napi_env env, napi_callback_info info)
{
	printf("Hello!!! from C Function\n");

	return (NULL);
}

// C function sending a value to JavaScript
napi_value MyC_GetValueFromC(napi_env env, napi_callback_info info)
{
	napi_status status;
	napi_value rcValue;

	const char *str = "C2JS: Hi JavaScript !!!";

	if ((status = napi_create_string_utf8(env, str, NAPI_AUTO_LENGTH, &rcValue)) != napi_ok)
	{
		napi_throw_error(env, "OUT", "Failed to set value-1");
		return(NULL);
	}

	return (rcValue);
}

// Receive a parameter from JavaScript
napi_value MyC_Print(napi_env env, napi_callback_info info)
{
	// Specifies the size of the argv array and receives the actual count of arguments
	const size_t ArgvArraySize = 1;
	size_t argc = ArgvArraySize; // IN & Out
	napi_value argv[ArgvArraySize];
	char buff[1024];
	size_t buff_len = 0;

	napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	if (argc < 1)
	{
		napi_throw_error(env, "EINVAL", "Too few arguments");
		return NULL;
	}

	if (napi_get_value_string_utf8(env, argv[0], (char *)&buff, sizeof(buff) - 2, &buff_len) != napi_ok)
	{
		napi_throw_error(env, "EINVAL", "Expected string");
		return NULL;
	}
	buff[sizeof(buff) - 1] = '\0';
	printf("%s (printed by C function)\n", buff);

	return (NULL);
}


napi_value CMyCreateJSObject(napi_env env, const napi_callback_info info)
{
	// Specifies the size of the argv array and receives the actual count of arguments
	const size_t ArgvArraySize = 1;
	size_t argc = ArgvArraySize; // IN & Out
	napi_value argv[ArgvArraySize];
	napi_status status;
	napi_value string;
	napi_value obj;
	int rc=0;

	status = napi_get_cb_info( env, info, &argc, argv, NULL, NULL );
	assert(status == napi_ok);

	// Create the obj to be returned to JS
	status = napi_create_object( env, &obj );
	assert(status == napi_ok);

	// Let us assume we also want to process an optional parameter from JS too
	if ( argc < 1 )
	{
		// The JS function has not passed any argument,
		// Then let us set a default value for this property.
		rc = ObjAddVal_utf8( env, obj, "name", "Default name set by the C function");
		PROCESS_ERR_ObjAddKV( env, rc );
	}
	else
	{
		string = argv[0]; // The first argument of the JS function.
		status = napi_set_named_property( env, obj, "name", string);
		assert(status == napi_ok);
	}

	rc = ObjAddVal_utf8( env, obj, "Hello", "World!");
	PROCESS_ERR_ObjAddKV( env, rc );

	rc = ObjAddVal_Int32(env, obj, "age", 21 );
	PROCESS_ERR_ObjAddKV(env, rc);

	rc = ObjAddVal_double(env, obj, "salary", 135.89 );
	PROCESS_ERR_ObjAddKV(env, rc);


	rc = ObjAddVal_utf8( env, obj, "email", "user@demo.com");
	PROCESS_ERR_ObjAddKV( env, rc );

	rc = ObjAddVal_utf8( env, obj, "description", "N-API is Awesome !!!");
	PROCESS_ERR_ObjAddKV( env, rc );


	return (obj);
}


// TODO:
////// Simple Asynchronous Operations /////
// napi_create_async_work
// napi_delete_async_work
// napi_queue_async_work
// napi_cancel_async_work

////// Custom Asynchronous Operations /////
// napi_async_init
// napi_async_destroy
// napi_make_callback
// napi_open_callback_scope
// napi_close_callback_scope

/////// N-API Callback types /////
// napi_callback_info
// napi_callback
// napi_finalize
// napi_async_execute_callback
// napi_async_complete_callback
// napi_threadsafe_function_call_js

// Promises
// napi_create_promise
// napi_resolve_deferred
// napi_reject_deferred
// napi_is_promise

// Script execution
// napi_run_script
