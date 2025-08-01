#include "Core/Primitives/MyTriangle.hpp"
#include <vector>

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyTriangle::MyTriangle() {}
MyTriangle::MyTriangle(const MyVertex& vertexA, const MyVertex& vertexB, const MyVertex& vertexC) {
    this->vertices.push_back(vertexA);
    this->vertices.push_back(vertexB);
    this->vertices.push_back(vertexC);
}
MyTriangle::~MyTriangle() {}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
