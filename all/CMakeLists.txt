cmake_minimum_required(VERSION 2.8...3.12)
set(project_name "example")
project(${project_name})

#find pybind11

find_package(pybind11)
if (pybind11_FOUND)
    set(PYBIND11_ROOT_DIR ${pybind11_FOUND})
else() 
    set(PYBIND11_ROOT_DIR $ENV{pybind11_FOUND})
endif()

message(STATUS "Find Pybind11: ${pybind11_FOUND}")

set(PYBIND11_CPP_STANDARD -std=c++14)

pybind11_add_module(${project_name} example.cpp)

