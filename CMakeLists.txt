cmake_minimum_required(VERSION 3.0)
project(cproject)

# Set build type to RELEASE by default:
if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type provided, default to RELEASE.")
  set(CMAKE_BUILD_TYPE "RELEASE")
endif ()

# Options can be turned on and off by providing cmake with a -DOPTIONNAME=ON (or OFF) argument.
# For example, to turn off benchmarks, build a shared library, and use sanitize flags in a DEBUG build:
#    cmake .. -DCMAKE_BUILD_TYPE=DEBUG -DBuildBench=OFF -DBuildShared=ON -DSanitize=ON
option(BuildTest     "BuildTest"      ON)
option(BuildBench    "BuildBench"     ON)
option(BuildStatic   "BuildStatic"    ON)
option(BuildShared   "BuildShared"    OFF)
option(Sanitize      "Sanitize"       OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(Threads REQUIRED)
find_package(Math)
#find_package(CUDA)

include_directories(. include)

# Flags for gcc, clang, intel compilers:
if (CMAKE_C_COMPILER_ID STREQUAL "Clang" OR CMAKE_COMPILER_IS_GNUC OR CMAKE_C_COMPILER_ID STREQUAL "Intel")
  set(CMAKE_C_FLAGS "-Wall ${CMAKE_C_FLAGS}")
  set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
  set(CMAKE_C_FLAGS_DEBUG "-g -pedantic -fno-omit-frame-pointer -fno-inline-functions")
endif ()

if (Sanitize)
  set(CMAKE_C_FLAGS "-fsanitize=address -fsanitize=undefined ${CMAKE_C_FLAGS}")
endif ()

add_subdirectory(src)

if (BuildTest)
  if (NOT BuildStatic)
    message(FATAL_ERROR "You need to build the static library to run tests.")
  endif ()
  enable_testing()
  add_subdirectory(test)
endif ()

if (BuildBench)
  if (NOT BuildStatic)
    message(FATAL_ERROR "You need to build the static library to run benchmarks.")
  endif ()
  add_subdirectory(bench)
endif ()

message(STATUS "")
message(STATUS "BUILD SUMMARY")
message(STATUS "  CMAKE_GENERATOR      : ${CMAKE_GENERATOR}")
message(STATUS "  Compiler ID          : ${CMAKE_C_COMPILER_ID}")
message(STATUS "  Build type           : ${CMAKE_BUILD_TYPE}")
message(STATUS "  Build tests          : ${BuildTest}")
message(STATUS "  Build benchmarks     : ${BuildBench}")
message(STATUS "  Sanitize flags       : ${Sanitize}")
#message(STATUS "  FoundCUDA            : ${CUDA_FOUND}")
message(STATUS "  C_FLAGS              : ${CMAKE_C_FLAGS}")
if ("${CMAKE_BUILD_TYPE}" STREQUAL "RELEASE")
  message(STATUS "  C_FLAGS_RELEASE      : ${CMAKE_C_FLAGS_RELEASE}")
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
  message(STATUS "  C_FLAGS_DEBUG        : ${CMAKE_C_FLAGS_DEBUG}")
endif ()
message(STATUS "")

