set(PROJECT_NAME ${SOLUTION_NAME}.logging)
message(STATUS "Building ${PROJECT_NAME} started.")
project(${PROJECT_NAME})

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_compile_options(-fPIC)

set(project_directories
        .)
foreach (current_dir ${project_directories})
    file(GLOB_RECURSE inner_headers ${current_dir}/*.h)
    file(GLOB_RECURSE inner_sources ${current_dir}/*.cpp)
    message("Adding headers from ${current_dir}: ${inner_headers}")
    message("Adding sources from ${current_dir}: ${inner_sources}")
    set(files ${files} ${inner_headers} ${inner_sources})
endforeach ()
set(logger_source_files ${files} PARENT_SCOPE)
add_library(${PROJECT_NAME} STATIC EXCLUDE_FROM_ALL ${files})

target_compile_definitions(${PROJECT_NAME} PRIVATE
        -DPROJECT_NAME="${external_project_name}"
        )

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME} LINK_PRIVATE fmt)
target_link_libraries(${PROJECT_NAME} LINK_PRIVATE spdlog)

message("Including directory: ${CMAKE_CURRENT_SOURCE_DIR}")
message("Linking private  library: fmt")
message("Linking private  library: spdlog")

function(link_specific_logger external_project_name)
    message(STATUS "Creating specific library for ${external_project_name} project.")
    message("  Building library ${external_project_name}.logging")
    message("Files: " ${files})
    add_library(${external_project_name}.logging STATIC EXCLUDE_FROM_ALL ${logger_source_files})
    target_compile_definitions(${external_project_name}.logging PRIVATE
            -DPROJECT_NAME="${external_project_name}" # Specific definition
            )
    message("  Set PROJECT_NAME=${external_project_name}")
    target_link_libraries(${external_project_name} PRIVATE ${external_project_name}.logging)
    message(STATUS "Creating specific library for ${external_project_name} done.")
endfunction()

message(STATUS "Building ${PROJECT_NAME} finished.")
message("")