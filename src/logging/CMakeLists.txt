set(PROJECT_NAME ${SOLUTION_NAME}.logging)
message(STATUS "Building ${PROJECT_NAME} started.")
project(${PROJECT_NAME})

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_compile_options(-fPIC)

file(GLOB_RECURSE headers ./*.h)
file(GLOB_RECURSE template_headers ./*.hpp)
file(GLOB_RECURSE sources ./*.cpp)
message("Adding headers from: ${headers}")
message("Adding header templates: ${template_headers}")
message("Adding sources : ${sources}")
set(files ${headers} ${template_headers} ${sources})

add_library(${PROJECT_NAME} SHARED EXCLUDE_FROM_ALL ${files})

target_compile_definitions(${PROJECT_NAME} PRIVATE
        -DPROJECT_NAME="${SOLUTION_NAME}"
        )

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS} fmt spdlog)
#conan_target_link_libraries(${PROJECT_NAME} fmt spdlog)

#message("Including directory: ${CMAKE_CURRENT_SOURCE_DIR}")
#
#conan_target_link_libraries(${PROJECT_NAME} fmt spdlog)
#
#message("Linking private  library: fmt")
#target_link_libraries(${PROJECT_NAME} PUBLIC fmt)
#message("Linking private  library: spdlog")
#target_link_libraries(${PROJECT_NAME} PUBLIC spdlog)
#target_link_libraries(${PROJECT_NAME} PUBLIC ${CONAN_LIBS})

message(STATUS "Building ${PROJECT_NAME} finished.")
message("")