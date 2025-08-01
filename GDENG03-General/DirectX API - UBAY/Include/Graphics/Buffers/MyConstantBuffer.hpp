#pragma once
#include <iostream>
#include <comdef.h>
#include <exception>
#include "Graphics/MyGraphicsEngine.hpp"
#include "Core/Prerequisites.hpp"


namespace DX3D {
    class MyConstantBuffer {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        MyRenderSystem* renderSystem{ nullptr };

        ID3D11Buffer* D3DConstantBuffer{ nullptr };

        friend class MyDeviceContext;
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyConstantBuffer(void* buffer, UINT bufferSize, MyRenderSystem* renderSystem);
        ~MyConstantBuffer();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        void Update(MyDeviceContextPtr deviceContext, void* buffer);

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

