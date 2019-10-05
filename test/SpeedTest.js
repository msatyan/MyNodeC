'use strict';

const myaddon = require('bindings')('mync1');


/*
// The C Function doing the PrimeCount calculation

int CPrimeCount( int x, int y )
{
	int PrimeCount = 0;
	int isPrime = 0;
	int VRange = 0;
	int i = 0;
	int j = 0;

	// printf( "\n (x=%d, y=%d)", x, y);
	if (x < 2)
		x = 2;

	++y;
	for (i = x; i < y; i++)
	{
		isPrime = 1;

		VRange = i / 2; //This Validation Range is good enough
		++VRange;
		for (j = 2; j < VRange; j++)
		{
			// Check whether it is  divisible by any number other than 1
			if (!(i % j))
			{
				isPrime = 0;
				break;
			}
		}

		if (isPrime)
		{
			++PrimeCount;
		}
	}

	return(PrimeCount);
}
*/



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
        console.log(`Time taken by C  function = ${delta_c}`);
        console.log(`Time taken by JS function = ${delta_js}`);
        console.log(' ');
        let r = delta_js / delta_c;
        console.log(`The Native C function appeared to be ${r} times faster`);
    }
    else {
        console.log(`Error: Prime Count not matching C=${rc3_c} Node=${rc3}`);
    }

    console.log(' ');
}


function Main() {
    let y = 1000;

    if (process.argv.length == 3) {
        let tmpy = Number(process.argv[2]);
        if (tmpy > 2)
            y = tmpy;
    }

    SppdTest(2, y);
}

Main();



