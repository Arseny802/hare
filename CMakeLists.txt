cmake_minimum_required(VERSION 3.15)
project(hare VERSION 0.0.1 LANGUAGES CXX)

if ("${CMAKE_PROJECT_NAME}" STREQUAL "${PROJECT_NAME}")
  set(HARE_IS_SUBPROJECT OFF)
else()
  set(HARE_IS_SUBPROJECT ON)
endif()

if (NOT HARE_IS_SUBPROJECT)
  message(STATUS "-- -- -- -- -- -- -- -- -- -- -- -- -- -- --")
  message(STATUS "BUILD_TOOL_TYPE_NAME: ${BUILD_TOOL_TYPE_NAME}")
  set(CMAKE_BINARY_DIR "${PROJECT_SOURCE_DIR}/bin/${BUILD_TOOL_TYPE_NAME}")

  message("Set CMAKE_LINKER_FLAGS: ${CMAKE_LINKER_FLAGS}")
  message("Set CMAKE_CXX_STANDARD: ${CMAKE_CXX_STANDARD}")
  message("Generator: ${CMAKE_GENERATOR}")
  message("Build tool: ${CMAKE_BUILD_TOOL}")
  message("Build type: ${CMAKE_BUILD_TYPE}")
  message("Build directory: ${CMAKE_BINARY_DIR}")

  SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} CACHE PATH "Single Directory for all")
  SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} CACHE PATH "Single Directory for all")
  SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} CACHE PATH "Single Directory for all")
  SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR} CACHE PATH "Single Directory for all")
  SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR} CACHE PATH "Single Directory for all")
  SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR} CACHE PATH "Single Directory for all")
  SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR} CACHE PATH "Single Directory for all")
  SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR} CACHE PATH "Single Directory for all")
  SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR} CACHE PATH "Single Directory for all")

  # Set default compile flags for GCC
  if (CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "GCC detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -pipe -pedantic -Wall -Wextra -Wcast-align -Wcast-qual")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wchar-subscripts -Wformat-nonliteral -Wmissing-declarations")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpointer-arith -Wredundant-decls -Wundef -Wwrite-strings")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-pragmas -pthread")
  elseif (MSVC) # building on visual c++
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
  endif (CMAKE_COMPILER_IS_GNUCXX)
endif(NOT HARE_IS_SUBPROJECT)

find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

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
add_library(${PROJECT_NAME} STATIC ${HARE_HEADERS} ${HARE_SOURCES})

target_precompile_headers(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/hare/hare.hpp
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/hare/hlogger.h
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  spdlog::spdlog
  fmt::fmt
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
)

if (NOT HARE_IS_SUBPROJECT)
  add_subdirectory(example)
  #add_subdirectory(tests)
endif(NOT HARE_IS_SUBPROJECT)
