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
  let search_time = 10;
  console.log( `Duration of search time specified in seconds = ${search_time}`);
  Test_ThreadSafe_AsyncStreamSearch( search_time );
}
Main();
