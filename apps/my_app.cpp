/**
 * @file my_apps.cpp
 * @author remzerrr (remi.helleboid@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <iostream>
#include <vector>

#include "vector.hpp"

int main() {
    math::Vector3D v1(1, 2, 3);
    math::Vector3D v2(4, 5, 6);
    math::Vector3D v3 = v1 + v2;
    std::cout << v3.x() << " " << v3.y() << " " << v3.z() << std::endl;
    return 0;
}