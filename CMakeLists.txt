message("")
message("##########################")
message("######## PREBUILD ########")
message("##########################")

# base settings for cmake
cmake_minimum_required(VERSION 3.3)
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
message("Set CMAKE_CXX_STANDARD: 17")
message("")

# cmake build dir & generator
set(bin_dir "${PROJECT_SOURCE_DIR}/bin")
set(third_party_dir ${PROJECT_SOURCE_DIR}/third-party)
message("#########################")
message("######## GENERAL ########")
message("#########################")
message("Generator: ${CMAKE_GENERATOR}")
message("Build tool: ${CMAKE_BUILD_TOOL}")
message("Build type: ${CMAKE_BUILD_TYPE}")
message("Build directory: ${bin_dir}")
message("Third party dir: ${third_party_dir}")

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

# Include fmt project for string formatting.
set(fmt_path "${third_party_dir}/fmt")
message("Loading fmt from '${fmt_path}'...")
add_subdirectory(${fmt_path})
include_directories(${fmt_path}/include)
message("fmt loaded.")

# Include spdlog project for logging.
set(spdlog_path "${third_party_dir}/spdlog")
message("Loading spdlog from '${spdlog_path}'...")
add_subdirectory(${spdlog_path})
include_directories(${spdlog_path}/include)
message("spdlog loaded.")

# Include Google test project for unit tests.
set(googletest_path "${third_party_dir}/googletest")
message("Loading googletest from '${googletest_path}'...")
add_subdirectory(${googletest_path})
include_directories(${googletest_path}/googletest/include)
message("googletest loaded.")

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