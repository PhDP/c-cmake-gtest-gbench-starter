# c-cmake starter with google test and google benchmark
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

A cross-platform C starter project with google test and google benchmark
support.

The project will compile a static library named cproject_static and, optionally,
a shared library named cproject.

# Organization

* **src** has the source files and the CMakeLists.txt to compile the library.
* **include** has the header files.
* **test** has the tests and related CMakeLists.txt.
* **bench** has the benchmarks and related CMakeLists.txt.

The main CMakeLists.txt file at the root of the project has options and further
documentation.

# Build

On Linux/Unix, to build and make the test:

    $ mkdir build && cd $_
    $ cmake ..
    $ make

By default, the makefiles will build the library, executable, tests,
and benchmarks. The commands

    $ ./test/xs_tests
    $ ./bench/xs_benchmark

will run the tests and benchmarks. And

    $ sudo make install

will install (at least on Linux) the library and executable to your computer's
path.

On Windows, you can use cmake to generate Visual Studio build files with
the same 'cmake ..' command.

By default, the project will be built in RELEASE mode, use

    $ cmake .. -DCMAKE_BUILD_TYPE=DEBUG

to build in DEBUG mode.

See the CMakeLists.txt file to see all the options.

# License

[MIT](http://opensource.org/licenses/MIT)

