#pragma once
#include <iostream>
#include <comdef.h>
#include <exception>
#include "Core/Prerequisites.hpp"
#include "Core/MyRenderSystem.hpp"
#include "Graphics/MyDeviceContext.hpp"
#include "Graphics/MyGraphicsEngine.hpp"

namespace DX3D {
    class MyIndexBuffer {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        MyRenderSystem* renderSystem{ nullptr };

        UINT indexCount{ 0 };
        ID3D11Buffer* D3DIndexBuffer{ nullptr };

        friend class MyDeviceContext;
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyIndexBuffer(void* indices, UINT indexCount, MyRenderSystem* renderSystem);
        ~MyIndexBuffer();

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
        UINT GetIndexCount() const { return indexCount; }
    };
} // namespace DX3D

