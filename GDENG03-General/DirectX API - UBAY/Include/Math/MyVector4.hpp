#pragma once
#include<iostream>
#include<string>

namespace DX3D {
    class MyVector4 {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
    public:
        float x, y, z, w;

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyVector4() : x(0), y(0), z(0), w(0) {}
        MyVector4(float all) : x(all), y(all), z(all), w(all) {}
        MyVector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
        MyVector4(const MyVector4& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        void Cross(MyVector4& A, MyVector4& B, MyVector4& C) {
            this->x = A.y * (B.z * C.w - C.z * B.w) - A.z * (B.y * C.w - C.y * B.w) + A.w * (B.y * C.z - B.z * C.y);
            this->y = -(A.x * (B.z * C.w - C.z * B.w) - A.z * (B.x * C.w - C.x * B.w) + A.w * (B.x * C.z - C.x * B.z));
            this->z = A.x * (B.y * C.w - C.y * B.w) - A.y * (B.x * C.w - C.x * B.w) + A.w * (B.x * C.y - C.x * B.y);
            this->w = -(A.x * (B.y * C.z - C.y * B.z) - A.y * (B.x * C.z - C.x * B.z) + A.z * (B.x * C.y - C.x * B.y));
        }
        MyVector4& operator += (const MyVector4& other) {
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;
            this->w += other.w;
            return *this;
        }
        MyVector4 GetCross(MyVector4& A, MyVector4& B, MyVector4& C) {
            MyVector4 result(this->x, this->y, this->z, this->w);
            result.x = A.y * (B.z * C.w - C.z * B.w) - A.z * (B.y * C.w - C.y * B.w) + A.w * (B.y * C.z - B.z * C.y);
            result.y = -(A.x * (B.z * C.w - C.z * B.w) - A.z * (B.x * C.w - C.x * B.w) + A.w * (B.x * C.z - C.x * B.z));
            result.z = A.x * (B.y * C.w - C.y * B.w) - A.y * (B.x * C.w - C.x * B.w) + A.w * (B.x * C.y - C.x * B.y);
            result.w = -(A.x * (B.y * C.z - C.y * B.z) - A.y * (B.x * C.z - C.x * B.z) + A.z * (B.x * C.y - C.x * B.y));
            return result;
        }
        void PrintValues(std::string label = "") {
            std::cout << "[" << label << "]: (" << this->x << ", " << this->y << ", " << this->z << ", " << this->w << ")" << std::endl;
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


