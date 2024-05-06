import unittest

class QuaternionTest(unittest.TestCase):
    Quaternion = None
    module_name = None

    @classmethod
    def setQuaternion(cls, Quaternion, module_name):
        cls.Quaternion = Quaternion
        cls.module_name = module_name
    
    @classmethod
    def setUpClass(cls):
        middle_text = f" Testing \"{cls.module_name}\" "
        n1 = (80 - len(middle_text)) // 2
        n2 = 80 - len(middle_text) - n1
        print("=" * n1 + middle_text + "=" * n2)

    def test_addition(self):
        q1 = self.Quaternion(1, 2, 3, 4)
        q2 = self.Quaternion(5, 6, 7, 8)
        result = q1 + q2
        self.assertAlmostEqual(result, self.Quaternion(6, 8, 10, 12))

    def test_subtraction(self):
        q1 = self.Quaternion(1, 2, 3, 4)
        q2 = self.Quaternion(5, 6, 7, 8)
        result = q1 - q2
        self.assertAlmostEqual(result, self.Quaternion(-4, -4, -4, -4))

    def test_multiplication(self):
        q1 = self.Quaternion(1, 2, 3, 4)
        q2 = self.Quaternion(5, 6, 7, 8)
        result = q1 * q2
        self.assertAlmostEqual(result, self.Quaternion(-60, 12, 30, 24))
    
    def test_multiplication_scalar_int(self):
        q1 = self.Quaternion(1, 2, 3, 4)
        scalar = 2
        result = q1 * scalar
        self.assertAlmostEqual(result, self.Quaternion(2, 4, 6, 8))
    
    def test_multiplication_scalar_int_reverse(self):
        q1 = self.Quaternion(1, 2, 3, 4)
        scalar = 2
        result = scalar * q1
        self.assertAlmostEqual(result, self.Quaternion(2, 4, 6, 8))
    
    def test_multiplication_scalar_float(self):
        q1 = self.Quaternion(1, 2, 3, 4)
        scalar = 2.5
        result = q1 * scalar
        self.assertAlmostEqual(result, self.Quaternion(2.5, 5, 7.5, 10))
    
    def test_multiplication_scalar_float_reverse(self):
        q1 = self.Quaternion(1, 2, 3, 4)
        scalar = 2.5
        result = scalar * q1
        self.assertAlmostEqual(result, self.Quaternion(2.5, 5, 7.5, 10))
    
    def test_inverse(self):
        q1 = self.Quaternion(1, 2, 3, 4)
        result = q1.inverse()
        self.assertAlmostEqual(result, self.Quaternion(1/30, -2/30, -3/30, -4/30))
    
    def test_double_inverse(self):
        q1 = self.Quaternion(1, 2, 3, 4)
        result = q1.inverse().inverse()
        self.assertAlmostEqual(result, q1)

    def test_division(self):
        q1 = self.Quaternion(1, 2, 3, 4)
        q2 = self.Quaternion(5, 6, 7, 8)
        result = q1 / q2

        self.assertAlmostEqual(result, self.Quaternion(70/174, 8/174, 0, 16/174))
    
    def test_division_scalar_int(self):
        q1 = self.Quaternion(1, 2, 3, 4)
        scalar = 2
        result = q1 / scalar
        self.assertAlmostEqual(result, self.Quaternion(0.5, 1, 1.5, 2))
    
    def test_division_scalar_int_reverse(self):
        q1 = self.Quaternion(1, 2, 3, 4)
        scalar = 2
        result = scalar / q1
        self.assertAlmostEqual(result, self.Quaternion(2/30, -4/30, -6/30, -8/30))
    
    def test_division_scalar_float(self):
        q1 = self.Quaternion(1, 2, 3, 4)
        scalar = 2.5
        result = q1 / scalar
        self.assertAlmostEqual(result, self.Quaternion(0.4, 0.8, 1.2, 1.6))
    
    def test_division_scalar_float_reverse(self):
        q1 = self.Quaternion(1, 2, 3, 4)
        scalar = 2.5
        result = scalar / q1
        self.assertAlmostEqual(result, self.Quaternion(2.5/30, -5/30, -7.5/30, -10/30))

    def test_inverse_by_division(self):
        q1 = self.Quaternion(1, 2, 3, 4)
        scalar = 1
        result = scalar / q1
        self.assertAlmostEqual(result, q1.inverse())
    
    def test_inplace_addition(self):
        q1 = self.Quaternion(1, 2, 3, 4)
        q2 = self.Quaternion(5, 6, 7, 8)
        q1 += q2
        self.assertAlmostEqual(q1, self.Quaternion(6, 8, 10, 12))
    
    def test_inplace_subtraction(self):
        q1 = self.Quaternion(1, 2, 3, 4)
        q2 = self.Quaternion(5, 6, 7, 8)
        q1 -= q2
        self.assertAlmostEqual(q1, self.Quaternion(-4, -4, -4, -4))
    
    def test_inplace_multiplication(self):
        q1 = self.Quaternion(1, 2, 3, 4)
        q2 = self.Quaternion(5, 6, 7, 8)
        q1 *= q2
        self.assertAlmostEqual(q1, self.Quaternion(-60, 12, 30, 24))
    
    def test_inplace_division(self):
        q1 = self.Quaternion(1, 2, 3, 4)
        q2 = self.Quaternion(5, 6, 7, 8)
        q1 /= q2
        self.assertAlmostEqual(q1, self.Quaternion(70/174, 8/174, 0, 16/174))
    
    def test_negation(self):
        q1 = self.Quaternion(1, 2, 3, 4)
        result = -q1
        self.assertAlmostEqual(result, self.Quaternion(-1, -2, -3, -4))
    
    def test_conjugate(self):
        q1 = self.Quaternion(1, 2, 3, 4)
        result = q1.conjugate()
        self.assertAlmostEqual(result, self.Quaternion(1, -2, -3, -4))
    
    def test_norm(self):
        q1 = self.Quaternion(1, 2, 3, 4)
        result = abs(q1)
        self.assertAlmostEqual(result, (1**2 + 2**2 + 3**2 + 4**2)**0.5)
    
    def test_normalize(self):
        q1 = self.Quaternion(1, 2, 3, 4)
        result = q1.normalize()
        self.assertAlmostEqual(abs(result), 1)
