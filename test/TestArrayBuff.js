'use strict'
const myaddon = require('bindings')('mync1');

function ArrayBufferExchange_BufferCreatedByJavaScript() {
    // Create Int32 Array from JavaScript.
    const i32array = new Int32Array(10);
    for (let i = 0; i < 10; ++i)
        i32array[i] = i * 5;

    // Pass the Array Buffer to Native Function
    const sum = myaddon.MyArrayBuffSum(i32array.buffer);
    console.log();
    console.log(`js: Sum of the array  = ${sum}`);
    console.log();
    console.log(`The value of array has modified at C with direct memory access`);
    console.log(`Let us print new values in the array`);
    for (let i = 0; i < 10; ++i) {
        // Print the modified (by native function) values.
        console.log(`js: i32array[i]  = ${i32array[i]}`);
    }
}


function ArrayBufferExchange_BufferCreatedByNative () {
    const s = 10;
    const m = 4;

    // Get an array buffer from native(the Multiplication Table)
    const ab = myaddon.GetMultiplicationTable( s, m );

    // we need to create a view for the underlying buffer,
    // Create a view, the data in the underlying buffer is Int32, then
    const MulTab = new Int32Array(ab);

    // Let us print the values of the table
    console.log( `ArrayBuffer: Multiplication table for ${m} (array size = ${MulTab.length})` );
    for (let i = 0; i < s; ++i)
        console.log(`js: MulTab[${i}]  = ${MulTab[i]}`);
}


function TypedArrayExchange_Int32ArrayCreatedByNative () {
    const s = 10;
    const m = 6;

    // Get an Int32 Array from native(the Multiplication Table)
    const MulTab = myaddon.GetMultiplicationTableInt32( s, m );

    // Let us print the values of the table
    console.log( `TypedArray: Multiplication table for ${m} (array size = ${MulTab.length})` );
    for (let i = 0; i < s; ++i)
        console.log(`js: MulTab[${i}]  = ${MulTab[i]}`);
}

function Main() {
    // JS to C
    ArrayBufferExchange_BufferCreatedByJavaScript();

    console.log()
    // C to JS
    ArrayBufferExchange_BufferCreatedByNative();

    console.log()
    // C to JS
    TypedArrayExchange_Int32ArrayCreatedByNative();
}
Main();

