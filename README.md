# [Node C Extension](https://msatyan.github.io/MyNodeC/)
A Sample node.js C/C++ Addons module by using N-API & node-addon-api along with CMake.js to build the native module. Also a SneakPeek into google V8 engine optimization while executing JavaScript (JS) code.

If you are new to node.js native (C/C++) Addons and starting the groundwork for creating one then you may come across many approaches such as V8, NAN, node-addon-api, N-API, node-gyp, CMake.js etc. For a new module the best choice could be to use **N-API** (or its C++ wrapper class **node-addon-api**).  

#### Glossary
- **[node.js](https://nodejs.org/en/)**
: is a server-side JavaScript runtime environment.
- **[V8](https://github.com/v8/v8)**
: is the default JavaScript engine used by node.js, it has a set of C++ library for application to interact with it directly.
- **[NAN](https://github.com/nodejs/nan)**
: Native Abstractions for Node.js; simplifies the life a bit by shielding from the crazy changes introduced by V8 API for every releases.
- **[node-addon-api](https://github.com/nodejs/node-addon-api)**
: Header-only C++ wrapper classes which simplify the use of the C based N-API provided by Node.js core.
- **[N-API](https://nodejs.org/api/n-api.html)**
: is the **node.js core C API** to interact with underlying JavaScript engine with Application Binary Interface (ABI) stability across Node.js versions.
- [CMake.js](https://github.com/cmake-js/cmake-js)
: CMake.js is a Node.js native addon build tool based on CMake (it is very similar to the traditional node-gyp).
- [NODE-GYP](https://github.com/nodejs/node-gyp)
: node-gyp is a cross-platform command-line tool to compile native extension.
- [BINDINGS](https://www.npmjs.com/package/bindings)
: It’s a Node.js package which allows us to export our native extension.
- BINDING.GYP : node-gyp uses this file to describes the configuration needed for compile and build native extension.


### Why [N-API](https://nodejs.org/api/n-api.html) ?
Node.js is a JavaScript library, yet its core is writ in C/C++ ([V8](https://github.com/v8/v8), [Libuv](https://libuv.org/) and many other such modules). The easy and popular way of writing a node.js modules is also by using JavaScript. Such a modules are mostly platform independent and easy to manage. There are times when the performance of JavaScript is not enough, then we may have to consider native Node.js Addon modules. There are many advantages with native Addon node modules, efficient and excellent runtime performance, and the list go on. One of the major downside of native node module is the overhead of maintenance. This overhead alone is good enough to keep us think twice before introducing a native module. Till the arrival of N-API none of the abstraction API used to provide ABI stability across node.js major releases, then we may have to recompile our native module with each major node.js release that often come with build breakage. There are many effort in the past to eliminate or minimize such difficulties, [NAN](https://github.com/nodejs/nan) is the most popular among that. Though NAN did a reasonably good job, still not addressed all possible pain points.

The [N-API](https://nodejs.org/api/n-api.html) is expected to address this problem to a new level, it is expected to be Application Binary Interface (ABI) stable across versions of Node.js release. This will be a big relief for those who maintain native node.js Addon modules. Though the N-API was available with two past LTS node releases, it was experimental at that time. The current node.js LTS release (v10) has marked it as stable. I feel then it is right time to jump in and start using it. So far I am impressed with the concept and design because of its simplicity and easy to use than NAN.

The **N-API** is C language API and it is part of node.js core itself, then no external module dependency. To provide support for C++, the node.js team is also maintains a C++ wrapper module (created on top of N-API) called [node-addon-api](https://github.com/nodejs/node-addon-api). This wrapper is not part of node.js core, still it is maintained by the node.js team.


### Native addon functionalities coved in this example
This example try to mix and match both **N-API** and **node-addon-api** in the same module, such approach provides better flexibility for a native addons project.
- Calling a native function from JavaScript
- Send data to native function
- Receive data from native function
- Send and Receive data between JS and native function
- Basic error handling.
- Create NativeObject
- Callback
- Promise
- Event Emitter


### Prerequisite
- [node.js](https://nodejs.org/en/) (v10 or higher)
- [CMake](https://cmake.org/) (v3.10 or higher)
- [CMake.js](https://github.com/cmake-js/cmake-js) (v6 or higher)

```bash
# install CMake.js
npm install -g cmake-js
cmake-js    --help
```

### Clone the repository
```bash
git clone https://github.com/msatyan/MyNodeC.git
cd MyNodeC

# Install dependency and build
npm install
```

### Build native module
```bash
# build native module with cmake-js
cmake-js compile

# or
cmake-js build

# for debug build
cmake-js build --debug
```

### FYI: cmake-generators for VS
- https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html
- https://cmake.org/cmake/help/latest/generator/Visual%20Studio%2016%202019.html
```bash
# Visual Studio Generators
Visual Studio 14 2015
Visual Studio 15 2017
Visual Studio 16 2019

# Example:
# FYI: CMake 3.7.2 or higher needed for VS 2017
cmake-js -G "Visual Studio 15 2017 Win64"
cmake-js build --release -G "Visual Studio 15 2017 Win64"
cmake-js build --debug   -G "Visual Studio 15 2017 Win64"

# FYI: CMake 3.14 or higher needed for VS 2019
cmake-js -G "Visual Studio 16 2019" -A Win32
cmake-js -G "Visual Studio 16 2019" -A x64
cmake-js -G "Visual Studio 16 2019" -A ARM
cmake-js -G "Visual Studio 16 2019" -A ARM64
```

### Run some sample
The following **SpeedTest.js** sample program execute two functions one is a native function **SpeedTest_CPrimeCount()** and the other one is a pure JavaScript function **SpeedTest_JSPrimeCount()**. Both the functions are doing the same operation, calculating number of prime numbers between a given two numbers (say X=2 and Y=1000). Then the sample module compare the time taken by this two functions.

```bash
node test/SpeedTest.js
# try with different range
node test/SpeedTest.js  800

# Other examples
node test/EventEmit.js
node test/TestExtensions.js
```


### Try a simple **JavaScript vs C/C++ profiling** by using the SpeedTest.js
Try to run the SpeedTest.js with different value range; for a moment we may get puzzled with the performance comparison output. What we are seeing is perfectly a normal behavior, if we dig a bit deeper then we may find very interesting discovery.

```bash
node test/SpeedTest.js  3
node test/SpeedTest.js  8
node test/SpeedTest.js  50
node test/SpeedTest.js  100
node test/SpeedTest.js  500
node test/SpeedTest.js  1000
node test/SpeedTest.js  5000
node test/SpeedTest.js  10000
node test/SpeedTest.js  25000
node test/SpeedTest.js  50000
```

#### We may see the following interesting behaviors
The performance variation we are seeing is because the V8 engine compilers (Ignition & TurboFan) started getting engaged and disengaged at various stages of JS code efficient execution. Two major module involved in this are:
- **Ignition**: The newest interpreter of V8 engine.
- **TurboFan**: The newest optimizing compiler of V8 engine.

##### 1) At near lower value ranges
- Performance of of JS may not be that bad:  
JavaScript is a dynamically typed language, it is difficult to guess data type of variables from JS code alone (please see the following code snippet). Then V8 has to do some runtime profiling and heuristic assumption about the code. The V8 collects metadata information about the code and its runtime behaviors for each run iterations. Since we are at very early iterations, V8 may not have enough metadata information about the JS code and runtime behavior to compile the code it into native. Then the **Ignition** is the only one to be engaged at this moment. The Ignition will get start converting the JS code into equivalent bytecode (and it may get further fine-tuned the bytecode in subsequent iterations if necessary). The subsequent run iterations, the bytecode is being used until the equivalent native code is ready.

```JavaScript
function Add( a, b ) {
    return( a + b );
}

// These are perfectly a valid JavaScript scenario
// Not recommended such usage for better code optimization.
console.log( Add(3, 5) );
console.log( Add("Hello ", "World !") );
```

##### 2) Slightly above lower value ranges
- Performance of of JS execution have start falling down significantly:  
The V8 may have started getting metadata information about various part of the JS code and the runtime behaviors based on its previous run iterations. This information is good enough for portions of  bytecode to be converted to native. Then it is time to get **TurboFan** compiler engaged and it will be busy for some time converting bits and pieces of the bytecode to native by using **peephole optimization** technique. The reason for the JS runtime performance degradation in this spectrum is because a slice of processing power is being diverted for TurboFan.

##### 3) Somewhat mid to upper value ranges
- Performance of of JS start getting better:  
The **TurboFan** compiler may be still active for converting the remaining bytecode to native. By now a significant portion of the bytecode is already in native, then those instructions can be executed faster if the runtime behavior remain same.

##### 4) Upper value ranges
- Performance of JS function is excellent and consistent:  
By now we may be wondering can JavaScript be performed this good, it is somewhat comparable to the native function execution speed. Yes it is not magic, the **TurboFan** compiler has converted most (if not all) bytecode to native. From now onwards no need of TurboFan to be engaged. The native instruction can be send directly to the underlying processors (as long as the runtime behavior remain same) and it is expected be run fast. There are situation V8 may not be successful in converting the entire JS bytecode to native; if so any leftover portion will be interpreted by Ignition.


### SpeedTest.js profile output
- y  :the rage argument passed to SpeedTest.js
- rs :relative speed when compared C & JS.
- c  :time taken by C function for the given argument y value.
- js :time taken by JS function for the given argument y value.
```JavaScript
let ProfileOutput = [
{ y: 3, rs: 15, c: 10299, js: 158901 },
{ y: 5, rs: 11, c: 10800, js: 122999 },
{ y: 10, rs: 11, c: 10800, js: 122500 },
{ y: 25, rs: 11, c: 10900, js: 124499 },
{ y: 50, rs: 11, c: 10900, js: 128200 },
{ y: 100, rs: 11, c: 11500, js: 136400 },
{ y: 250, rs: 11, c: 16400, js: 185700 },
{ y: 500, rs: 11, c: 32900, js: 364000 },
{ y: 800, rs: 35, c: 60401, js: 2171500 },
{ y: 1000, rs: 28, c: 77400, js: 2189001 },
{ y: 1500, rs: 15, c: 152599, js: 2311900 },
{ y: 2000, rs: 10, c: 265800, js: 2658199 },
{ y: 5000, rs: 3, c: 1430501, js: 4496300 },
{ y: 8000, rs: 2, c: 3347300, js: 7514100 },
{ y: 10000, rs: 2, c: 5248800, js: 10847200 },
{ y: 15000, rs: 1, c: 10421999, js: 20148500 },
{ y: 20000, rs: 1, c: 19104700, js: 33193900 },
{ y: 30000, rs: 1, c: 40006900, js: 66896801 },
{ y: 40000, rs: 1, c: 71726800, js: 114892000 },
{ y: 50000, rs: 1, c: 106460200, js: 170908100 },
{ y: 100000, rs: 1, c: 389390700, js: 635012200 },
{ y: 150000, rs: 1, c: 843773700, js: 1368024300 },
{ y: 200000, rs: 1, c: 1473544300, js: 2392540000 }
];
```
