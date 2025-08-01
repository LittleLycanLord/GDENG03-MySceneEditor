#include "Core/Primitives/MyQuad.hpp"

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyQuad::MyQuad() {
    this->triangleA = MyTriangle(
        // MyVertex(
        //     -0.1f, 0.1f, 0.0f,    // position (x, y, z)
        //     -0.1f, 0.1f, 0.0f,    // position (x, y, z)
        //     0.0f, 1.0f, 0.0f,    // color (r, g, b)
        //     1.0f, 0.0f, 0.0f     // nextColor (r, g, b)
        // ), // Top-left
        // MyVertex(
        //     0.1f, 0.1f, 0.0f,    // position
        //     0.1f, 0.1f, 0.0f,    // position
        //     1.0f, 1.0f, 0.0f,    // color
        //     0.0f, 1.0f, 0.0f     // nextColor
        // ), // Top-right
        // MyVertex(
        //     -0.1f, -0.1f, 0.0f,    // position
        //     -0.1f, -0.1f, 0.0f,    // position
        //     1.0f, 0.0f, 0.0f,    // color
        //     0.0f, 0.0f, 1.0f     // nextColor
        // ) // Bottom-left
    );

    this->triangleB = MyTriangle(
        // MyVertex(
        //     -0.1f, -0.1f, 0.0f,    // position
        //     -0.1f, -0.1f, 0.0f,    // position
        //     1.0f, 0.0f, 0.0f,    // color
        //     0.0f, 0.0f, 1.0f     // nextColor
        // ), // Bottom-left
        // MyVertex(
        //     0.1f, 0.1f, 0.0f,    // position
        //     0.1f, 0.1f, 0.0f,    // position
        //     1.0f, 1.0f, 0.0f,    // color
        //     0.0f, 1.0f, 0.0f     // nextColor
        // ), // Top-right
        // MyVertex(
        //     0.1f, -0.1f, 0.0f,    // position
        //     0.1f, -0.1f, 0.0f,    // position
        //     0.0f, 0.0f, 1.0f,    // color
        //     1.0f, 1.0f, 0.0f     // nextColor
        // ) // Bottom-right
    );
}
MyQuad::MyQuad(const MyVertex& topLeft, const MyVertex& topRight, const MyVertex& bottomRight, const MyVertex& bottomLeft) {
    this->triangleA = MyTriangle(topLeft, topRight, bottomLeft);
    this->triangleB = MyTriangle(bottomLeft, topRight, bottomRight);
}
MyQuad::MyQuad(const MyTriangle& triangleA, const MyTriangle& triangleB) : triangleA(triangleA), triangleB(triangleB) {
}
MyQuad::~MyQuad() {}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
