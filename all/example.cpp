/*************************************************************************
  > File Name: example.cpp
  > Author: zhouyuan
  > Mail: 3294207721@qq.com 
  > Created Time: 一  5/17 23:28:48 2021
 ************************************************************************/
#include <iostream>
#include <pybind11/pybind11.h>
namespace py = pybind11;
using std::cout;
using std::endl;

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
        People(const std::string &name, int age) : name(name), age(age){}
        std::string getName() { return name; }
        void setName(const std::string& name_) { name = name_; }
        void set(const std::string &name_) { name = name_; }
        void set(int age_)  { age = age_; }
        virtual void eat() = 0;
        virtual void drink(const std::string& name_) { cout << "I like drink with"  << name_ << endl; }

        virtual ~People() {}
    private:
        std::string name;
        int age;
};
template <class PeopleBase = People>  class PyPeople:public PeopleBase {
    public:
        using PeopleBase::PeopleBase;
        void eat() override{
            PYBIND11_OVERRIDE_PURE (
                void,
                PeopleBase,
                eat,
            );
        }
        void drink(const std::string& name_) override {
            PYBIND11_OVERRIDE_PURE (
                void,
                PeopleBase,
                drink,
                name_
            );
        }
};


class Man: public  People {
    public:
        enum Kind {
           Dog = 0,
           Cat
        };
        Man(const std::string &name, int age, Kind type): People(name, age), type(type) {}
        void run() {
            std::cout << "I can run" << std::endl;
        }

        void eat() override{
                cout << "I like eat apple" << endl;
        }

      /*  void drink(const std::string &name_) override {
                cout << "I like drink milk with " << name_ << endl;
        }
*/
        Kind type;
    private:
        std::string name;
        int age;
};

template <class ManBase = Man> 
class PyMan:public  PyPeople<ManBase>{
public:
    using PyPeople<ManBase>::PyPeople;
    void eat()  override {
            PYBIND11_OVERRIDE_PURE (
                void,
                ManBase, 
                eat,

            );
    }
    void drink(const  std::string &name_) override {
        PYBIND11_OVERRIDE_PURE(
            void,
            ManBase,
            drink,
            name_
        );

    }

};

class JK :public Man {};



//注：对于有多个构造函数， 只需使用.def(py::init<...>())语法一个一个地声明
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
    py::class_<People,PyPeople<>> people(m, "People");
    people.def(py::init<const std::string &, int>())
        .def_property("name", &People::getName, &People::setName)
        .def("set", static_cast<void (People::*)(int)>(&People::set),"Overloaded set the pet's age")//c++11 overloaded
        .def("set", static_cast<void (People::*)(const std::string&)>(&People::set),  "Overloaded set the pet's name");//c++11 overloaded
        //template<typename... Args>
        //using overload_cast_ = pybid11::detail::overload_cast_impl<Args...>;//只有c++11， 但想用overload_cast
       // .def("set", py::overload_cast<int>(&People::set)).//根据参数类型推导返回类型和类， c++14 overloaded
       // def("set", py::overload_cast<const std::string &>(&People::set))
       // .def();
    py::class_<Man, People, PyMan<>> man(m, "Man");
    man.def(py::init<const std::string &, int, Man::Kind >())
        .def("run", &Man::run)
        .def_readwrite("type", &Man::type)
        .def("eat", &People::eat);
    py::enum_<Man::Kind>(m, "Kind")
        .def("Dog", Man::Kind::Dog)
        .def("Cat", Man::Kind::Cat);
        //.export_values();//可用Man.Kind__members__查看属性,c++14
    py::class_<JK,Man,  PyMan<JK>> jk(m, "JK");
    

}
