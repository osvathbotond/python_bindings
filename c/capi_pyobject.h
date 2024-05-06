#include "capi_quaternion.h"

static PyTypeObject QuaternionType;

static PyObject* Quaternion_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    Quaternion *self;
    self = (Quaternion*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->a = 0.0;
        self->b = 0.0;
        self->c = 0.0;
        self->d = 0.0;
    }
    return (PyObject *)self;
}

static int Quaternion_init(Quaternion* self, PyObject* args, PyObject* kwds) {
    double a, b, c, d;
    if (!PyArg_ParseTuple(args, "dddd", &a, &b, &c, &d)) {
        return -1;
    }
    self->a = a;
    self->b = b;
    self->c = c;
    self->d = d;
    return 0;
}

static PyObject* Quaternion_getA(Quaternion* self, void* closure) {
    return PyFloat_FromDouble(self->a);
}

static int Quaternion_setA(Quaternion* self, PyObject* value, void* closure) {
    if (!PyNumber_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "The 'a' attribute must be set to a number");
        return -1;
    }
    self->a = PyFloat_AsDouble(PyNumber_Float(value));
    return 0;
}

static PyObject* Quaternion_getB(Quaternion* self, void* closure) {
    return PyFloat_FromDouble(self->b);
}

static int Quaternion_setB(Quaternion* self, PyObject* value, void* closure) {
    if (!PyNumber_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "The 'b' attribute must be set to a number");
        return -1;
    }
    self->b = PyFloat_AsDouble(PyNumber_Float(value));
    return 0;
}

static PyObject* Quaternion_getC(Quaternion* self, void* closure) {
    return PyFloat_FromDouble(self->c);
}

static int Quaternion_setC(Quaternion* self, PyObject* value, void* closure) {
    if (!PyNumber_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "The 'c' attribute must be set to a number");
        return -1;
    }
    self->c = PyFloat_AsDouble(PyNumber_Float(value));
    return 0;
}

static PyObject* Quaternion_getD(Quaternion* self, void* closure) {
    return PyFloat_FromDouble(self->d);
}

static int Quaternion_setD(Quaternion* self, PyObject* value, void* closure) {
    if (!PyNumber_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "The 'd' attribute must be set to a number");
        return -1;
    }
    self->d = PyFloat_AsDouble(PyNumber_Float(value));
    return 0;
}

static PyObject* Quaternion_getAt(Quaternion* self, Py_ssize_t index) {
    if (index < 0 || index >= 4) {
        PyErr_SetString(PyExc_IndexError, "Index out of range");
        return NULL;
    }
    switch (index) {
        case 0:
            return PyFloat_FromDouble(self->a);
        case 1:
            return PyFloat_FromDouble(self->b);
        case 2:
            return PyFloat_FromDouble(self->c);
        case 3:
            return PyFloat_FromDouble(self->d);
    }
    return NULL;
}

static int Quaternion_setAt(Quaternion* self, Py_ssize_t index, PyObject* value) {
    if (index < 0 || index >= 4) {
        PyErr_SetString(PyExc_IndexError, "Index out of range");
        return -1;
    }
    if (!PyNumber_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "Value must be a number");
        return -1;
    }
    double val = PyFloat_AsDouble(PyNumber_Float(value));
    switch (index) {
        case 0:
            self->a = val;
            break;
        case 1:
            self->b = val;
            break;
        case 2:
            self->c = val;
            break;
        case 3:
            self->d = val;
            break;
    }
    return 0;
}

static PyObject* Quaternion_getData(Quaternion* self, void* closure) {
    return Py_BuildValue("dddd", self->a, self->b, self->c, self->d);
}

static PyObject* Quaternion_toString(Quaternion* self) {
    char output[250];
    snprintf(output, sizeof(output), "Quaternion(%.15g, %.15g, %.15g, %.15g)", self->a, self->b, self->c, self->d);
    return PyUnicode_FromString(output);
}

static PyObject* Quaternion_add(Quaternion* self, Quaternion* other) {
    Quaternion* result = (Quaternion*)QuaternionType.tp_alloc(&QuaternionType, 0);
    if (result == NULL) {
        return NULL;
    }
    _Quaternion_add(self, other, result);
    return (PyObject*)result;
}

static PyObject* Quaternion_sub(Quaternion* self, Quaternion* other) {
    Quaternion* result = (Quaternion*)QuaternionType.tp_alloc(&QuaternionType, 0);
    if (result == NULL) {
        return NULL;
    }
    _Quaternion_sub(self, other, result);
    return (PyObject*)result;
}

