#pragma once
#include <map>
#include <string>
#include <iostream>
#include <comdef.h>
#include <exception>
#include <filesystem>
#include "Core/Prerequisites.hpp"
#include "Core/Resource System/MyResource.hpp"

namespace DX3D {
    class MyResourceSystem {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        std::map<std::wstring, MyResourcePtr> resources;

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyResourceSystem();
        ~MyResourceSystem();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        MyResourcePtr CreateResourceFromFile(const wchar_t* resourcePath);

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
        virtual MyResource* CreateResourceFromFileConcrete(const wchar_t* resourcePath) = 0;
    public:

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
    };
} // namespace DX3D

