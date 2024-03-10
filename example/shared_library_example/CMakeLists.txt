project(hare.example.shared)

add_library(${PROJECT_NAME} SHARED
    src/worker.cpp)
target_link_libraries(${PROJECT_NAME} hare)
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS "HARE_EXAMPLE_SUB_SHARED_EXPORTS")

target_include_directories(${PROJECT_NAME}
    PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src")
