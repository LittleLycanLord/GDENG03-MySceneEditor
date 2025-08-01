#pragma once
#include<iostream>
#include<string>
#include<cmath> // For std::isnan and std::isinf

namespace DX3D {
    class MyVector2 {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
    public:
        float x, y;

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyVector2() : x(0), y(0) {}
        MyVector2(float all) : x(all), y(all) {}
        MyVector2(float x, float y) : x(x), y(y) {}
        MyVector2(const MyVector2& other) : x(other.x), y(other.y) {}

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        MyVector2 operator * (float scalar) const {
            return MyVector2(this->x * scalar, this->y * scalar);
        }
        MyVector2 operator + (MyVector2 other) const {
            return MyVector2(this->x + other.x, this->y + other.y);
        }
        MyVector2& operator += (const MyVector2& other) {
            this->x += other.x;
            this->y += other.y;
            return *this;
        }
        static MyVector2 Lerp(const MyVector2& start, const MyVector2& end, float delta) {
            MyVector2 returnVector;
            returnVector.x = start.x * (1.0f - delta) + end.x * (delta);
            returnVector.y = start.y * (1.0f - delta) + end.y * (delta);
            return returnVector;
        }
        void PrintValues(std::string label = "") {
            std::cout << "[" << label << "]: (" << this->x << ", " << this->y << ")" << std::endl;
        }

        // Validation method
        bool IsValid() const {
            return !std::isnan(x) && !std::isnan(y) &&
                   !std::isinf(x) && !std::isinf(y);
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


