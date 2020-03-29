set(PROJECT_NAME ${SOLUTION_NAME}.shared_example)
message(STATUS "Building ${PROJECT_NAME}")
project(${PROJECT_NAME})

file(GLOB headers *.h)
file(GLOB sources *.cpp)
add_library(${PROJECT_NAME} SHARED EXCLUDE_FROM_ALL ${headers} ${sources})
message("Adding headers: ${headers}")
message("Adding sources: ${sources}")

include_directories(
        ${CMAKE_SOURCE_DIR}
)
message("Including directory: ${CMAKE_SOURCE_DIR}")

link_specific_logger(${PROJECT_NAME})
message("")