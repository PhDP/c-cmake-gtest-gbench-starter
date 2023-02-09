# Source files (except the main for the executable):
set(xs_src
  xs1024.c
)

# Compile the library
add_library(${XS_LIB_NAME} ${XS_LIB_TYPE} ${xs_src})

target_link_libraries(${XS_LIB_NAME} ${CMAKE_THREAD_LIBS_INIT} ${MATH_LIBRARIES})

install(TARGETS ${NEMO_LIB_NAME} LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

install(DIRECTORY ../include/xs DESTINATION include)

