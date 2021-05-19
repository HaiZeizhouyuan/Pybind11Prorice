/*************************************************************************
  > File Name: example.cpp
  > Author: zhouyuan
  > Mail: 3294207721@qq.com 
  > Created Time: 一  5/17 23:28:48 2021
 ************************************************************************/
#include <iostream>
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
        Cat(const std::string &name, const std::string &iddress, int age) :_name(name), _iddress(iddress), _age(age){}
        void setName(const std::string &name) {
            this->_name = name;
        }

        const std::string &getName() const {
            return _name;
        }

        void hello() {
            std::cout << "Hi!" << std::endl;
        }
        std::string _iddress;
        int _age;
    private:
        std::string _name;
        static int sum;
};

class People {
    public:
        People(const std::string &name) : name(name){}
        std::string name;
};

class Man: public  People {
    public:
        Man(const std::string &name): People(name) {}
        void run() {
            std::cout << "I can run" << std::endl;
        }
};

PYBIND11_MODULE(example, m) {
    m.attr("autor_name") = "zy";
    m.attr("autor_age") = 25;
    py::object hello_words = py::cast("welcom");
    m.attr("hi") = hello_words;
    m.def("add", &add, "A function which adds two numbers");
    m.def("mul", &mul, "Keyword arguments", py::arg("x"), py::arg("y"));
    m.def("sub", &sub, "Default arguments", py::arg("x") = 10, py::arg("y") = 6);
    py::class_<Cat>(m, "Cat",py::dynamic_attr())
        .def(py::init<const std::string &, const std::string &, int>())
        .def("hello",&Cat::hello, "usually func bind")
        .def_readwrite("age", &Cat::_age, "set and get public variable use def_readwrite")
        .def_property("_name", &Cat::getName, &Cat::setName, "set and get private variable use def_property")
        //.def_property_readonly_static("sum", [](py::object ) { return Cat(); })
        .def("__repr__",
                [](const Cat &a) {
                return "<example Cat address'" + a._iddress  + "'>'";
                }
            );
    py::class_<People>(m, "People")
        .def(py::init<const std::string &>())
        .def_readwrite("name", &People::name);
    py::class_<Man, People>(m, "Man")
        .def(py::init<const std::string &>())
        .def("run", &Man::run);
}
