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

int ObjAddVal_utf8(  napi_env env, napi_value obj, const char *key, const char *val);
int ObjAddVal_Int32( napi_env env, napi_value obj, const char *key, int val );
int ObjAddVal_double( napi_env env, napi_value obj, const char *key, double val );
void MyPrintValueType( napi_env env, napi_value val, char *name );
void MyPrintValueType2( napi_valuetype valuetype, char *name );

#endif  // _EXTUTIL_H_
