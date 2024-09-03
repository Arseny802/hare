project(${CMAKE_PROJECT_NAME}.tests)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

file(GLOB_RECURSE inner_sources ./*.cpp)
message("Adding sources: ${inner_sources}")
add_executable(${PROJECT_NAME} ${inner_sources})


target_link_libraries(${PROJECT_NAME} PRIVATE
    ${CMAKE_PROJECT_NAME}
    GTEST
    ${GTEST_BOTH_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON)
