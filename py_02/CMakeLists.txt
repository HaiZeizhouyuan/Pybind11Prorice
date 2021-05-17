cmake_minimum_required(VERSION 2.9...3.20)
project(example2)

set(PYBIND11_DIR "/Users/zhiyi/Pybind11Prorice/pybind11/")
if (PYBIND11_DIR)
    set(PYBIND11_ROOT_DIR ${PYBIND11_DIR})
else()
    set(PYBIND11_ROOT_DIR $ENV{PYBIND11_DIR})
endif()
message(STATUS "Find Pybind11: ${PYBIND11_ROOT_DIR}")
unset(PYBIND11_DIR)
add_subdirectory(${PYBIND11_ROOT_DIR} "./pybind11")
set(PYBIND11_CPP_STANDARD -std=c++14)

pybind11_add_module(example2 example2.cpp)

