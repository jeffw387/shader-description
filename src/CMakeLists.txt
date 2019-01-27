message("From src/:")
message("List dir: ${CMAKE_CURRENT_LIST_DIR}")
message("Source dir: ${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(json-shader main.cpp)
target_link_libraries(json-shader PRIVATE ${CONAN_LIBS})
target_include_directories(json-shader PRIVATE ${CMAKE_CURRENT_LIST_DIR})

add_executable(json-shader-tests catchmain.cpp)
target_link_libraries(json-shader-tests PRIVATE ${CONAN_LIBS})
target_include_directories(json-shader-tests PRIVATE ${CMAKE_CURRENT_LIST_DIR})

set(common-headers 
  split_view.hpp 
  buffer_block.hpp
  make_glsl_buffer.hpp 
  make_glsl_input.hpp
  make_glsl_output.hpp
  make_glsl_image.hpp
  )
target_sources(json-shader PUBLIC ${common-headers})
target_sources(json-shader-tests PUBLIC 
  ${common-headers} 
  split_view.test.cpp 
  make_glsl_buffer.test.cpp
  make_glsl_input.test.cpp
  make_glsl_output.test.cpp
  make_glsl_image.test.cpp)