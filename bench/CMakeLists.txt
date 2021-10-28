set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)

add_subdirectory(benchmark)
include_directories(benchmark/include)

# Flags for gcc, clang, intel compilers:
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  include(CheckCXXCompilerFlag)
  check_cxx_compiler_flag(-std=c++11 HAVE_FLAG_CXX_11)
  if (HAVE_FLAG_CXX_11)
    set(CMAKE_CXX_FLAGS "-Wall -std=c++11 ${CMAKE_CXX_FLAGS}")
  else ()
    message(FATAL_ERROR "Gorram! Your compiler is too frakking old. C++11 support is required for benchmarks.")
  endif ()
  set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
  set(CMAKE_CXX_FLAGS_DEBUG "-g -pedantic -fno-omit-frame-pointer -fno-inline-functions")
endif ()

set(bench_cc
  xs1024_bench.cc
)

add_executable(xs_benchmark ${bench_cc})

target_link_libraries(xs_benchmark
  benchmark
  cproject_static
  ${CMAKE_THREAD_LIBS_INIT}
  ${MATH_LIBRARIES}
)
