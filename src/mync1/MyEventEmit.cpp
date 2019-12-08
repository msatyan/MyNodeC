#include <node_api.h>
#include <napi.h>
#include <thread>
#include <assert.h>

int ReadSensor1()
{
    static int sensor1 = 0;
    return (++sensor1);
}

int ReadSensor2()
{
    static int sensor2 = 0;
    return (++sensor2);
}

///////////////////////////////////////////////////////////
// Emitter implimentation by using node-addon-api
// node-addon-api is the C++ wrapper on top of N-API
///////////////////////////////////////////////////////////
Napi::Value CCallEmit1(const Napi::CallbackInfo &info)
{
    char buff1[128];
    char buff2[128];

    Napi::Env env = info.Env();

    Napi::Function emit = info[0].As<Napi::Function>();
    emit.Call({Napi::String::New(env, "start")});

    for (int i = 0; i < 6; i++)
    {
        // Let us simulate some delay for collecting data from its sensors
        // std::this_thread::sleep_for(std::chrono::seconds(1));
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        sprintf(buff1, "sensor-1 data %d ...", ReadSensor1());

        emit.Call({Napi::String::New(env, "sensor1"),
                   Napi::String::New(env, buff1)});

        // Let, sensor 2 data is reported half the rate as sensor1
        if (i % 2)
        {
            sprintf(buff2, "sensor-2 data %d ...", ReadSensor2());
            emit.Call({Napi::String::New(env, "sensor2"),
                       Napi::String::New(env, buff2)});
        }
    }

    emit.Call({Napi::String::New(env, "end")});
    return Napi::String::New(env, "OK");
}

///////////////////////////////////////////////////////////
// Emitter implimentation by using N-API
///////////////////////////////////////////////////////////
napi_value CCallEmit2(napi_env env, napi_callback_info info)
{
    const size_t MaxArgExpected = 1;
    napi_value args[MaxArgExpected];
    size_t argc = sizeof(args) / sizeof(napi_value);

    char buff1[128];
    char buff2[128];

    assert(napi_get_cb_info(env, info, &argc, args, NULL, NULL) == napi_ok);
    if (argc != 1)
        napi_throw_error(env, "EINVAL", "CallEmit2: Argument count mismatch");

    napi_value emit_cbJsFunc = args[0];

    napi_value global;
    size_t NumOfArgs = 0;
    napi_value cb_result;
    // We plan to use max of two argument to JS callback function
    napi_value aParams2cbJsFunc[2];

    assert(napi_get_global(env, &global) == napi_ok);
    assert(napi_create_string_utf8(env, "start",
                                   NAPI_AUTO_LENGTH, &aParams2cbJsFunc[0]) == napi_ok);

    NumOfArgs = 1; // The JS callback for start has only one arg
    assert(napi_call_function(env, global, emit_cbJsFunc,
                              NumOfArgs, aParams2cbJsFunc, &cb_result) == napi_ok);

    for (int i = 0; i < 6; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        sprintf(buff1, "sensor-1 data %d ...", ReadSensor1());

        assert(napi_create_string_utf8(env, "sensor1",
                                       NAPI_AUTO_LENGTH, &aParams2cbJsFunc[0]) == napi_ok);

        assert(napi_create_string_utf8(env, buff1,
                                       NAPI_AUTO_LENGTH, &aParams2cbJsFunc[1]) == napi_ok);

        NumOfArgs = 2; // The JS callback for sensors has one extra param.
        assert(napi_call_function(env, global, emit_cbJsFunc,
                                  NumOfArgs, aParams2cbJsFunc, &cb_result) == napi_ok);

        // Let, sensor 2 data is reported half the rate as sensor1
        if (i % 2)
        {
            sprintf(buff2, "sensor-2 data %d ...", ReadSensor2());

            assert(napi_create_string_utf8(env, "sensor2",
                                           NAPI_AUTO_LENGTH, &aParams2cbJsFunc[0]) == napi_ok);

            assert(napi_create_string_utf8(env, buff2,
                                           NAPI_AUTO_LENGTH, &aParams2cbJsFunc[1]) == napi_ok);

            NumOfArgs = 2; // The JS callback for sensors has one extra param.
            assert(napi_call_function(env, global, emit_cbJsFunc,
                                      NumOfArgs, aParams2cbJsFunc, &cb_result) == napi_ok);
        }
    }

    assert(napi_create_string_utf8(env, "end",
                                   NAPI_AUTO_LENGTH, &aParams2cbJsFunc[0]) == napi_ok);

    NumOfArgs = 1; // The JS callback for end has only one arg
    assert(napi_call_function(env, global, emit_cbJsFunc,
                              NumOfArgs, aParams2cbJsFunc, &cb_result) == napi_ok);

    napi_value rc;
    assert(napi_create_string_utf8(env, "ok", NAPI_AUTO_LENGTH, &rc) == napi_ok);
    return (rc);
}
