const myaddon = require('bindings')('mync1');

function Test_NativeCalls()
{
    console.log(' ');
    console.log('///////////  Test_NativeCalls //////////////');

    // Call a C function
    myaddon.sayHello();

    // Send some value to C function
    console.log();
    myaddon.CPrint("Hello!!! from JavaScript");

    // Receive some value from C function
    const str = myaddon.GetValueFromC();
    console.log(`${str}  (Received from C printed by JS)`);

    // Get a Json Object from C function
    console.log();
    var obj1 = myaddon.CreateJsonObject();
    console.log("CreateJsonObject-1 returned : ", obj1);

    console.log();
    obj1 = myaddon.CreateJsonObject("Name given by JS function");
    console.log("CreateJsonObject-2 returned : ", obj1);


    // Send and receive values
    console.log();
    const x = 8;
    const y = 100;
    const prime = myaddon.SpeedTest_CPrimeCount(x, y);
    console.log(`Prime numbers between ${x} and ${y} is ${prime}`);
}


// We can use this for SPEED TEST between JavaScrip and C
// Find the number of prime numbers between X and Y
// The equivalent C function is SpeedTest_CPrimeCount
function SpeedTest_JSPrimeCount(x, y)
{
    let i = 0;
    let j = 0;
    let VRange = 0;
    let isPrime = 0;
    let PrimeCount = 0;

    if (x < 2)
        x = 2;

    y += 1;
    i = x;
    while (i < y)
    {
        isPrime = 1;
        VRange = i / 2; // This Validation Range is good enough
        j = 2;
        VRange += 1;
        while (j < VRange)
        {
            if (i % j == 0)
            {
                j += 1;
                isPrime = 0;
                break;
            }
            j += 1;
        }

        if (isPrime)
        {
            PrimeCount += 1;
        }

        i += 1;
    }

    return PrimeCount
}



function Native_vs_JavaScript(x, y)
{
    console.log(' ');
    console.log(' ');
    console.log('/////////// Performance: Native_vs_JavaScript //////////////');
    console.log("Speed Test: \'Pure JavaScript\' vs \'Native Code\'. ");
    console.log(`Calculating Prime Numbers Between ${x} and ${y}`);

    console.log(' ');
    console.log('Executing C  function, please wait....');

    //  current high-resolution real time in a bigint
    let s = process.hrtime.bigint();

    // Calculating PrimeCount by using Native call
    let rc3_c = myaddon.SpeedTest_CPrimeCount(x, y);

    let e = process.hrtime.bigint();
    let delta_c = e - s;

    console.log('Executing JS function, please wait....');
    s = process.hrtime.bigint();;

    // Calculating PrimeCount by using Pure JavaScript function
    let rc3 = SpeedTest_JSPrimeCount(x, y);

    e = process.hrtime.bigint();
    let delta_js = e - s;

    console.log(`Prime numbers between ${x} and ${y} is ${rc3_c}`);

    if (rc3 == rc3_c)
    {
        console.log(' ');
        console.log('Time taken by :');
        console.log(`     Native function = ${delta_c};`);
        console.log(`     Nodejs function = ${delta_js};`);
        console.log(' ');
        let r = delta_js / delta_c;
        console.log(`The Native C function appeared to be ${r} times faster`);
    }
    else
    {
        console.log(`Error: Prime Count not matching C=${rc3_c} Node=${rc3}`);
    }

    console.log(' ');
}


function Main()
{
    Test_NativeCalls();
    Native_vs_JavaScript(2, 5000);
}

Main();
