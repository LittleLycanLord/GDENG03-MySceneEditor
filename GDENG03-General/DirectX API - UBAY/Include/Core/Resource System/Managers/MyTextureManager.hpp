#pragma once
#include <string>
#include <iostream>
#include <comdef.h>
#include <exception>
#include "Core/Prerequisites.hpp"
#include "Core/Resource System/MyResourceSystem.hpp"
#include "Core/Resource System/MyResource.hpp"
#include "Core/Resource System/Managers/MyTexture.hpp"

namespace DX3D {
    class MyTextureManager : public MyResourceSystem {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyTextureManager();
        ~MyTextureManager();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        MyTexturePtr CreateUniqueTextureFromFile(const wchar_t* resourcePath);
        MyTexturePtr CreateTextureFromFile(const wchar_t* resourcePath) {
            return std::static_pointer_cast<MyTexture>(CreateResourceFromFile(resourcePath));
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

