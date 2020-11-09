set(PROJECT_NAME ${CMAKE_PROJECT_NAME}.tests)
message(STATUS "Building ${PROJECT_NAME} started.")
project(${PROJECT_NAME})

include_directories(${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/src)

file(GLOB_RECURSE inner_sources ./*.cpp)
message("Adding sources: ${inner_sources}")
add_executable(${PROJECT_NAME} ${inner_sources})

#find_package(GTest REQUIRED)
#find_package(Threads REQUIRED)

set(libs
        ${CMAKE_PROJECT_NAME}.logging
        ${CMAKE_PROJECT_NAME}.memory_tracer
        ${GTEST_BOTH_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        )
target_link_libraries(${PROJECT_NAME} ${libs} GTEST)

message("Including directories: ${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/src")
message("Including libraries: ${libs}")

message(STATUS "Building ${PROJECT_NAME} finished.")
message("")