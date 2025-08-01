#pragma once

namespace DX3D {
    class MyScreenPoint {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
    public:
        int x;
        int y;

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyScreenPoint() : x(0), y(0) {};
        MyScreenPoint(int x, int y) : x(x), y(y) {};
        MyScreenPoint(const MyScreenPoint& other) : x(other.x), y(other.y) {};
        ~MyScreenPoint() {};

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:

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

