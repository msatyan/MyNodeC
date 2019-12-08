'use strict'

const EventEmitter = require('events').EventEmitter
const addon = require('bindings')('mync1')

function Test_CallEmit(test_choice) {
    const emitter = new EventEmitter()

    emitter.on('start', () => {
        console.log( '# Sensor reading started ...');
    })

    emitter.on('sensor1', (evt) => {
        // This module will be called as on when the
        // sensor1 data available for consuming from JS
        console.log(evt);
    })

    emitter.on('sensor2', (evt) => {
        console.log(evt);
    })

    emitter.on('end', () => {
        console.log('# Sensor reading ended');
    })

    if( test_choice == 1) {
        console.log( "===== Test=CallEmit1 =====" );
        addon.CallEmit1( emitter.emit.bind(emitter) );
    } else {
        console.log( "===== Test=CallEmit2 =====" );
        addon.CallEmit2( emitter.emit.bind(emitter) );
    }
}


function Main() {
    let test_choice = 1;
    Test_CallEmit(test_choice);

    console.log();
    console.log();
    test_choice = 2;
    Test_CallEmit(test_choice);
}
Main();