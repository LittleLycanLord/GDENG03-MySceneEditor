#pragma once

#include <iostream>
#include <comdef.h>
#include <exception>
#include "Core/Prerequisites.hpp"
#include "Math/MyVector3.hpp"
#include "Math/MyMatrix4x4.hpp"

namespace DX3D {
    class MyTransform {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    public:
        MyMatrix4x4 worldMatrix;
        MyVector3 position;
        MyVector3 rotation;
        MyVector3 scale;

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyTransform() : position(MyVector3()),
            rotation(MyVector3()),
            scale(MyVector3(1.0f)) {
        }
        ~MyTransform() {}

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        void Update(float deltaTime) {
            this->worldMatrix.SetIdentity();
            this->worldMatrix.Scale(this->scale);
            this->worldMatrix.Rotate(this->rotation);
            this->worldMatrix.Translate(this->position);
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

