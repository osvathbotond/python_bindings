#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "quaternion.hpp"



PYBIND11_MODULE(quaternion, m) {
    pybind11::class_<Quaternion>(m, "Quaternion")
        .def(pybind11::init<double, double, double, double>(), pybind11::arg("a") = 0.0, pybind11::arg("b") = 0.0, pybind11::arg("c") = 0.0, pybind11::arg("d") = 0.0)
        .def("set_at", &Quaternion::setAt)
        .def("get_at", &Quaternion::getAt)
        .def_property("a", &Quaternion::getA, &Quaternion::setA)
        .def_property("b", &Quaternion::getB, &Quaternion::setB)
        .def_property("c", &Quaternion::getC, &Quaternion::setC)
        .def_property("d", &Quaternion::getD, &Quaternion::setD)
        .def_property_readonly("data", [](const Quaternion& q) { auto data = q.getData(); return pybind11::make_tuple(data[0], data[1], data[2], data[3]); })
        .def("__repr__", &Quaternion::toString)
        .def(pybind11::self + pybind11::self)
        .def(pybind11::self - pybind11::self)
        .def(pybind11::self * pybind11::self)
        .def(pybind11::self / pybind11::self)
        .def(pybind11::self == pybind11::self)
        .def(pybind11::self != pybind11::self)
        .def(pybind11::self * double())
        .def(pybind11::self * int())
        .def(pybind11::self / double())
        .def(pybind11::self / int())
        .def(double() * pybind11::self)
        .def(int() * pybind11::self)
        .def(double() / pybind11::self)
        .def(int() / pybind11::self)
        .def(-pybind11::self)
        .def("conjugate", &Quaternion::conjugate)
        .def("normalize", &Quaternion::normalize)
        .def("inverse", &Quaternion::inverse)
        .def("__abs__", &Quaternion::norm)
        ;

}