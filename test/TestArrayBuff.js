'use strict'
const myaddon = require('bindings')('mync1');

function test1() {
    const i32array = new Int32Array(10);
    for (let i = 0; i < 10; ++i)
        i32array[i] = i * 5;

    const sum = myaddon.MyArrayBuffSum(i32array.buffer);
    console.log();
    console.log();
    console.log(`js: Sum of the array  = ${sum}`);
    console.log(`The value of array has modified at C with direct memory access`);
    for (let i = 0; i < 10; ++i)
        console.log(`js: i32array[i]  = ${i32array[i]}`);
}

test1();

