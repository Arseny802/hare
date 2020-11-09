message("")
message("##########################")
message("######## PREBUILD ########")
message("##########################")

# base settings for cmake
cmake_minimum_required(VERSION 3.15)
set(IS_SUBPROJECT OFF)
if (${SOLUTION_NAME})
    set(IS_SUBPROJECT ON)
    set(MAIN_SOLUTION_NAME ${SOLUTION_NAME})
endif (${SOLUTION_NAME})
set(SOLUTION_NAME hare)
project(${SOLUTION_NAME} VERSION 1.0.0 LANGUAGES CXX)

# temporary global linking
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS}")
set(CMAKE_CXX_STANDARD 17)

message("Set SOLUTION_NAME: ${SOLUTION_NAME}")
message("Set CMAKE_LINKER_FLAGS: ${CMAKE_LINKER_FLAGS}")
message("Set CMAKE_CXX_STANDARD: 20")
message("")

# cmake build dir & generator
set(bin_dir "${PROJECT_SOURCE_DIR}/bin")
message("#########################")
message("######## GENERAL ########")
message("#########################")
message("Generator: ${CMAKE_GENERATOR}")
message("Build tool: ${CMAKE_BUILD_TOOL}")
message("Build type: ${CMAKE_BUILD_TYPE}")
message("Build directory: ${bin_dir}")

# set output folders
# libs
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${bin_dir}
        CACHE PATH
        "Single Directory for all"
        )
# executables
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${bin_dir}
        CACHE PATH
        "Single Directory for all"
        )
# libs .a
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
        ${bin_dir}
        CACHE PATH
        "Single Directory for all"
        )

message("")
message("#########################")
message("###### CUSTOM ARGS ######")
message("#########################")

set(CMAKE_CXX_FLAGS                " ${CMAKE_CXX_FLAGS_INIT} -std=c++17 -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG          "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -DDEBUG")

# Set default compile flags for GCC
if (CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "GCC detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif (CMAKE_COMPILER_IS_GNUCXX)
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    message(STATUS "Build type is debug - setting compile arg \"-D _DEBUG\".")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D _DEBUG")
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(STATUS "Build type is relese - setting compile arg \"-D _RELEASE\".")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D _RELEASE")
endif()

message("")
message("###################################")
message("######## EXTERNAL PROJECTS ########")
message("###################################")

set(CONAN_DISABLE_CHECK_COMPILER True)
if(NOT EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    execute_process(COMMAND CMD "conan install .")
endif()
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

message("")
message("#############################")
message("########## SOURCES ##########")
message("#############################")
# base libs
add_subdirectory(src/logging)

if (NOT ${IS_SUBPROJECT}) # building example target
    add_subdirectory(src/example)
    enable_testing()
endif (NOT ${IS_SUBPROJECT})

if(CMAKE_TESTING_ENABLED)
    add_subdirectory(tests EXCLUDE_FROM_ALL)
    set(PROJECT_TESTS ${CMAKE_PROJECT_NAME}.tests)
    add_test(tests/${PROJECT_TESTS} tests/${PROJECT_TESTS})
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)
    add_dependencies(check ${PROJECT_TESTS})
endif()

#target_link_libraries(${CMAKE_PROJECT_NAME} ${CONAN_LIBS})

# checking build type on platform
message("")
message("#############################")
message("###### OS DEPENDENCIES ######")
message("#############################")
if (WIN32) # building on windows
    #add_subdirectory(win__special_sources)
elseif (MSVC) # building on visual c++
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    #add_subdirectory(win_msvc__special_sources)
elseif (UNIX) # building on unix (mac, linux)
    #add_subdirectory(unix__special_sources)
endif (WIN32)
message("")
message("##########################")
message("######### FINISH #########")
message("##########################")

if (${IS_SUBPROJECT})
    set(SOLUTION_NAME ${MAIN_SOLUTION_NAME})
endif(${IS_SUBPROJECT})