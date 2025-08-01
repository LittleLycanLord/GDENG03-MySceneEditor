#pragma once
#include "Math/MyVector3.hpp"
#include "Math/MyVector2.hpp"

namespace DX3D {
    // // * Single Color Vertex
    // struct MyVertex {
    //     MyVector3 position;

    //     MyVertex() : position() {}
    //     MyVertex(float x, float y, float z) : position(x, y, z) {}
    //     MyVertex(const MyVector3& position) : position(position) {}
    // };

    // //* Colored Vertex
    // struct MyVertex {
    //     MyVector3 position;
    //     MyVector3 color;

    //     MyVertex() : position(0.0f), color(1.0f) {}
    //     MyVertex(float x, float y, float z) : position(x, y, z), color(1.0f) {}
    //     MyVertex(float x, float y, float z, float r, float g, float b) : position(x, y, z), color(r, g, b) {}
    //     MyVertex(const MyVector3& position) : position(position), color(1.0f) {}
    //     MyVertex(const MyVector3& position, const MyVector3& color) : position(position), color(color) {}
    // };

    // //* Animated Vertex : Moving
    // struct MyVertex {
    //     MyVector3 position;
    //     MyVector3 nextPosition;
    //     MyVector3 color;

    //     MyVertex() : position(0.0f), nextPosition(0.0f), color(1.0f) {}
    //     MyVertex(float x, float y, float z) : position(x, y, z), nextPosition(position), color(1.0f) {}
    //     MyVertex(float x, float y, float z, float r, float g, float b) : position(x, y, z), nextPosition(position), color(r, g, b) {}
    //     MyVertex(float x1, float y1, float z1, float x2, float y2, float z2, float r, float g, float b) : position(x1, y1, z1), nextPosition(x2, y2, z2), color(r, g, b) {}

    //     MyVertex(const MyVector3& position) : position(position), nextPosition(position), color(1.0f) {}
    //     MyVertex(const MyVector3& position, const MyVector3& color) : position(position), nextPosition(position), color(color) {}
    //     MyVertex(const MyVector3& position, const MyVector3& nextPosition, const MyVector3& color) : position(position), nextPosition(nextPosition), color(color) {}
    // };

    // //* Animated Vertex : Color Shifting
    // struct MyVertex {
    //     MyVector3 position;
    //     MyVector3 nextPosition;
    //     MyVector3 color;
    //     MyVector3 nextColor;

    //     MyVertex() : position(0.0f), nextPosition(0.0f), color(1.0f), nextColor(0.0f) {}
    //     MyVertex(float x, float y, float z) : position(x, y, z), nextPosition(position), color(1.0f), nextColor(0.0f) {}
    //     MyVertex(float x, float y, float z, float r, float g, float b) : position(x, y, z), nextPosition(position), color(r, g, b), nextColor(0.0f) {}
    //     MyVertex(float x1, float y1, float z1, float x2, float y2, float z2, float r, float g, float b) : position(x1, y1, z1), nextPosition(x2, y2, z2), color(r, g, b), nextColor(0.0f) {}
    //     MyVertex(float x1, float y1, float z1, float x2, float y2, float z2, float r1, float g1, float b1, float r2, float g2, float b2) : position(x1, y1, z1), nextPosition(x2, y2, z2), color(r1, g1, b1), nextColor(r2, g2, b2) {}

    //     MyVertex(const MyVector3& position) : position(position), nextPosition(position), color(1.0f), nextColor(0.0f) {}
    //     MyVertex(const MyVector3& position, const MyVector3& color) : position(position), nextPosition(position), color(color), nextColor(0.0f) {}
    //     MyVertex(const MyVector3& position, const MyVector3& nextPosition, const MyVector3& color) : position(position), nextPosition(nextPosition), color(color), nextColor(0.0f) {}
    //     MyVertex(const MyVector3& position, const MyVector3& nextPosition, const MyVector3& color, const MyVector3& nextColor) : position(position), nextPosition(nextPosition), color(color), nextColor(nextColor) {}
    // };

    // //* 3D Vertex
    // struct MyVertex {
    //     MyVector3 position;
    //     MyVector3 color;
    //     MyVector3 nextColor;

    //     MyVertex() : position(0.0f), color(1.0f), nextColor(0.0f) {}
    //     MyVertex(float x, float y, float z) : position(x, y, z), color(1.0f), nextColor(0.0f) {}
    //     MyVertex(float x, float y, float z, float r, float g, float b) : position(x, y, z), color(r, g, b), nextColor(0.0f) {}
    //     MyVertex(float x1, float y1, float z1, float x2, float y2, float z2, float r, float g, float b) : position(x1, y1, z1), color(r, g, b), nextColor(0.0f) {}
    //     MyVertex(float x1, float y1, float z1, float x2, float y2, float z2, float r1, float g1, float b1, float r2, float g2, float b2) : position(x1, y1, z1), color(r1, g1, b1), nextColor(r2, g2, b2) {}

    //     MyVertex(const MyVector3& position) : position(position), color(1.0f), nextColor(0.0f) {}
    //     MyVertex(const MyVector3& position, const MyVector3& color) : position(position), color(color), nextColor(0.0f) {}
    //     MyVertex(const MyVector3& position, const MyVector3& nextPosition, const MyVector3& color) : position(position), color(color), nextColor(0.0f) {}
    //     MyVertex(const MyVector3& position, const MyVector3& nextPosition, const MyVector3& color, const MyVector3& nextColor) : position(position), color(color), nextColor(nextColor) {}
    // };

    //* Textured Vertex
    struct MyVertex {
        MyVector3 position;
        MyVector2 textureCoordinate;

        MyVertex() : position(0.0f), textureCoordinate(1.0f) {}
        MyVertex(float x, float y, float z) : position(x, y, z), textureCoordinate(1.0f) {}
        MyVertex(float x, float y, float z, float u, float v) : position(x, y, z), textureCoordinate(u,v) {}

        MyVertex(const MyVector3& position) : position(position), textureCoordinate(1.0f) {}
        MyVertex(const MyVector3& position, const MyVector2& textureCoordinate) : position(position), textureCoordinate(textureCoordinate) {}
    };
} // namespace DX3D


