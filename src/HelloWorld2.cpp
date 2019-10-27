
# include <assert.h>
#include <napi.h>
#include "extutil.h"


// Receive a JsonObject parameter from JavaScript, and interpret it at C
napi_value MyC_PrintJsonObject(napi_env env, napi_callback_info info)
{
	napi_status status;
	// Specifies the size of the argv array and receives the actual count of arguments
	const size_t ArgvArraySize = 2;
	size_t argc = ArgvArraySize; // IN & Out
	napi_value argv[ArgvArraySize];
	size_t buff_len = 0;
	napi_value jsthis;
    char buff[1024];
    napi_value arg1;

	// napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
	status = napi_get_cb_info(env, info, &argc, argv, &jsthis, nullptr);
	if (argc < 1)
	{
		napi_throw_error(env, "EINVAL", "Too few arguments");
		goto Exit;
	}

	printf( "\n");
	printf( "\n argc = %d", (int)argc);


    arg1 = argv[0];
	MyPrintValueType(env, arg1, "arg1");


    // The C++ wraper usage for getting all properties
	// Napi::Object obj = Napi::Object( env, arg1 );
    // Napi::Array arr = obj.GetPropertyNames();

    napi_value AllProperties;
    status = napi_get_property_names( env, arg1, &AllProperties);
    assert(status == napi_ok);

    MyPrintValueType(env, AllProperties, "AllProperties");

    // The API can be used to iterate over result using napi_get_array_length and napi_get_element.
    uint32_t ArrayLen=0;
    status = napi_get_array_length( env, AllProperties, &ArrayLen);
    assert(status == napi_ok);
    printf( "\n ArrayLen = %d", ArrayLen);

    for( int i=0; i<(int)ArrayLen; ++i)
    {
        napi_value PropertyName;
        napi_get_element( env, AllProperties, i, &PropertyName);

        if (napi_get_value_string_utf8(env, PropertyName, (char *)&buff, sizeof(buff) - 2, &buff_len) != napi_ok)
        {
            napi_throw_error(env, "EINVAL", "Expected string");
            break;
        }
        buff[sizeof(buff) - 1] = '\0';
	    printf("\n %s", buff);
        // MyPrintValueType(env, PropertyName, buff);

    }

	Exit:
	printf( "\n");
	return (NULL);
}





// Receive a JsonObject parameter from JavaScript, and interpret it at C
napi_value MyCpp_PrintJsonObject(napi_env env, napi_callback_info info)
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
	MyPrintValueType(env, arg1, "arg1");

    // The C++ wraper usage for getting all properties
	Napi::Object obj = Napi::Object( env, arg1 );
    Napi::Array AllProperties = obj.GetPropertyNames();

    uint32_t ArrayLen=(int)AllProperties.Length();
    printf( "\n ArrayLen = %d",  ArrayLen);

    for( int i=0; i<(int)ArrayLen; ++i)
    {
        Napi::Value PropertyName = AllProperties.Get(i);
        std::string s = PropertyName.ToString().Utf8Value();
         printf( "\n %s", s.c_str() );
    }

	// Exit:
	printf( "\n");
	return (NULL);
}

