//
// Created by mgl on 12/06/2021.
//

#include <memory>
#include "Vector3.hpp"

std::shared_ptr<Raylib::Vector3> newVector(float x, float y, float z) {
    return std::make_shared<Raylib::Vector3>(x, y, z);
}