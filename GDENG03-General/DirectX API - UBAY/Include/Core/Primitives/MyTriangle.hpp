#pragma once
#include <vector>
#include "Math/MyVertex.hpp"

namespace DX3D {
    class MyTriangle {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        std::vector<MyVertex> vertices;
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyTriangle();
        MyTriangle(const MyVertex& vertexA, const MyVertex& vertexB, const MyVertex& vertexC);
        ~MyTriangle();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        std::vector<MyVertex> GetVertices() { return this->vertices; }

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

