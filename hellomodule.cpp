#include <iostream>
 
using namespace std;
 
void say_hello(const char* name) {
    cout << "Hello " <<  name << "!\n";
}

struct World
{
    void set(std::string msg) { this->msg = msg; }
    std::string greet() { return msg; }
    std::string msg;
};
 
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python.hpp>
using namespace boost::python;
 
BOOST_PYTHON_MODULE(hello)
{
    def("say_hello", say_hello);
    class_<World>("World")
        .def("greet", &World::greet)
        .def("set", &World::set)
    ;
}
