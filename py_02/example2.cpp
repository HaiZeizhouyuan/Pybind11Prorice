/*************************************************************************
	> File Name: example2.cpp
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 六  4/ 3 01:05:17 2021
 ************************************************************************/
#include <pybind11/pybind11.h>
namespace py = pybind11;

PYBIND11_MODULE(example2, m){
    m.attr("the_answer") = 42;
    py::object world = py::cast("World");
    m.attr("What") = world;
}
