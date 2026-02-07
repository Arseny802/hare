cmake_minimum_required(VERSION 3.15)
project(hare VERSION 0.0.1 LANGUAGES CXX)

find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

option(HARE_ENABLE_STD_FORMAT "Enable std format library (or use fmt)" OFF)
option(HARE_USE_IMPLEMENTATION_SPDLOG "Use spdlog inner implementation" ON)

file(GLOB_RECURSE HARE_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/details/*cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*cc)
file(GLOB_RECURSE HARE_HEADERS
  ${CMAKE_CURRENT_SOURCE_DIR}/include/*h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/*hpp)
add_library(${PROJECT_NAME} STATIC ${HARE_HEADERS} ${HARE_SOURCES})

target_precompile_headers(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/hare/config_custom.h
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/hare/config_default.h
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/hare/config.h
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/hare/hare_loggers.h
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/hare/hlog.hpp
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

if (HARE_ENABLE_STD_FORMAT)
  target_compile_definitions(${PROJECT_NAME}
    PUBLIC HARE_ENABLE_STD_FORMAT
  )
endif(HARE_ENABLE_STD_FORMAT)

if (HARE_USE_IMPLEMENTATION_SPDLOG)
  target_compile_definitions(${PROJECT_NAME}
    PUBLIC HARE_USE_IMPLEMENTATION_SPDLOG
  )
endif(HARE_USE_IMPLEMENTATION_SPDLOG)

if ("${CMAKE_PROJECT_NAME}" STREQUAL "${PROJECT_NAME}")
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
  add_subdirectory(example)
  #add_subdirectory(tests)
endif("${CMAKE_PROJECT_NAME}" STREQUAL "${PROJECT_NAME}")
