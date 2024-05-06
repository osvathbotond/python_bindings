#include <array>
#include <sstream>
#include <string>
#include <cmath>

class Quaternion {
    public:
        Quaternion() {
            m_data.fill(0.0f);
        }

        Quaternion(double a, double b, double c, double d) {
            m_data[0] = a;
            m_data[1] = b;
            m_data[2] = c;
            m_data[3] = d;
        }

        void setAt(size_t index, double value) {
            if (index < 0 || index >= 4) {
                throw std::out_of_range("Index out of range");
            }
            m_data[index] = value;
        }

        double getAt(size_t index) {
            if (index < 0 || index >= 4) {
                throw std::out_of_range("Index out of range");
            }
            return m_data[index];
        }

        void setA(double value) {
            m_data[0] = value;
        }

        double getA() {
            return m_data[0];
        }

        void setB(double value) {
            m_data[1] = value;
        }

        double getB() {
            return m_data[1];
        }

        void setC(double value) {
            m_data[2] = value;
        }

        double getC() {
            return m_data[2];
        }

        void setD(double value) {
            m_data[3] = value;
        }

        double getD() {
            return m_data[3];
        }

        std::array<double, 4> getData() const {
            return m_data;
        }

        std::string toString() const {
            std::stringstream ss;
            ss << "Quaternion(" << m_data[0] << ", " << m_data[1] << ", " << m_data[2] << ", " << m_data[3] << ")";
            return ss.str();
        }

        Quaternion operator+(const Quaternion& other) const {
            return Quaternion(m_data[0] + other.m_data[0], m_data[1] + other.m_data[1], m_data[2] + other.m_data[2], m_data[3] + other.m_data[3]);
        }

        Quaternion operator-(const Quaternion& other) const {
            return Quaternion(m_data[0] - other.m_data[0], m_data[1] - other.m_data[1], m_data[2] - other.m_data[2], m_data[3] - other.m_data[3]);
        }

        Quaternion operator*(const Quaternion& other) const {
            return Quaternion(
                m_data[0] * other.m_data[0] - m_data[1] * other.m_data[1] - m_data[2] * other.m_data[2] - m_data[3] * other.m_data[3],
                m_data[0] * other.m_data[1] + m_data[1] * other.m_data[0] + m_data[2] * other.m_data[3] - m_data[3] * other.m_data[2],
                m_data[0] * other.m_data[2] - m_data[1] * other.m_data[3] + m_data[2] * other.m_data[0] + m_data[3] * other.m_data[1],
                m_data[0] * other.m_data[3] + m_data[1] * other.m_data[2] - m_data[2] * other.m_data[1] + m_data[3] * other.m_data[0]
            );
        }

        Quaternion operator*(double scalar) const {
            return Quaternion(m_data[0] * scalar, m_data[1] * scalar, m_data[2] * scalar, m_data[3] * scalar);
        }

        friend Quaternion operator*(double scalar, const Quaternion& q) {
            return q * scalar;
        }

        Quaternion operator/(const Quaternion& other) const {
            return (*this) * other.inverse();
        }

        Quaternion operator/(double scalar) const {
            return Quaternion(m_data[0] / scalar, m_data[1] / scalar, m_data[2] / scalar, m_data[3] / scalar);
        }

        friend Quaternion operator/(double scalar, const Quaternion& q) {
            return q.inverse() * scalar;
        }

        Quaternion operator-() const {
            return Quaternion(-m_data[0], -m_data[1], -m_data[2], -m_data[3]);
        }

        Quaternion conjugate() const {
            return Quaternion(m_data[0], -m_data[1], -m_data[2], -m_data[3]);
        }

        double normSquared() const {
            return m_data[0] * m_data[0] + m_data[1] * m_data[1] + m_data[2] * m_data[2] + m_data[3] * m_data[3];
        }

        double norm() const {
            return std::sqrt(normSquared());
        }

        Quaternion normalize() const {
            double n = norm();
            return Quaternion(m_data[0] / n, m_data[1] / n, m_data[2] / n, m_data[3] / n);
        }

        Quaternion inverse() const {
            return conjugate() / normSquared();
        }

        bool operator==(const Quaternion& other) const {
            return m_data[0] == other.m_data[0] && m_data[1] == other.m_data[1] && m_data[2] == other.m_data[2] && m_data[3] == other.m_data[3];
        }

    private:
        std::array<double, 4> m_data;
};