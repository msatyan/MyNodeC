'use strict'

const EventEmitter = require('events').EventEmitter
const addon = require('bindings')('mync1')

// General theme of EventEmitter is: notify me when it is ready

function Main() {
    const emitter = new EventEmitter()

    emitter.on('start', () => {
        console.log('### Sensor reading started ...');
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
        console.log('### Sensor reading ended');
    })

    console.log("emitter is ");
    console.log(emitter);

    console.log("emitter.emit is ");
    console.log(emitter.emit);

    var x = emitter.emit.bind(emitter);
    console.log(x) // [Function: bound emit]

    // addon.callEmit( emitter.emit.bind(emitter) )
}

Main();
