project(hare.tests)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

file(GLOB_RECURSE inner_sources ./*.cpp)
message("Adding sources: ${inner_sources}")
add_executable(${PROJECT_NAME} ${inner_sources})


target_link_libraries(${PROJECT_NAME} PRIVATE
    hare
    GTEST
    ${GTEST_BOTH_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT})
