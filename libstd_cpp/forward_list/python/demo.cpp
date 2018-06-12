#include <boost/python.hpp>

#include <string>
#include "forward_list.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(demo)
{
    class_<Hx::forward_list<double> >("slist")
		.def("push_front", &Hx::forward_list<double>::push_front)
        .def("__iter__", boost::python::iterator<Hx::forward_list<double> >())
        ;
}
