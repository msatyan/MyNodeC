# [Node C Extension](https://msatyan.github.io/MyNodeC/)
A Sample node.js C Addons module by using N-API with CMake.js to build it.

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


### Functionalities coved in this example
- Calling a native function from JavaScript
- Send data to native function
- Receive data from native function
- Send and Receive data between JS and native function
- Basic error handling.


### Prerequisite
- [node.js](https://nodejs.org/en/) (v10 or higher)
- [CMake](https://cmake.org/) (v3.10 or higher)
- [CMake.js](https://github.com/cmake-js/cmake-js) (v6 or higher)

```bash
# install CMake.js
npm install -g cmake-js
cmake-js    --help
```

### Clone
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


### Run a sample
The following **SpeedTest.js** sample program execute two functions one is a native function **SpeedTest_CPrimeCount()** and the other one is a pure JavaScript function **SpeedTest_JSPrimeCount()**. Both the functions are doing the same operation, calculating number of prime numbers between a given two numbers (say X=2 and Y=1000). Then the sample module compare the time taken by this two functions.

```bash
npm test

# or
node test/SpeedTest.js
node test/SpeedTest.js  1000

# other test
node test/TestEextensions.js
```


