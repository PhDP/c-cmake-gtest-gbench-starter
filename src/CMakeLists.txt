# Source files (except the main for the executable):
set(cproject_src
  xs1024.c
)

# Compile the library
if (BuildShared)
  add_library(cproject SHARED ${cproject_src})
  target_link_libraries(cproject ${CMAKE_THREAD_LIBS_INIT} ${MATH_LIBRARIES})
  install(TARGETS cproject LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
endif ()

if (BuildStatic)
  add_library(cproject_static STATIC ${cproject_src})
  target_link_libraries(cproject_static ${CMAKE_THREAD_LIBS_INIT} ${MATH_LIBRARIES})
  install(TARGETS cproject_static LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
endif()

install(DIRECTORY ../include/xs DESTINATION include)

