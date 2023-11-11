cmake_minimum_required(VERSION 3.18)
project(SpdlogHelper)

include(cmake/module_define.cmake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -fPIC)

set(SPDLOG_INSTALL OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_EXAMPLE OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_BENCH OFF CACHE BOOL "" FORCE)

add_compile_definitions(ENABLE_SPDLOG)

set(modules example helper spdlog)
foreach(item ${modules})
    add_subdirectory(${item})
endforeach()