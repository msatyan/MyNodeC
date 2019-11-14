
# include <assert.h>
#include <napi.h>
#include "extutil.h"


// Receive a JsonObject parameter from JavaScript, and interpret it at C
napi_value CMyPrintJSObject(napi_env env, napi_callback_info info)
{
	napi_status status;
	// Specifies the size of the argv array and receives the actual count of arguments
	const size_t ArgvArraySize = 2;
	size_t argc = ArgvArraySize; // IN & Out
	napi_value argv[ArgvArraySize];
	napi_value jsthis;
    napi_value arg1;
	int dbg_flag = 0;

	// napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	status = napi_get_cb_info(env, info, &argc, argv, &jsthis, nullptr);
	if (argc < 1)
	{
		napi_throw_error(env, "EINVAL", "Too few arguments");
		goto Exit;
	}

	arg1 = argv[0];
	if (argc > 1) {
		bool cVal;

		status =  napi_get_value_bool( env, argv[1], &cVal);
		assert(status == napi_ok);
		dbg_flag = cVal;
	}

	if ( dbg_flag )
	{
		printf( "\n ================================");
		printf( "\n argc = %d", (int)argc);
	}


	{
		napi_valuetype valuetype;
		status = napi_typeof(env, arg1, &valuetype);
		if ( valuetype == napi_object && isArrayType( env, arg1 ) == 0)
		{
			if ( dbg_flag )
			{
				printf( "\n arg1: is of type napi_object");
				printf( "\n ================================ \n");
			}

			// This is an object
			MyPrintObj( env, arg1, 0, dbg_flag);
		}
	}

	Exit:
	printf( "\n");
	return (NULL);
}



// Receive a JsonObject parameter from JavaScript, and interpret it at C
napi_value CppMyPrintJSObject(napi_env env, napi_callback_info info)
{
	napi_status status;
	// Specifies the size of the argv array and receives the actual count of arguments
	const size_t ArgvArraySize = 2;
	size_t argc = ArgvArraySize; // IN & Out
	napi_value argv[ArgvArraySize];
    // char buff[1024];
    napi_value arg1;

	status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
	if (argc < 1)
	{
		napi_throw_error(env, "EINVAL", "Too few arguments");
		// goto Exit;
	}

	printf( "\n");
	printf( "\n argc = %d", (int)argc);

    arg1 = argv[0];

    // The C++ wraper usage for getting all properties
	Napi::Object obj = Napi::Object( env, arg1 );
    Napi::Array arg1_Properties = obj.GetPropertyNames();

    uint32_t ArrayLen=(int)arg1_Properties.Length();
	printf( "\n The arg1 has %d properties", ArrayLen);

    for( int i=0; i<(int)ArrayLen; ++i)
    {
        Napi::Value PropertyName = arg1_Properties.Get(i);
        std::string s = PropertyName.ToString().Utf8Value();
         printf( "\n %d   %s:", 1+i, s.c_str() );
    }

	// Exit:
	printf( "\n");
	return (NULL);
}


