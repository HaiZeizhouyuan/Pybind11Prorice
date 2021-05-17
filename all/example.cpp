/*************************************************************************
	> File Name: example.cpp
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 一  5/17 23:28:48 2021
 ************************************************************************/
#include <pybind11/pybind11.h>
namespace py = pybind11;

//example.add(x, y)
int add(int x, int y) {
    return x + y;
}

class Cat {
    public:
       Cat(const std::string &name) :_name(name){}
       void setName(const std::string &name) {
            this->_name = name;
       }

       const std::string &getName() const {
            return _name;
       }
    private:
       std::string _name;
};

PYBIND11_MODULE(example, m) {
    m.def("add", &add, "A function which adds two numbers");
    py::class_<Cat>(m, "Cat")
        .def(py::init<const std::string &>())
        .def("setName", &Cat::setName)
        .def("getName", &Cat::getName);
}
