set(PROJECT_NAME ${SOLUTION_NAME}.static_example)
message(STATUS "Building ${PROJECT_NAME}")
project(${PROJECT_NAME})

file(GLOB headers *.h)
file(GLOB sources *.cpp)
add_library(${PROJECT_NAME} STATIC ${headers} ${sources})
message("Adding headers: ${headers}")
message("Adding sources: ${sources}")

include_directories(
        ${CMAKE_SOURCE_DIR}
)
message("Including directory: ${CMAKE_SOURCE_DIR}")

target_compile_definitions(${SOLUTION_NAME}.logging PRIVATE PROJECT_NAME="${PROJECT_NAME}")
target_link_libraries(${PROJECT_NAME} PRIVATE ${SOLUTION_NAME}.logging)

message("Including library: ${SOLUTION_NAME}.logging with PROJECT_NAME=${PROJECT_NAME}")
message("")