#pragma once
#include<iostream>
#include<string>
#include<cmath> // For std::isnan and std::isinf

namespace DX3D {
    class MyVector3 {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
    public:
        float x, y, z;

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyVector3() : x(0), y(0), z(0) {}
        MyVector3(float all) : x(all), y(all), z(all) {}
        MyVector3(float x, float y, float z) : x(x), y(y), z(z) {}
        MyVector3(const MyVector3& other) : x(other.x), y(other.y), z(other.z) {}

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        MyVector3 operator * (float scalar) const {
            return MyVector3(this->x * scalar, this->y * scalar, this->z * scalar);
        }
        MyVector3 operator + (MyVector3 other) const {
            return MyVector3(this->x + other.x, this->y + other.y, this->z + other.z);
        }
        MyVector3& operator += (const MyVector3& other) {
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;
            return *this;
        }
        MyVector3& operator = (const MyVector3& other) {
            this->x = other.x;
            this->y = other.y;
            this->z = other.z;
            return *this;
        }
        static MyVector3 Lerp(const MyVector3& start, const MyVector3& end, float delta) {
            MyVector3 returnVector;
            returnVector.x = start.x * (1.0f - delta) + end.x * (delta);
            returnVector.y = start.y * (1.0f - delta) + end.y * (delta);
            returnVector.z = start.z * (1.0f - delta) + end.z * (delta);
            return returnVector;
        }
        void PrintValues(std::string label = "") {
            std::cout << "[" << label << "]: (" << this->x << ", " << this->y << ", " << this->z << ")" << std::endl;
        }

        // Validation method
        bool IsValid() const {
            return !std::isnan(x) && !std::isnan(y) && !std::isnan(z) &&
                   !std::isinf(x) && !std::isinf(y) && !std::isinf(z);
        }

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
    public:

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
    };
} // namespace DX3D


