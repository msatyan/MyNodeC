#include "addon_api.h"
# include <assert.h>

int ObjAddVal_utf8(napi_env env, napi_value obj, const char *key, const char *val)
{
    napi_status status;
    napi_value nv;

	if ((status = napi_create_string_utf8(env, val, NAPI_AUTO_LENGTH, &nv)) == napi_ok)
	{
		status = napi_set_named_property(env, obj, key, nv);
		if ( status != napi_ok)
		{
			return( -1 );
		}
	}
	else
	{
		return(-2);
	}

    return(0);
}

int ObjAddVal_Int32( napi_env env, napi_value obj, const char *key, int val )
{
    napi_status status;
    napi_value nv;

	if ( (status = napi_create_int32( env, val, &nv) ) == napi_ok)
	{
		status = napi_set_named_property(env, obj, key, nv );
		if ( status != napi_ok)
		{
			return( -1 );
		}
	}
	else
	{
		return(-2);
	}

    return(0);
}


int ObjAddVal_double( napi_env env, napi_value obj, const char *key, double val )
{
    napi_status status;
    napi_value nv;

	if ( (status = napi_create_double( env, val, &nv) ) == napi_ok)
	{
		status = napi_set_named_property(env, obj, key, nv );
		if ( status != napi_ok)
		{
			return( -1 );
		}
	}
	else
	{
		return(-2);
	}

    return(0);
}


void MyPrintValueType2( napi_valuetype valuetype, char *name )
{
	if (valuetype == napi_undefined)
	{
		printf( "\n %s: is of type napi_undefined", name);
	} else if (valuetype == napi_null)
	{
		printf( "\n %s: is of type napi_null", name);
	} else if (valuetype == napi_boolean)
	{
		printf( "\n %s: is of type napi_boolean", name);
	} else if (valuetype == napi_number)
	{
		printf( "\n %s: is of type napi_number", name);
	} else if (valuetype == napi_string)
	{
		printf( "\n %s: is of type napi_string", name);
	} else if (valuetype == napi_symbol)
	{
		printf( "\n %s: is of type napi_symbol", name);
	} else if (valuetype == napi_object)
	{
		printf( "\n %s: is of type napi_object", name);
	} else if (valuetype == napi_function)
	{
		printf( "\n %s: is of type napi_function", name);
	} else if (valuetype == napi_external)
	{
		printf( "\n %s: is of type napi_external", name);
	} else
	{
		printf( "\n %s: is of type %d ? (I don't know this enum type yet, is it new type ?)",
		 name, valuetype);
	}
}

void MyPrintValueType( napi_env env, napi_value val, char *name )
{
	napi_status status;
	napi_valuetype valuetype;

	if ( name == NULL)
		name = "";

	status = napi_typeof(env, val, &valuetype);
	assert(status == napi_ok);
	MyPrintValueType2( valuetype, name );
}
