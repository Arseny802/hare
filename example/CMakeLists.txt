project(hare.example)

add_subdirectory(shared_library_example)
add_subdirectory(static_library_example)

add_executable(${PROJECT_NAME} src/console.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${PROJECT_NAME}.shared
    ${PROJECT_NAME}.static)
