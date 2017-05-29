add_library(gtest ./gtest/gtest-all.cc)
include_directories(.)
target_link_libraries(gtest ${CMAKE_THREAD_LIBS_INIT})

set(test_src
  run_all.cc
  xs1024_spec.cc
)

add_executable(xs_tests ${test_src})

target_link_libraries(xs_tests
  gtest
  cproject_static
  ${CMAKE_THREAD_LIBS_INIT}
  ${MATH_LIBS}
)

add_test(
  NAME tests
  COMMAND xs_tests
)
