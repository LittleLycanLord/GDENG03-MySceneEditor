#pragma once
#include <d3d11.h>
#include <exception>
#include "Core/Prerequisites.hpp"
#include "Core/MyRenderSystem.hpp"
#include "Graphics/MyGraphicsEngine.hpp"
#include "Graphics/MyDeviceContext.hpp"

namespace DX3D {
    class MyVertexShader {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        MyRenderSystem* renderSystem { nullptr };
        
        ID3D11VertexShader* D3DVertexShader{ nullptr };

        friend class MyRenderSystem;
        friend class MyDeviceContext;
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyVertexShader(const void* shaderByteCode, size_t shaderSize, MyRenderSystem* renderSystem);
        ~MyVertexShader();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
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

