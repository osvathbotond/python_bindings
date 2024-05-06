#include <Python.h>
#include <boost/python.hpp>

#include "quaternion.hpp"

BOOST_PYTHON_MODULE(quaternion) {
    boost::python::class_<Quaternion>("Quaternion", boost::python::init<double, double, double, double>((boost::python::arg("a") = 0.0, boost::python::arg("b") = 0.0, boost::python::arg("c") = 0.0, boost::python::arg("d") = 0.0)))
        .def("set_at", &Quaternion::setAt)
        .def("get_at", &Quaternion::getAt)
        .add_property("a", &Quaternion::getA, &Quaternion::setA)
        .add_property("b", &Quaternion::getB, &Quaternion::setB)
        .add_property("c", &Quaternion::getC, &Quaternion::setC)
        .add_property("d", &Quaternion::getD, &Quaternion::setD)
        .add_property("data", &Quaternion::getData)
        .def("__repr__", &Quaternion::toString)
        .def(boost::python::self + boost::python::self)
        .def(boost::python::self - boost::python::self)
        .def(boost::python::self * boost::python::self)
        .def(boost::python::self / boost::python::self)
        .def(boost::python::self == boost::python::self)
        .def(boost::python::self != boost::python::self)
        .def(boost::python::self * double())
        .def(boost::python::self * int())
        .def(boost::python::self / double())
        .def(boost::python::self / int())
        .def(double() * boost::python::self)
        .def(int() * boost::python::self)
        .def(double() / boost::python::self)
        .def(int() / boost::python::self)
        .def(-boost::python::self)
        .def("conjugate", &Quaternion::conjugate)
        .def("normalize", &Quaternion::normalize)
        .def("inverse", &Quaternion::inverse)
        .def("__abs__", &Quaternion::norm)
        ;
}