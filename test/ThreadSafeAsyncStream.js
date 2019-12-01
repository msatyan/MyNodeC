const myaddon = require('bindings')('mync1');

// The native addon function doing the Thrad Safe Async all is AsyncStreamSearch
// which accepts time  in second and a callback which it will call from the
// worker thread and this callback JS function simply prints them result out.
function Test_ThreadSafe_AsyncStreamSearch( t ) {

  // The actual addon function doing the thread safe call
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
