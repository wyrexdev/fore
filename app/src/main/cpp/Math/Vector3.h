//
// Created by wyrex on 8/14/25.
//

#ifndef FORE_VECTOR3_H
#define FORE_VECTOR3_H

#include <iostream>
#include <cmath>

struct Vector3 {
    float x, y, z;

    Vector3(float _x = 0, float _y = 0, float _z = 0)
            : x(_x), y(_y), z(_z) {}

    Vector3 operator+(const Vector3& v) const {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }

    Vector3 operator-(const Vector3& v) const {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    float dot(const Vector3& v) const {
        return x*v.x + y*v.y + z*v.z;
    }

    Vector3 cross(const Vector3& v) const {
        return Vector3(
                y*v.z - z*v.y,
                z*v.x - x*v.z,
                x*v.y - y*v.x
        );
    }

    float length() const {
        return std::sqrt(x*x + y*y + z*z);
    }

    Vector3 normalize() const {
        float len = length();
        if (len == 0) return Vector3(0,0,0);
        return *this * (1.0f / len);
    }

    void print() const {
        std::cout << "(" << x << ", " << y << ", " << z << ")\n";
    }
};

#endif //FORE_VECTOR3_H
