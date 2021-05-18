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

//关键字
int mul(int x, int y)  {
    return x * y;
}

//默认参数
int sub(int x = 10, int y = 6){
    return x - y;
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
    m.attr("autor_name") = "zy";
    m.attr("autor_age") = 25;
    py::object hello_words = py::cast("welcome");
    m.attr("hi") = hello_words;
    m.def("add", &add, "A function which adds two numbers");
    m.def("mul", &mul, "Keyword arguments", py::arg("x"), py::arg("y"));
    m.def("sub", &sub, "Default arguments", py::arg("x") = 10, py::arg("y") = 6);
    py::class_<Cat>(m, "Cat")
        .def(py::init<const std::string &>())
        .def("setName", &Cat::setName)
        .def("getName", &Cat::getName);
}
