#pragma once
#include <string>
#include <iostream>
#include <comdef.h>
#include <exception>
#include <filesystem>
#include "Core/Prerequisites.hpp"

namespace DX3D {
    class MyResource {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        std::wstring resourcePath;

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyResource(const wchar_t* resourcePath);
        virtual ~MyResource();

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

