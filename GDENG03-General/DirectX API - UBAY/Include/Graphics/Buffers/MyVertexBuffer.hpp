#pragma once
#include <iostream>
#include <comdef.h>
#include <exception>
#include <d3d11.h>
#include "Core/MyRenderSystem.hpp"
#include "Core/Prerequisites.hpp"

namespace DX3D {
    class MyVertexBuffer {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        MyRenderSystem* renderSystem{ nullptr };

        UINT vertexSize{ 0 };
        UINT vertexCount{ 0 };
        ID3D11Buffer* D3DVertexBuffer{ nullptr };
        ID3D11InputLayout* D3DInputLayout{ nullptr };

        friend class MyDeviceContext;
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyVertexBuffer(void* vertexList, UINT vertexSize, UINT vertexCount, void* shaderByteCode, size_t shaderByteCodeSize, MyRenderSystem* renderSystem);
        ~MyVertexBuffer();

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
        UINT GetVertexCount() const { return vertexCount; }
        UINT GetVertexSize() const { return vertexSize; }
    };
} // namespace DX3D

