#include "addon_api.h"
#include "extutil.h"
# include <assert.h>


void Pad(int level)
{
	const char *pad = "  ";
	for( int i=0; i<level; ++i)
		printf("%s", pad);
}


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
myobj_valuetype GetMyValueType( napi_env env, napi_value val )
{
	napi_status status;
	napi_valuetype valuetype;
	myobj_valuetype vtype = myobj_undefined;

	status = napi_typeof(env, val, &valuetype);
	assert(status == napi_ok);

	if (valuetype == napi_undefined) {
		vtype = myobj_undefined;
	} else if (valuetype == napi_null) {
		vtype = myobj_null;
	} else if (valuetype == napi_boolean) {
		vtype = myobj_boolean;
	} else if (valuetype == napi_number) {
		vtype = myobj_number;
	} else if (valuetype == napi_string) {
		vtype = myobj_string;
	} else if (valuetype == napi_symbol) {
		vtype = myobj_symbol;
	} else if (valuetype == napi_object) {
		bool isArray = isArrayType( env, val );
		if ( isArray )
			vtype = myobj_array;
		else
			vtype = myobj_object;
	} else if (valuetype == napi_function) {
		vtype = myobj_function;
	} else if (valuetype == napi_external) {
		vtype = myobj_external;
	} else {
		vtype = myobj_unknown_yet;
	}

	return( vtype );
}

char *GetMyValueTypeName( myobj_valuetype valuetype )
{
	char *name = NULL;

	if (valuetype == myobj_undefined) {
		name = (char *)"undefined";
	} else if (valuetype == myobj_null)	{
		name = (char *)"null";
	} else if (valuetype == myobj_boolean) {
		name = (char *)"boolean";
	} else if (valuetype == myobj_number) {
		name = (char *)"number";
	} else if (valuetype == myobj_string) {
		name = (char *)"string";
	} else if (valuetype == myobj_symbol) {
		name = (char *)"symbol";
	} else if (valuetype == myobj_object) {
		name = (char *)"object";
	} else if (valuetype == myobj_array) {
		name = (char *)"array";
	} else if (valuetype == myobj_function)	{
		name = (char *)"function";
	} else if (valuetype == myobj_external)	{
		name = (char *)"external";
	} else {
		name = (char *)"unknown";
	}

	return( name );
}


void MyPrintValue( napi_env env, napi_value val)
{
	napi_status status;
	napi_valuetype valuetype;

	status = napi_typeof(env, val, &valuetype);
	assert(status == napi_ok);

	if (valuetype == napi_undefined)
	{
		printf( "UNDEFINED");
	} else if (valuetype == napi_null)
	{
		printf( "NULL");
	} else if (valuetype == napi_boolean)
	{
		bool cVal;
		status =  napi_get_value_bool( env, val, &cVal);
		assert(status == napi_ok);
		printf( "%s", (cVal ? "true": "false") );

	} else if (valuetype == napi_number)
	{
		double cVal;
		status = napi_get_value_double( env, val, &cVal);
		assert(status == napi_ok);

		// g: the shortest representation: %e or %f to avoid trailing zeros.
		printf( "%lg", cVal );

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

		printf( "'%s'", pBuff);
		delete[] pBuff;

	} else if (valuetype == napi_symbol)
	{
		printf( "SYMBOL");
	} else if (valuetype == napi_object)
	{
		bool isArray = isArrayType( env, val );
		if ( isArray )
			printf( "ARRAY");
		else
			printf( "OBJECT");

	} else if (valuetype == napi_function)
	{
		printf( "FUNCTION");
	} else if (valuetype == napi_external)
	{
		printf( "EXTERNAL");
	} else
	{
		printf( "UNKNOWN");
	}
}


int MyPrintObj( napi_env env, napi_value obj, int level, int dbg_flag)
{
	napi_status status;
	size_t buff_len = 0;
    char buff[1024]; // Let us assume properties of the object are less than a K.
    napi_value obj_Properties;

	++level;
    status = napi_get_property_names( env, obj, &obj_Properties);
    assert(status == napi_ok);

    // The API can be used to iterate over result using napi_get_array_length and napi_get_element.
    uint32_t ArrayLen=0;
    status = napi_get_array_length( env, obj_Properties, &ArrayLen);
    assert(status == napi_ok);

	if ( dbg_flag == 1)
	{
		printf( "\n" );
		Pad(level);
    	printf( "// level=%d, properties=%d\n", level, ArrayLen);
		Pad(level);
	}
	else if ( level == 1)
	{
		Pad(level);
	}

	printf( "{");

    for( int i=0; i<(int)ArrayLen; ++i)
    {
        napi_value PropertyName;
		char *pName = NULL;
        napi_get_element( env, obj_Properties, i, &PropertyName);

        if (napi_get_value_string_utf8(env, PropertyName, (char *)&buff, sizeof(buff) - 2, &buff_len) != napi_ok)
        {
            napi_throw_error(env, "EINVAL", "Expected string");
            break;
        }
        buff[sizeof(buff) - 1] = '\0';
		pName = buff;

		napi_value val; // The value of the property.
		myobj_valuetype val_type;
		char *vtype_name = NULL;
		status = napi_get_property( env, obj, PropertyName, &val );
		assert(status == napi_ok);

		val_type =  GetMyValueType( env, val );
		vtype_name = GetMyValueTypeName( val_type );

		printf("\n");
		Pad(level+1);
		// Preint Key
		if ( dbg_flag == 1)
			printf("%s(%s): ", pName, vtype_name);
		else
			printf("%s: ", pName );

		// Preint value
		if ( val_type == myobj_object) {
			MyPrintObj( env, val, level, dbg_flag);
		} else if ( val_type == myobj_array) {
			MyPrintArray( env, val, level, dbg_flag);
		} else {
			MyPrintValue( env, val );
		}

		if (i<(int)(ArrayLen-1)) {
			printf(", ");
		}
    }
	// if ( level > 1)
	// 	printf( "\n}");
	// else
	printf( "\n");
	Pad(level);
	printf( "}");

	return(level);
}


int MyPrintArray( napi_env env, napi_value arr, int level, int dbg_flag)
{
	napi_status status;
	uint32_t ArrayLen=0;

	++level;
	status = napi_get_array_length( env, arr, &ArrayLen);
	assert(status == napi_ok);

	printf( "[");
    for( int i=0; i<(int)ArrayLen; ++i)
    {
        napi_value arr_val;
		myobj_valuetype val_type;
		char *pName = NULL;
        napi_get_element( env, arr, i, &arr_val);

		val_type = GetMyValueType( env, arr_val );
		if ( val_type == myobj_object) {
			MyPrintObj( env, arr_val, level, dbg_flag);
		} else if ( val_type == myobj_array) {
			MyPrintArray( env, arr_val, level, dbg_flag);
		} else {
			MyPrintValue( env, arr_val );
		}

		if (i<(int)(ArrayLen-1)) {
			printf(", ");
		}
	}
	printf( "\n");
	Pad(level);
	printf( "]");
	return(0);
}