static PyObject* Quaternion_mul(PyObject* left, PyObject* right) {
    if (PyObject_TypeCheck(left, &QuaternionType) && PyObject_TypeCheck(right, &QuaternionType)) {
        Quaternion* result = (Quaternion*)QuaternionType.tp_alloc(&QuaternionType, 0);
        if (result == NULL) {
            return NULL;
        }
        _Quaternion_mul((Quaternion*)left, (Quaternion*)right, result);
        return (PyObject*)result;
    } else if (PyObject_TypeCheck(left, &QuaternionType) && PyNumber_Check(right)) {
        double scalar = PyFloat_AsDouble(PyNumber_Float(right));
        Quaternion* result = (Quaternion*)QuaternionType.tp_alloc(&QuaternionType, 0);
        if (result == NULL) {
            return NULL;
        }
        _Quaternion_mulScalar((Quaternion*)left, scalar, result);
        return (PyObject*)result;
    } else if (PyNumber_Check(left) && PyObject_TypeCheck(right, &QuaternionType)) {
        double scalar = PyFloat_AsDouble(PyNumber_Float(left));
        Quaternion* result = (Quaternion*)QuaternionType.tp_alloc(&QuaternionType, 0);
        if (result == NULL) {
            return NULL;
        }
        _Quaternion_mulScalar((Quaternion*)right, scalar, result);
        return (PyObject*)result;
    }
    PyErr_SetString(PyExc_TypeError, "Unsupported operand type for *");
    return NULL;
}

static PyObject* Quaternion_div(PyObject* left, PyObject* right) {
    if (PyObject_TypeCheck(left, &QuaternionType) && PyObject_TypeCheck(right, &QuaternionType)) {
        Quaternion* result = (Quaternion*)QuaternionType.tp_alloc(&QuaternionType, 0);
        if (result == NULL) {
            return NULL;
        }
        _Quaternion_div((Quaternion*)left, (Quaternion*)right, result);
        return (PyObject*)result;
    } else if (PyObject_TypeCheck(left, &QuaternionType) && PyNumber_Check(right)) {
        double scalar = PyFloat_AsDouble(PyNumber_Float(right));
        Quaternion* result = (Quaternion*)QuaternionType.tp_alloc(&QuaternionType, 0);
        if (result == NULL) {
            return NULL;
        }
        _Quaternion_divScalarLeft((Quaternion*)left, scalar, result);
        return (PyObject*)result;
    } else if (PyNumber_Check(left) && PyObject_TypeCheck(right, &QuaternionType)) {
        double scalar = PyFloat_AsDouble(PyNumber_Float(left));
        Quaternion* result = (Quaternion*)QuaternionType.tp_alloc(&QuaternionType, 0);
        if (result == NULL) {
            return NULL;
        }
        _Quaternion_divScalarRight((Quaternion*)right, scalar, result);
        return (PyObject*)result;
    }
    PyErr_SetString(PyExc_TypeError, "Unsupported operand type for /");
    return NULL;
}

static PyObject* Quaternion_conjugate(Quaternion* self) {
    Quaternion* result = (Quaternion*)QuaternionType.tp_alloc(&QuaternionType, 0);
    if (result == NULL) {
        return NULL;
    }
    _Quaternion_conjugate(self, result);
    return (PyObject* )result;
}

static PyObject* Quaternion_abs(Quaternion* self) {
    return PyFloat_FromDouble(_Quaternion_norm(self));
}

static PyObject* Quaternion_inverse(Quaternion* self) {
    Quaternion* result = (Quaternion*)QuaternionType.tp_alloc(&QuaternionType, 0);
    if (result == NULL) {
        return NULL;
    }
    _Quaternion_inverse(self, result);
    return (PyObject*)result;
}

static PyObject* Quaternion_normalize(Quaternion* self) {
    Quaternion* result = (Quaternion*)QuaternionType.tp_alloc(&QuaternionType, 0);
    if (result == NULL) {
        return NULL;
    }
    double norm = _Quaternion_norm(self);
    if (norm == 0.0) {
        PyErr_SetString(PyExc_ZeroDivisionError, "Cannot normalize the zero quaternion");
        return NULL;
    }
    _Quaternion_divScalarLeft(self, norm, result);
    return (PyObject*)result;
}

static PyObject* Quaternion_neg(Quaternion* self) {
    Quaternion* result = (Quaternion*)QuaternionType.tp_alloc(&QuaternionType, 0);
    if (result == NULL) {
        return NULL;
    }
    _Quaternion_mulScalar(self, -1.0, result);
    return (PyObject*)result;
}

