set(PROJECT_NAME ${SOLUTION_NAME}.example)
message(STATUS "Building ${PROJECT_NAME}")
project(${PROJECT_NAME})

file(GLOB headers *.h)
file(GLOB sources *.cpp)
add_executable(${PROJECT_NAME}
        ${headers}
        ${sources})
message("Adding headers: ${headers}")
message("Adding sources: ${sources}")

include_directories(
        ${CMAKE_SOURCE_DIR}
)
message("Including directory: ${CMAKE_SOURCE_DIR}")

target_compile_definitions(${SOLUTION_NAME}.logging PRIVATE PROJECT_NAME="${PROJECT_NAME}")
target_link_libraries(${PROJECT_NAME} PRIVATE ${SOLUTION_NAME}.logging)

message("Including library: ${SOLUTION_NAME}.logging with PROJECT_NAME=${PROJECT_NAME}")

target_link_libraries(${PROJECT_NAME} PUBLIC ${SOLUTION_NAME}.static_example)
message("Including library: ${SOLUTION_NAME}.static_example")
target_link_libraries(${PROJECT_NAME} PUBLIC ${SOLUTION_NAME}.shared_example)
message("Including library: ${SOLUTION_NAME}.shared_example")

message("")