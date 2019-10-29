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

bool isArrayType( napi_env env, napi_value val)
{
	napi_status status;
	bool isArray=0;

	// Check whether the object is an array
	status = napi_is_array( env, val, &isArray);
	assert(status == napi_ok);

	return( isArray );
}

napi_valuetype MyPrintValueType( napi_env env, napi_value val, char *name )
{
	napi_status status;
	napi_valuetype valuetype;

	if ( name == NULL)
		name = "";

	status = napi_typeof(env, val, &valuetype);
	assert(status == napi_ok);

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
		bool isArray = isArrayType( env, val );
		if ( isArray )
			printf( "\n %s: is an ARRAY: (type is napi_object)", name);
		else
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


	return( valuetype );
}



void MyPrintValue( napi_env env, napi_value val, int level)
{
	napi_status status;
	napi_valuetype valuetype;

	++level;

	status = napi_typeof(env, val, &valuetype);
	assert(status == napi_ok);

	if (valuetype == napi_undefined)
	{
		printf( "\nUNDEFINED");
	} else if (valuetype == napi_null)
	{
		printf( "\nNULL");
	} else if (valuetype == napi_boolean)
	{
		bool cVal;
		status =  napi_get_value_bool( env, val, &cVal);
		assert(status == napi_ok);
		printf( "\n%s", (cVal ? "true": "false") );

	} else if (valuetype == napi_number)
	{
		double cVal;
		status = napi_get_value_double( env, val, &cVal);
		assert(status == napi_ok);
		printf( "\n%lf", cVal );

	} else if (valuetype == napi_string)
	{
		size_t NumBytes=0;

		// get the length of the string, by setting NULL to the BUFF
		status = napi_get_value_string_utf8( env, val, NULL, 0, &NumBytes);
		assert(status == napi_ok);

		char *pBuff = new char[ NumBytes+2 ];
		// Need the one byte extra for the null termination
		status = napi_get_value_string_utf8( env, val, pBuff, NumBytes+1, &NumBytes);
		// *(pBuff + NumBytes) = 0;

		printf( "\n%s", pBuff);
		delete[] pBuff;

	} else if (valuetype == napi_symbol)
	{
		printf( "\nSYMBOL");
	} else if (valuetype == napi_object)
	{
		bool isArray = isArrayType( env, val );
		if ( isArray )
			printf( "\nARRAY");
		else
			printf( "\nOBJECT");

	} else if (valuetype == napi_function)
	{
		printf( "\nFUNCTION");
	} else if (valuetype == napi_external)
	{
		printf( "\nEXTERNAL");
	} else
	{
		printf( "\n UNKNOWN");
	}

}
