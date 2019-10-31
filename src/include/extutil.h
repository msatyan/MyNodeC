#ifndef _EXTUTIL_H_
#define _EXTUTIL_H_

#define ERR_COD_ObjAddKV "U10001"
#define ERR_STR_ObjAddKV "Failed to set Key & Value"

#define PROCESS_ERR_ObjAddKV( env, rc )\
    if( (rc) != 0 ) \
    {\
        napi_throw_error( (env), ERR_COD_ObjAddKV, ERR_STR_ObjAddKV );\
        return(NULL);\
    }


enum myobj_valuetype {
  myobj_undefined,
  myobj_null,
  myobj_boolean,
  myobj_number,
  myobj_string,
  myobj_symbol,
  myobj_object,
  myobj_function,
  myobj_external,
  myobj_unknown_yet,
  myobj_array
};


int ObjAddVal_utf8(  napi_env env, napi_value obj, const char *key, const char *val);
int ObjAddVal_Int32( napi_env env, napi_value obj, const char *key, int val );
int ObjAddVal_double( napi_env env, napi_value obj, const char *key, double val );
myobj_valuetype GetMyValueType( napi_env env, napi_value val );
char *GetMyValueTypeName( myobj_valuetype valuetype );
void MyPrintValue( napi_env env, napi_value val);
int MyPrintObj( napi_env env, napi_value obj, int level, int dbg_flag);
int MyPrintArray( napi_env env, napi_value arr, int level, int dbg_flag);
bool isArrayType( napi_env env, napi_value val);

#endif  // _EXTUTIL_H_
