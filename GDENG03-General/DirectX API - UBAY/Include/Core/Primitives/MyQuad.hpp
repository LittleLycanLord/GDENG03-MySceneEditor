#pragma once
#include <vector>
#include "Core/Primitives/MyTriangle.hpp"

namespace DX3D {
    class MyQuad {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        MyTriangle triangleA;
        MyTriangle triangleB;
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyQuad();
        MyQuad(const MyVertex& topLeft, const MyVertex& topRight, const MyVertex& bottomRight, const MyVertex& bottomLeft);
        MyQuad(const MyTriangle& triangleA, const MyTriangle& triangleB);
        ~MyQuad();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        std::vector<MyVertex> GetVertices() {
            std::vector<MyVertex> vertices;
            vertices.reserve(triangleA.GetVertices().size() + triangleB.GetVertices().size()); // preallocate memory
            vertices.insert(vertices.end(), triangleA.GetVertices().begin(), triangleA.GetVertices().end());
            vertices.insert(vertices.end(), triangleB.GetVertices().begin(), triangleB.GetVertices().end());
            return vertices;
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

