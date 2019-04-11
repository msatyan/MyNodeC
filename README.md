# [Node C Extension](https://msatyan.github.io/MyNodeC/)
A Sample node.js C Addons module by using N-API  

If you are new to node.js native (C/C++) Addons and starting the groundwork for creating one then you may come across many approaches such as V8, NAN, node-addon-api, N-API. If you are starting a new development now (2019) then your best choice could be to use N-API (or its C++ wrapper class node-addon-api).  

- **V8**: is the default JavaScript engine used by node.js, it has a set of C++ library for application to interact with it.
- **NAN**: Native Abstractions for Node.js; simplify the life a bit by shielding from the crazy changes introduced by V8 API for every releases.
- **node-addon-api**: Header-only C++ wrapper classes which simplify the use of the C based N-API provided by Node.js core.
- **N-API**: is the node.js core C API to interact with underlying JavaScript engine. It provides Application Binary Interface (ABI) stability guarantee across Node.js versions.



### Why N-API
Node.js is a JavaScript library, yet its core is writ in C/C++ ([V8](https://github.com/v8/v8), [Libuv](https://libuv.org/) and many other such modules). The easy and popular way of writing a node.js modules is also by using JavaScript. Such a modules are mostly platform independent and easy to manage. There are times when the performance of JavaScript is not enough, then you may have to consider native Node.js Addon modules. There are many advantages with native Addon node modules, efficient and excellent runtime performance, and the list go on. One of the major downside of native node module is the overhead of maintenance. This overhead alone is good enough to keep you think twice before introducing a native module. You may have to recompile your native module with each major node.js release that often come with build breakage. There are many effort in the past to eliminate or minimize such difficulties, [NAN](https://github.com/nodejs/nan) is the most popular among that. Though NAN did a reasonably good job, still not addressed all possible pain points.

The [N-API](https://nodejs.org/api/n-api.html) is expected to address this problem to a new level, it is likely Application Binary Interface (ABI) stable across versions of Node.js release. This will be a big relief for those who maintain native node.js Addon modules. Though the N-API was available with two past LTS node releases, it was experimental at that time. The current node.js LTS release (v10) has marked it as stable. I feel then it is right time to jump in and start using it. So far I am impressed with the concept and design because of its simplicity and easy to use than NAN.

The N-API is C based API and it is part of the node.js core itself, then no external module dependency. To provide support for C++, the node.js team is also maintains a C++ wrapper module (created on top of N-API) called [node-addon-api](https://github.com/nodejs/node-addon-api). This wrapper is not part of node.js core, still it is maintained by the node.js team.


### Functionalities coved in this example
- Calling a native function from JavaScript
- Send data to native function
- Receive data from native function
- Send and Receive data between JS and native function
- Basic error handling.


### Tools and tips
- [N-API](https://nodejs.org/api/n-api.html)
: It’s C API that allows us to interact with node.js engine in a completely abstract way.
- [NODE-GYP](https://github.com/nodejs/node-gyp)
: node-gyp is a cross-platform command-line tool to compile native extension.
- [BINDINGS](https://www.npmjs.com/package/bindings)
: It’s a Node.js package which allows us to export our native extension.
- BINDING.GYP : specify how we need to compile our native extension.



### Clone
```bash
git clone https://github.com/msatyan/MyNodeC.git
cd MyNodeC

# Install dependency and build
npm instll
```

### Building native module
```bash
# FYI
# node-gyp --python /work/python2.7
# node-gyp configure --msvs_version=2015
# node-gyp configure --msvs_version=2017
node-gyp configure


# node-gyp build  --release
# node-gyp build  --debug
node-gyp build

# if you prefer rebuild
node-gyp rebuild
```

### Test the native module
```bash
node test/test_extn.js
```


#### [FYI: node-gyp build helps](https://github.com/nodejs/node-gyp)
```bash
|:--------------|:--------------------------------------------------------
| **Command**   | **Description**
|:--------------|:--------------------------------------------------------
| `help`        | Shows the help dialog
| `build`       | Invokes `make`/`msbuild.exe` and builds the native addon
| `clean`       | Removes the `build` directory if it exists
| `configure`   | Generates project build files for the current platform
| `rebuild`     | Runs `clean`, `configure` and `build` all in a row
| `install`     | Installs node header files for the given version
| `list`        | Lists the currently installed node header versions
| `remove`      | Removes the node header files for the given version
|:--------------|:--------------------------------------------------------
```

