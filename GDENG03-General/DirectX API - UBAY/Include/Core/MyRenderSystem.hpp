#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <iostream>
#include <comdef.h>
#include <exception>
#include "Core/Prerequisites.hpp"
#include "Graphics/MySwapChain.hpp"
#include "Graphics/MyDeviceContext.hpp"
#include "Graphics/Buffers/MyVertexBuffer.hpp"
#include "Graphics/Buffers/MyConstantBuffer.hpp"
#include "Graphics/Buffers/MyIndexBuffer.hpp"
#include "Graphics/Shaders/MyHullShader.hpp"
#include "Graphics/Shaders/MyDomainShader.hpp"
#include "Graphics/Shaders/MyVertexShader.hpp"
#include "Graphics/Shaders/MyPixelShader.hpp"
#include "Core/Resource System/Managers/MyTexture.hpp"

namespace DX3D {
    class MyRenderSystem {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        ID3D11Device* D3DDevice{ nullptr };
        MyDeviceContextPtr immediateDeviceContext{ nullptr };
        ID3D11DeviceContext* D3DDeviceContext{ nullptr };
        IDXGIDevice* DXGIDevice{ nullptr };
        IDXGIAdapter* DXGIAdapter{ nullptr };
        IDXGIFactory* DXGIFactory{ nullptr };
        D3D_FEATURE_LEVEL featureLevel{ D3D_FEATURE_LEVEL_11_0 };

        ID3DBlob* temporaryBlob{ nullptr };
        ID3DBlob* vertexShaderBlob{ nullptr };
        ID3DBlob* pixelShaderBlob{ nullptr };
        ID3D11HullShader* D3DHullShader{ nullptr };
        ID3D11DomainShader* D3DDomainShader{ nullptr };
        ID3D11VertexShader* D3DVertexShader{ nullptr };
        ID3D11PixelShader* D3DPixelShader{ nullptr };

        friend class MySwapChain;
        friend class MyVertexBuffer;
        friend class MyConstantBuffer;
        friend class MyIndexBuffer;
        friend class MyHullShader;
        friend class MyDomainShader;
        friend class MyVertexShader;
        friend class MyPixelShader;
        friend class MyTexture;
        friend class MyDeviceContext;
        friend class MyLogger;
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyRenderSystem();
        ~MyRenderSystem();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        MySwapChainPtr CreateSwapChain(HWND windowHandle, UINT width, UINT height);
        MyVertexBufferPtr CreateVertexBuffer(void* vertexList, UINT vertexSize, UINT vertexCount, void* shaderByteCode, size_t shaderByteCodeSize);
        MyConstantBufferPtr CreateConstantBuffer(void* buffer, UINT bufferSize);
        MyIndexBufferPtr CreateIndexBuffer(void* indices, UINT indexCount);
        MyHullShaderPtr CreateHullShader(const void* shaderByteCode, size_t shaderSize);
        MyDomainShaderPtr CreateDomainShader(const void* shaderByteCode, size_t shaderSize);
        MyVertexShaderPtr CreateVertexShader(const void* shaderByteCode, size_t shaderSize);
        MyPixelShaderPtr CreatePixelShader(const void* shaderByteCode, size_t shaderSize);

        bool CompileHullShader(const wchar_t* fileName, const char* entryPoint, void** shaderByteCode, size_t* shaderSize);
        bool CompileDomainShader(const wchar_t* fileName, const char* entryPoint, void** shaderByteCode, size_t* shaderSize);
        bool CompileVertexShader(const wchar_t* fileName, const char* entryPoint, void** shaderByteCode, size_t* shaderSize);
        bool CompilePixelShader(const wchar_t* fileName, const char* entryPoint, void** shaderByteCode, size_t* shaderSize);
        bool ReleaseCompiledShader();

        void ToggleWireframeMode(bool enabled);
        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
    public:

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
        MyDeviceContextPtr GetImmediateDeviceContext() const { return this->immediateDeviceContext; }
        ID3D11Device* GetD3DDevice() const { return this->D3DDevice; }
    };
} // namespace DX3D

