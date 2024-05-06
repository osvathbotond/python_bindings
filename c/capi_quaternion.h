#include <Python.h>

typedef struct Quaternion {
    PyObject_HEAD

    double a;
    double b;
    double c;
    double d;
} Quaternion;

static inline void _Quaternion_add(Quaternion* left, Quaternion* right, Quaternion* result) {
    result->a = left->a + right->a;
    result->b = left->b + right->b;
    result->c = left->c + right->c;
    result->d = left->d + right->d;
}

static inline void _Quaternion_sub(Quaternion* left, Quaternion* right, Quaternion* result) {
    result->a = left->a - right->a;
    result->b = left->b - right->b;
    result->c = left->c - right->c;
    result->d = left->d - right->d;
}

static inline void _Quaternion_mul(Quaternion* left, Quaternion* right, Quaternion* result) {
    double a = left->a * right->a - left->b * right->b - left->c * right->c - left->d * right->d;
    double b = left->a * right->b + left->b * right->a + left->c * right->d - left->d * right->c;
    double c = left->a * right->c - left->b * right->d + left->c * right->a + left->d * right->b;
    double d = left->a * right->d + left->b * right->c - left->c * right->b + left->d * right->a;

    result->a = a;
    result->b = b;
    result->c = c;
    result->d = d;
}

static inline void _Quaternion_mulScalar(Quaternion* quaternion, double scalar, Quaternion* result) {
    result->a = quaternion->a * scalar;
    result->b = quaternion->b * scalar;
    result->c = quaternion->c * scalar;
    result->d = quaternion->d * scalar;
}

static inline double _Quaternion_normSquared(Quaternion* self) {
    return self->a * self->a + self->b * self->b + self->c * self->c + self->d * self->d;
}

static inline double _Quaternion_norm(Quaternion* self) {
    return sqrt(_Quaternion_normSquared(self));
}

static inline void _Quaternion_conjugate(Quaternion* self, Quaternion* result) {
    result->a = self->a;
    result->b = -self->b;
    result->c = -self->c;
    result->d = -self->d;
}

static inline void _Quaternion_divScalarLeft(Quaternion* quaternion, double scalar, Quaternion* result) {
    result->a = quaternion->a / scalar;
    result->b = quaternion->b / scalar;
    result->c = quaternion->c / scalar;
    result->d = quaternion->d / scalar;
}

static inline void _Quaternion_inverse(Quaternion* self, Quaternion* result) {
    double normSquared = _Quaternion_normSquared(self);
    _Quaternion_conjugate(self, result);
    _Quaternion_divScalarLeft(result, normSquared, result);
}

static inline void _Quaternion_div(Quaternion* left, Quaternion* right, Quaternion* result) {
    _Quaternion_inverse(right, result);
    _Quaternion_mul(left, result, result);
}

static inline void _Quaternion_divScalarRight(Quaternion* quaternion, double scalar, Quaternion* result) {
    _Quaternion_inverse(quaternion, result);
    _Quaternion_mulScalar(result, scalar, result);
}
