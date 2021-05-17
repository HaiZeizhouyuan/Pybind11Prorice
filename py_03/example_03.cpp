/*************************************************************************
	> File Name: example_03.cpp
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 日  4/ 4 11:30:57 2021
 ************************************************************************/
#include<pybind11/pybind11.h>
namespace py=pybind11;

struct Pet {
    Pet(const std::string &name):name(name) {}
    void setName(const std::string &name_) { name = name_;}
    const std::string &getName() const { return name; }
    std::string name;
};

PYBIND11_MODULE(example_03, m){
    py::class_<Pet>(m, "Pet")
        .def(py::init<const std::string &>())
        .def("setName", &Pet::setName)
        .def("getName", &Pet::getName);
}
