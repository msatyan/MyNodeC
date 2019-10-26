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


void MyPrintType( napi_env env, napi_value val, char *name )
{
  napi_valuetype xtype;

  napi_typeof( env, val, &xtype );
  if (xtype == napi_function)
  {
	  printf("\n napi_typeof of %s is %d", name, xtype);
  }
}

void MyPrintvalueType( napi_valuetype valuetype )
{
	if (valuetype == napi_undefined)
	{
		printf( "\n valuetype = napi_undefined");
	} else if (valuetype == napi_null)
	{
		printf( "\n valuetype = napi_null");
	} else if (valuetype == napi_boolean)
	{
		printf( "\n valuetype = napi_boolean");
	} else if (valuetype == napi_number)
	{
		printf( "\n valuetype = napi_number");
	} else if (valuetype == napi_string)
	{
		printf( "\n valuetype = napi_string");
	} else if (valuetype == napi_symbol)
	{
		printf( "\n valuetype = napi_symbol");
	} else if (valuetype == napi_object)
	{
		printf( "\n valuetype = napi_object");
	} else if (valuetype == napi_function)
	{
		printf( "\n valuetype = napi_function");
	} else if (valuetype == napi_external)
	{
		printf( "\n valuetype = napi_external");
	} else
	{
		printf( "\n valuetype = ? I don't know");
	}
}
