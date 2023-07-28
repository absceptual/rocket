
#pragma once
#include <iostream>
#include <cmath>

class Vector3 {
public:
    float x, y, z;

    // Default constructor
    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

    // Parameterized constructor
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

    // Copy constructor
    Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z) {}

    // Addition operator overloading
    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    // Subtraction operator overloading
    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    // Multiplication operator overloading with a scalar
    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    // Division operator overloading with a scalar
    Vector3 operator/(float scalar) const {
        // Avoid division by zero
        if (scalar != 0.0f)
            return Vector3(x / scalar, y / scalar, z / scalar);
        else {
            std::cerr << "Error: Division by zero." << std::endl;
            return Vector3();
        }
    }

    // Multiplication operator overloading with another Vector3
    Vector3 operator*(const Vector3& other) const {
        return Vector3(x * other.x, y * other.y, z * other.z);
    }

    // Division operator overloading with another Vector3
    Vector3 operator/(const Vector3& other) const {
        // Avoid division by zero
        if (other.x != 0.0f && other.y != 0.0f && other.z != 0.0f)
            return Vector3(x / other.x, y / other.y, z / other.z);
        else {
            std::cerr << "Error: Division by zero." << std::endl;
            return Vector3();
        }
    }

    // Assignment operator overloading
    Vector3& operator=(const Vector3& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }

    // Addition assignment operator overloading
    Vector3& operator+=(const Vector3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    // Subtraction assignment operator overloading
    Vector3& operator-=(const Vector3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    // Multiplication assignment operator overloading with a scalar
    Vector3& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    // Division assignment operator overloading with a scalar
    Vector3& operator/=(float scalar) {
        // Avoid division by zero
        if (scalar != 0.0f) {
            x /= scalar;
            y /= scalar;
            z /= scalar;
        }
        else
            std::cerr << "Error: Division by zero." << std::endl;

        return *this;
    }

    // Equality operator overloading
    bool operator==(const Vector3& other) const {
        return (x == other.x && y == other.y && z == other.z);
    }

    // Inequality operator overloading
    bool operator!=(const Vector3& other) const {
        return !(*this == other);
    }

    // Magnitude function
    float magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }
};

// Stream insertion operator overloading (for output)
inline std::ostream& operator<<(std::ostream& os, const Vector3& vector) {
    os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
    return os;
}
