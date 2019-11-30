const myaddon = require('bindings')('mync1');

// Call the function "ThreadSafe_AsyncStreamSearch" which the native bindings library exposes.
// The function accepts a callback which it will call from the worker thread and
// into which it will pass prime numbers. This callback simply prints them out.
function Test_ThreadSafe_AsyncStreamSearch( t ) {

  myaddon.AsyncStreamSearch( t, (obj) => {

    console.log( JSON.stringify(obj) );

  } );

}

function Main() {
      Test_ThreadSafe_AsyncStreamSearch( 11 );
}
Main();
