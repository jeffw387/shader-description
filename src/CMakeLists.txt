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
  compile_hash.hpp
  glsl_type.hpp
  buffer_block.hpp
  make_buffer.hpp 
  make_input.hpp
  make_output.hpp
  make_image.hpp
  make_sampler.hpp
  make_constant.hpp
  make_push_constant.hpp
  make_shader.hpp
  )
target_sources(json-shader PUBLIC ${common-headers})
target_sources(json-shader-tests PUBLIC 
  ${common-headers} 
  split_view.test.cpp 
  make_buffer.test.cpp
  make_input.test.cpp
  make_output.test.cpp
  make_image.test.cpp
  make_sampler.test.cpp
  make_constant.test.cpp
  make_push_constant.test.cpp
  make_shader.test.cpp
  )