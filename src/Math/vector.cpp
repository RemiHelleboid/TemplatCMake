/**
 * @file vector.cpp
 * @author remzerrr (remi.helleboid@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-10-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "vector.hpp"

namespace math {

double Vector3D::norm() const { return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z); }

double Vector3D::norm_square() const { return m_x * m_x + m_y * m_y + m_z * m_z; }

Vector3D& Vector3D::normalize() {
    double v_norm = norm();
    m_x /= v_norm;
    m_y /= v_norm;
    m_z /= v_norm;
    return *this;
}

Vector3D Vector3D::normalized() const {
    double v_norm = norm();
    return Vector3D(m_x / v_norm, m_y / v_norm, m_z / v_norm);
}

Vector3D Vector3D::cross(const Vector3D& v) const {
    return Vector3D(m_y * v.m_z - m_z * v.m_y, m_z * v.m_x - m_x * v.m_z, m_x * v.m_y - m_y * v.m_x);
}

double Vector3D::dot(const Vector3D& v) const { return m_x * v.m_x + m_y * v.m_y + m_z * v.m_z; }

double triple_scalar_product(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3) { return v1.dot(v2.cross(v3)); }

Vector3D Vector3D::operator-() const { return Vector3D(-m_x, -m_y, -m_z); }

Vector3D operator+(const Vector3D& v1, const Vector3D& v2) { return Vector3D(v1.m_x + v2.m_x, v1.m_y + v2.m_y, v1.m_z + v2.m_z); }

Vector3D operator-(const Vector3D& v1, const Vector3D& v2) { return Vector3D(v1.m_x - v2.m_x, v1.m_y - v2.m_y, v1.m_z - v2.m_z); }

}  // namespace math