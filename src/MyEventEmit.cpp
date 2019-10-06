#include <napi.h>
#include <thread>

int ReadSensor1()
{
	static int sensor1 = 0;
	return(++sensor1);
}

int ReadSensor2()
{
	static int sensor2 = 0;
	return(++sensor2);
}


Napi::Value CallEmit(const Napi::CallbackInfo &info)
{
    char buff1[128];
	char buff2[128];

    Napi::Env env = info.Env();

    Napi::Function emit = info[0].As<Napi::Function>();
    emit.Call(  {Napi::String::New(env, "start")}  );

    for (int i = 0; i < 6; i++)
    {
		// Let us simulate some delay for collecting data from its sensors
		// std::this_thread::sleep_for(std::chrono::seconds(1));
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		sprintf(buff1, "sensor-1 data %d ...", ReadSensor1() );

        emit.Call( { Napi::String::New(env, "sensor1"),
                   Napi::String::New(env, buff1 ) } );

		// Let, sensor 2 data is reported half the rate as sensor1
		if (i % 2)
		{
			sprintf(buff2, "sensor-2 data %d ...", ReadSensor2() );
			emit.Call({ Napi::String::New(env, "sensor2"),
					   Napi::String::New(env, buff2) });
		}
    }

    emit.Call( {Napi::String::New(env, "end")} );
    return Napi::String::New( env, "OK" );
}

