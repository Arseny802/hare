cmake_minimum_required(VERSION 3.15)
project(hare VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS}")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS_INIT} -fPIC")
set(CMAKE_BINARY_DIR "${PROJECT_SOURCE_DIR}/bin")

message("Set CMAKE_LINKER_FLAGS: ${CMAKE_LINKER_FLAGS}")
message("Set CMAKE_CXX_STANDARD: ${CMAKE_CXX_STANDARD}")
message("Generator: ${CMAKE_GENERATOR}")
message("Build tool: ${CMAKE_BUILD_TOOL}")
message("Build type: ${CMAKE_BUILD_TYPE}")
message("Build directory: ${CMAKE_BINARY_DIR}")

find_package(spdlog CONFIG REQUIRED)

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    CACHE PATH "Single Directory for all")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    CACHE PATH "Single Directory for all")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    CACHE PATH "Single Directory for all")

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

file(GLOB_RECURSE HARE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/details/*cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*cc)
file(GLOB_RECURSE HARE_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*hpp)
message(${HARE_HEADERS})
add_library(${PROJECT_NAME} STATIC ${HARE_HEADERS} ${HARE_SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(${PROJECT_NAME} PRIVATE
    spdlog::spdlog
    fmt::fmt)

if (WIN32) # building on windows
    #add_subdirectory(win__special_sources)
elseif (MSVC) # building on visual c++
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    #add_subdirectory(win_msvc__special_sources)
elseif (UNIX) # building on unix (mac, linux)
    #add_subdirectory(unix__special_sources)
endif (WIN32)

add_subdirectory(example)
#add_subdirectory(tests)