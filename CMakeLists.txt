cmake_minimum_required(VERSION 3.11) # Minimum for FetchContent
project(xs)

# Set build type to RELEASE by default:
if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type provided, default to RELEASE.")
  set(CMAKE_BUILD_TYPE "RELEASE")
endif ()

# Options can be turned on and off by providing cmake with a -DOPTIONNAME=ON (or OFF) argument.
# For example, to turn off benchmarks, build a shared library, and use sanitize flags in a DEBUG build:
#    cmake .. -DCMAKE_BUILD_TYPE=DEBUG -DXS_BENCH=OFF -DXS_STATIC=OFF -DXS_SANITIZE=ON
option(XS_TEST        "Enables testing." ON)
option(XS_BENCH       "Enables benchmarks." ON)
option(XS_STATIC      "Builds a static library instead of a shared one." ON)
option(XS_SANITIZE    "Adds sanitize flags." OFF)

if (XS_STATIC)
  set(XS_LIB_NAME xs_static)
  set(XS_LIB_TYPE STATIC)
else ()
  set(XS_LIB_NAME xs)
  set(XS_LIB_TYPE SHARED)
endif ()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(Threads REQUIRED)
find_package(MATH)

include(FetchContent)

include_directories(. include)

if (XS_SANITIZE)
  set(CMAKE_C_FLAGS "-fsanitize=address -fsanitize=undefined ${CMAKE_C_FLAGS}")
endif ()

add_subdirectory(src)

if (XS_TEST)
  enable_testing()
  add_subdirectory(test)
endif ()

if (XS_BENCH)
  add_subdirectory(bench)
endif ()

message(STATUS "")
message(STATUS "BUILD SUMMARY")
message(STATUS "  CMAKE_GENERATOR      : ${CMAKE_GENERATOR}")
message(STATUS "  Compiler ID          : ${CMAKE_C_COMPILER_ID}")
message(STATUS "  Build type           : ${CMAKE_BUILD_TYPE}")
message(STATUS "  Library name         : ${XS_LIB_NAME}")
message(STATUS "  Library type         : ${XS_LIB_TYPE}")
message(STATUS "  Build tests          : ${XS_TEST}")
message(STATUS "  Build benchmarks     : ${XS_BENCH}")
message(STATUS "  Sanitize flags       : ${XS_SANITIZE}")
message(STATUS "  C_FLAGS              : ${CMAKE_C_FLAGS}")
if ("${CMAKE_BUILD_TYPE}" STREQUAL "RELEASE")
  message(STATUS "  C_FLAGS_RELEASE      : ${CMAKE_C_FLAGS_RELEASE}")
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
  message(STATUS "  C_FLAGS_DEBUG        : ${CMAKE_C_FLAGS_DEBUG}")
endif ()
message(STATUS "")

