#pragma once
#include <string>
#include <iostream>
#include <comdef.h>
#include <exception>
#include "Core/Prerequisites.hpp"
#include "Core/Resource System/MyResourceSystem.hpp"
#include "Core/Resource System/MyResource.hpp"
#include "Core/Resource System/Managers/MyMesh.hpp"

namespace DX3D {
    class MyMeshManager : public MyResourceSystem {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyMeshManager();
        ~MyMeshManager();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        MyMeshPtr CreateUniqueMeshFromFile(const wchar_t* resourcePath);
        MyMeshPtr CreateMeshFromFile(const wchar_t* resourcePath) {
            return std::static_pointer_cast<MyMesh>(CreateResourceFromFile(resourcePath));
        }

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
        virtual MyResource* CreateResourceFromFileConcrete(const wchar_t* resourcePath);
    public:

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
    };
} // namespace DX3D

