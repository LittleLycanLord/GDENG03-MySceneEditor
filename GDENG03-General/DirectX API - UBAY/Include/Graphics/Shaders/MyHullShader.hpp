#pragma once
#include <d3d11.h>
#include <exception>
#include "Core/Prerequisites.hpp"
#include "Core/MyRenderSystem.hpp"
#include "Graphics/MyGraphicsEngine.hpp"
#include "Graphics/MyDeviceContext.hpp"

namespace DX3D {
    class MyHullShader {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        MyRenderSystem* renderSystem { nullptr };
        
        ID3D11HullShader* D3DHullShader{ nullptr };

        friend class MyRenderSystem;
        friend class MyDeviceContext;
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyHullShader(const void* shaderByteCode, size_t shaderSize, MyRenderSystem* renderSystem);
        ~MyHullShader();

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

