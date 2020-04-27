set(PROJECT_NAME ${SOLUTION_NAME}.example)
message(STATUS "Building ${PROJECT_NAME}")
project(${PROJECT_NAME})

add_subdirectory(sub_example_a)
add_subdirectory(sub_example_so)

add_executable(${PROJECT_NAME} console.cpp)

include_directories(
        ${CMAKE_SOURCE_DIR}
        sub_example_a
        sub_example_so
)
message("Including directory: ${CMAKE_SOURCE_DIR}")

target_link_libraries(${PROJECT_NAME} PRIVATE ${SOLUTION_NAME}.logging)
message("Including library: ${SOLUTION_NAME}.logging")
target_link_libraries(${PROJECT_NAME} PUBLIC ${SOLUTION_NAME}.static_example)
message("Including library: ${SOLUTION_NAME}.static_example")
target_link_libraries(${PROJECT_NAME} PUBLIC ${SOLUTION_NAME}.shared_example)
message("Including library: ${SOLUTION_NAME}.shared_example")

message("")