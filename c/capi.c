#include "capi_pyobject.h"

static PyGetSetDef Quaternion_getsetters[] = {
    {"a", (getter)Quaternion_getA, (setter)Quaternion_setA, "a component", NULL},
    {"b", (getter)Quaternion_getB, (setter)Quaternion_setB, "b component", NULL},
    {"c", (getter)Quaternion_getC, (setter)Quaternion_setC, "c component", NULL},
    {"d", (getter)Quaternion_getD, (setter)Quaternion_setD, "d component", NULL},
    {"data", (getter)Quaternion_getData, NULL, "data", NULL},
    {NULL}  /* Sentinel */
};

static PyMethodDef Quaternion_methods[] = {
    {"set_at", (PyCFunction)Quaternion_setAt, METH_VARARGS, "Set the value at the given index."},
    {"get_at", (PyCFunction)Quaternion_getAt, METH_VARARGS, "Get the value at the given index."},
    {"conjugate", (PyCFunction)Quaternion_conjugate, METH_NOARGS, "Conjugate the quaternion."},
    {"normalize", (PyCFunction)Quaternion_normalize, METH_NOARGS, "Normalize the quaternion."},
    {"inverse", (PyCFunction)Quaternion_inverse, METH_NOARGS, "Return the inverse of the quaternion."},
    {NULL}  /* Sentinel */
};

static PyNumberMethods Quaternion_number_methods = {
    (binaryfunc)Quaternion_add,     /* nb_add */
    (binaryfunc)Quaternion_sub,     /* nb_subtract */
    (binaryfunc)Quaternion_mul,     /* nb_multiply */
    0,                              /* nb_remainder */
    0,                              /* nb_divmod */
    0,                              /* nb_power */
    (unaryfunc)Quaternion_neg,      /* nb_negative */
    0,                              /* nb_positive */
    (unaryfunc)Quaternion_abs,      /* nb_absolute */
    0,                              /* nb_bool */
    0,                              /* nb_invert */
    0,                              /* nb_lshift */
    0,                              /* nb_rshift */
    0,                              /* nb_and */
    0,                              /* nb_xor */
    0,                              /* nb_or */
    0,                              /* nb_int */
    NULL,                           /* nb_reserved */
    0,                              /* nb_float */
    0,                              /* nb_inplace_add */
    0,                              /* nb_inplace_subtract */
    0,                              /* nb_inplace_multiply */
    0,                              /* nb_inplace_remainder */
    0,                              /* nb_inplace_power */
    0,                              /* nb_inplace_lshift */
    0,                              /* nb_inplace_rshift */
    0,                              /* nb_inplace_and */
    0,                              /* nb_inplace_xor */
    0,                              /* nb_inplace_or */
    0,                              /* nb_floor_divide */
    (binaryfunc)Quaternion_div,     /* nb_true_divide */
    0,                              /* nb_inplace_floor_divide */
    0,                              /* nb_inplace_true_divide */
    0,                              /* nb_index */
};

static PyTypeObject QuaternionType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "quaternion.Quaternion",        /* tp_name */
    sizeof(Quaternion),             /* tp_basicsize */
    0,                              /* tp_itemsize */
    0,                              /* tp_dealloc */
    0,                              /* tp_print */
    0,                              /* tp_getattr */
    0,                              /* tp_setattr */
    NULL,                           /* tp_reserved */
    (reprfunc)Quaternion_toString,  /* tp_repr */
    &Quaternion_number_methods,     /* tp_as_number */
    0,                              /* tp_as_sequence */
    0,                              /* tp_as_mapping */
    0,                              /* tp_hash  */
    0,                              /* tp_call */
    0,                              /* tp_str */
    0,                              /* tp_getattro */
    0,                              /* tp_setattro */
    0,                              /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,             /* tp_flags */
    "Quaternion class",             /* tp_doc */
    0,		                      /* tp_traverse */
    0,		                      /* tp_clear */
    0,		                      /* tp_richcompare */
    0,		                      /* tp_weaklistoffset */
    0,		                      /* tp_iter */
    0,		                      /* tp_iternext */
    Quaternion_methods,             /* tp_methods */
    0,                              /* tp_members */
    Quaternion_getsetters,          /* tp_getset */
    0,                              /* tp_base */
    0,                              /* tp_dict */
    0,                              /* tp_descr_get */
    0,                              /* tp_descr_set */
    0,                              /* tp_dictoffset */
    (initproc)Quaternion_init,      /* tp_init */
    0,                              /* tp_alloc */
    Quaternion_new,                 /* tp_new */
};

static PyModuleDef quaternion_module = {
    PyModuleDef_HEAD_INIT,
    "quaternion",
    "A simple quaternion module",
    -1,
    NULL, NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC PyInit_quaternion(void) {
    PyObject *m;
    if (PyType_Ready(&QuaternionType) < 0)
        return NULL;

    m = PyModule_Create(&quaternion_module);
    if (m == NULL)
        return NULL;

    Py_INCREF(&QuaternionType);
    PyModule_AddObject(m, "Quaternion", (PyObject *)&QuaternionType);
    return m;
}
