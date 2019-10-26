const myaddon = require('bindings')('mync1');



// We can use this for SPEED TEST between JavaScrip and C
// Find the number of prime numbers between X and Y
// The equivalent C function is SpeedTest_CPrimeCount
function SpeedTest_JSPrimeCount(x, y) {
    let i = 0;
    let j = 0;
    let VRange = 0;
    let isPrime = 0;
    let PrimeCount = 0;

    if (x < 2)
        x = 2;

    y += 1;
    i = x;
    while (i < y) {
        isPrime = 1;
        VRange = i / 2; // This Validation Range is good enough
        j = 2;
        VRange += 1;
        while (j < VRange) {
            if (i % j == 0) {
                j += 1;
                isPrime = 0;
                break;
            }
            j += 1;
        }

        if (isPrime) {
            PrimeCount += 1;
        }

        i += 1;
    }

    return PrimeCount
}



function SppdTest(x, y) {
    console.log(' ');
    console.log(' ');
    console.log('/////////// SppdTest: Native vs JS //////////////');
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

    if (rc3 == rc3_c) {
        console.log(' ');
        console.log('Time taken by :');
        console.log(`     Native function = ${delta_c};`);
        console.log(`     Nodejs function = ${delta_js};`);
        console.log(' ');
        let r = delta_js / delta_c;
        console.log(`The Native C function appeared to be ${r} times faster`);
    }
    else {
        console.log(`Error: Prime Count not matching C=${rc3_c} Node=${rc3}`);
    }

    console.log(' ');
}

function TestNativeCalls() {
    console.log(' ');
    console.log('///////////  TestNativeCalls //////////////');

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
}


function TestMyNativeObject() {
    var obj = new myaddon.MyObject(10);
    console.log(obj.plusOne()); // 11
    console.log(obj.plusOne()); // 12
    console.log(obj.plusOne()); // 13

    console.log(obj.multiply().value); // 13
    console.log(obj.multiply(10).value); // 130

    var newobj = obj.multiply(-1);
    console.log(newobj.value); // -13
    console.log(obj === newobj); // false
}

function TestCallback() {
    let x = 8;
    let y = 100;

    console.log("Start: TestCallback()");
    // The native addon function take a JS callback function as argument to it.
    myaddon.MyCallback1(msg => console.log(msg));

    // The native addon is being given three params, x, y, and callback function
    // The native function internally call the JS callback by passing two params (msg and p)
    myaddon.MyCallback2(x, y, (msg, p) => {
        console.log(msg); // msg and p are the arguments pass on from Native function
        console.log(`Prime numbers between ${x} and ${y} is ${p}`);
    });

    console.log("End: TestCallback()");
}

function TestPromise() {
    // Send and receive values
    console.log();
    const x = 8;
    const y = 100;

    console.log("Start: TestPromise()");
    // const prime = myaddon.SpeedTest_CPrimeCount(x, y);
    // console.log(`Prime numbers between ${x} and ${y} is ${prime}`);

    // Example of a Promise
    myaddon.MyPromise1SpeedTest(x, y)
        .then((pCount) => { console.log(`MyPromise1SpeedTest ${pCount}`) },
            err => { console.log(err) });

    console.log("End: TestPromise()");
}


function Main() {
    TestNativeCalls();
    // SppdTest(2, 5000);

    TestMyNativeObject();

    TestCallback();

    TestPromise();
}

// Main();


//////////////////////////////
function TestNativeCalls2() {
    console.log(' ');
    console.log('///////////  TestNativeCalls //////////////');

    // Send some value to C function
    console.log();

    const val1 = { a: 'Hello World'};
    myaddon.CPrintJsonObject(val1);
}

TestNativeCalls2();