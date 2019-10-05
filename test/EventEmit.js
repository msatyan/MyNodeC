'use strict'

const EventEmitter = require('events').EventEmitter
const addon = require('bindings')('mync1')

function Main() {
    const emitter = new EventEmitter()

    console.log( "Under development...., event emitter implementation is incomplete" );
    emitter.on('start', () => {
        console.log( '### Sensor reading started ...');
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

    console.log( emitter );
    // Not ready yet
    // addon.callEmit( emitter.emit.bind(emitter) )
}

Main();