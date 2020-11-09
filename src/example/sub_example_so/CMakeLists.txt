set(PROJECT_NAME ${SOLUTION_NAME}.static_example)
message(STATUS "Building ${PROJECT_NAME}")
project(${PROJECT_NAME})

file(GLOB headers *.h)
file(GLOB sources *.cpp)
add_library(${PROJECT_NAME} STATIC EXCLUDE_FROM_ALL ${headers} ${sources})
message("Adding headers: ${headers}")
message("Adding sources: ${sources}")

include_directories(
        ${CMAKE_SOURCE_DIR}
)
message("Including directory: ${CMAKE_SOURCE_DIR}")

target_link_libraries(${PROJECT_NAME}
        ${SOLUTION_NAME}.logging
        ${CONAN_LIBS}
        fmt
        spdlog)
message("")