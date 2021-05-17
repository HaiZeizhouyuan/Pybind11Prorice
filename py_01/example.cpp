/*************************************************************************
	> File Name: example.cpp
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2021年03月30日 星期二 14时54分06秒
 ************************************************************************/

#include <pybind11/pybind11.h>
namespace py=pybind11;

int add(int i, int j) {
        return i + j;
}

PYBIND11_MODULE(example, m) {
        m.doc() = "pybind11 example plugin"; // optional module docstring
        m.def("add1", &add, "A function which adds two numbers", py::arg("i") = 1, py::arg("j") = 2); 
}

int main() {
 
 
    return 0;
}
