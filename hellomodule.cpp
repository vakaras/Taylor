#include <iostream>
 
using namespace std;

void swap( int &x, int &y)
{
    int tmp = x;
    x = y;
    y = tmp;
}
 
int &getC() {
  int &c = *(new int);
  return c;
  }

void say_hello(const char* name) {
    getC() = 0;
    int a = 1, b = 2;
    cout << "a = " << a << " b = " << b << endl;
    swap(a, b);
    cout << "a = " << a << " b = " << b << endl;
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
