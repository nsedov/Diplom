#include <boost/python.hpp>
#include <NTL/GF2.h>

void define_GF2 {
    using namespace boost::python;
    class_<GF2>("GF2", init<>())
        .def(init<const ZZ&>())
        .def("swap", &ZZ::swap)
}