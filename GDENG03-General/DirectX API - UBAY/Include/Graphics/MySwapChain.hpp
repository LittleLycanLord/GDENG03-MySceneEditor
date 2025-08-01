#pragma once
#include <d3d11.h>
#include <Windows.h>
#include <iostream>
#include <comdef.h>
#include <exception>
#include "Core/Prerequisites.hpp"
#include "Core/MyRenderSystem.hpp"
#include "Graphics/MyGraphicsEngine.hpp"

namespace DX3D {
    class MySwapChain {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        MyRenderSystem* renderSystem{ nullptr };

        IDXGISwapChain* DXGISwapChain;
        ID3D11RenderTargetView* D3D11RenderTargetView{ nullptr };
        ID3D11DepthStencilView* D3D11DepthStencilView{ nullptr };

        friend class MyDeviceContext;
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MySwapChain(HWND windowHandle, UINT width, UINT height, MyRenderSystem* renderSystem);
        ~MySwapChain();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        bool Present(bool vsync);


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

