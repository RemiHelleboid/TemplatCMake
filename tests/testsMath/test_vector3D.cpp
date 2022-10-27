/**
 * @file test_vector3D.cpp
 * @author remzerrr (remi.helleboid@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <cassert>
#include <cmath>
#include <random>
#include <sstream>

#include "doctest/doctest.h"

#include "vector.hpp"

TEST_CASE("Vector3D") {
    SUBCASE("Constructor") {
        math::Vector3D v1(1, 2, 3);
        CHECK(v1.x() == 1);
        CHECK(v1.y() == 2);
        CHECK(v1.z() == 3);
    }

    SUBCASE("Norm") {
        math::Vector3D v1(1, 2, 3);
        CHECK(v1.norm() == std::sqrt(14));
    }

    SUBCASE("Norm square") {
        math::Vector3D v1(1, 2, 3);
        CHECK(v1.norm_square() == 14);
    }

    SUBCASE("Normalize") {
        math::Vector3D v1(1, 2, 3);
        v1.normalize();
        CHECK(v1.norm() == 1);
    }

    SUBCASE("Normalized") {
        math::Vector3D v1(1, 2, 3);
        math::Vector3D v2 = v1.normalized();
        CHECK(v2.norm() == 1);
    }

    SUBCASE("Cross") {
        math::Vector3D v1(1, 2, 3);
        math::Vector3D v2(4, 5, 6);
        math::Vector3D v3 = v1.cross(v2);
        CHECK(v3.x() == -3);
        CHECK(v3.y() == 6);
        CHECK(v3.z() == -3);
    }

    SUBCASE("Dot") {
        math::Vector3D v1(1, 2, 3);
        math::Vector3D v2(4, 5, 6);
        CHECK(v1.dot(v2) == 32);
    }

    SUBCASE("Triple scalar product") {
        math::Vector3D v1(1, 2, 3);
        math::Vector3D v2(4, 5, 6);
        math::Vector3D v3(7, 8, 9);
        CHECK(triple_scalar_product(v1, v2, v3) == 0);
    }

    SUBCASE("Operator -") {
        math::Vector3D v1(1, 2, 3);
        math::Vector3D v2 = -v1;
        CHECK(v2.x());
    };
}