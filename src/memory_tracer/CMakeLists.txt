set(PROJECT_NAME ${SOLUTION_NAME}.memory_tracer)
message(STATUS "Building ${PROJECT_NAME} started.")
project(${PROJECT_NAME})

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_compile_options(-fPIC)

file(GLOB_RECURSE headers ./*.h)
file(GLOB_RECURSE template_headers ./*.hpp)
file(GLOB_RECURSE sources ./*.cpp)
message("Adding headers from: ${headers}")
message("Adding header templates: ${template_headers}")
message("Adding sources : ${sources}")
set(files ${headers} ${template_headers} ${sources})

add_library(${PROJECT_NAME} STATIC EXCLUDE_FROM_ALL ${files})

message(STATUS "Building ${PROJECT_NAME} finished.")
message("")