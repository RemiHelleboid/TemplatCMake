/**
 * @file vector.hpp
 * @author remzerrr (remi.helleboid@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-10-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <array>
#include <cmath>
#include <iostream>
#include <vector>

namespace math {

class Vector3D {
 private:
    double m_x;
    double m_y;
    double m_z;

 public:
    Vector3D() : m_x(0), m_y(0), m_z(0) {}
    Vector3D(double x, double y, double z) : m_x(x), m_y(y), m_z(z) {}
    Vector3D(const Vector3D& v) = default;
    ~Vector3D()                 = default;

    double x() const { return m_x; }
    double y() const { return m_y; }
    double z() const { return m_z; }

    void x(double x) { m_x = x; }
    void y(double y) { m_y = y; }
    void z(double z) { m_z = z; }

    double    norm() const;
    double    norm_square() const;
    Vector3D& normalize();
    Vector3D  normalized() const;

    Vector3D cross(const Vector3D& v) const;
    double   dot(const Vector3D& v) const;
    double   triple_product(const Vector3D& v1, const Vector3D& v2) const;

    void randomize_uniform(double min, double max);
    void randomize_uniform(double min_x, double max_x, double min_y, double max_y, double min_z, double max_z);
    void randomize_normal(double mean, double std_dev);

    Vector3D& operator=(const Vector3D& v) = default;
    Vector3D& operator+=(const Vector3D& v);
    Vector3D& operator-=(const Vector3D& v);
    Vector3D& operator*=(double a);
    Vector3D& operator/=(double a);

    Vector3D operator-() const;
    Vector3D operator+(const Vector3D& v) const;
    Vector3D operator-(const Vector3D& v) const;
    Vector3D operator*(double a) const;
    Vector3D operator/(double a) const;

    double   operator*(const Vector3D& v) const;
    Vector3D operator^(const Vector3D& v) const;

    bool operator==(const Vector3D& v) const;
    bool operator!=(const Vector3D& v) const;

    friend std::ostream& operator<<(std::ostream& os, const Vector3D& v);
};

}  // namespace math