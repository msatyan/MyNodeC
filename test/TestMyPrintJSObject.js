const myaddon = require('bindings')('mync1');

function Main() {
    console.log(' ');
    console.log('////// Native function printing JSON object ////////');

    // Send some value to C function
    console.log();

    const val1 = {
        myString_1: 'Hello World',
        myNum_1: 1257,
        myNum_2: 1257.28,
        myBool_1: true,
        myArray_1: [2, 4, 6, 9, { a1: 10, b1 : 20.34, c1: 30, d1: [ 35,  2.6 ], e1: 45 } ],
        myNullVal_1: null,
        myObj_1: { a1: 1, b1 : 2},
        xyz: 'for more testing!'
    };

    let dbg_on = false;
    myaddon.CPrintJsonObject(val1, dbg_on);

    console.log();
    console.log('////// With Debug On /////' );
    dbg_on = true;
    myaddon.CPrintJsonObject(val1, dbg_on);
    // myaddon.CPrintJsonObject2(val1);
}



Main();

