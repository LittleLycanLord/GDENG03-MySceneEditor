#pragma once
#include <d3d11.h>
#include <exception>
#include "Core/Prerequisites.hpp"
#include "Math/MyVector4.hpp"
#include "Core/Resource System/Managers/MyTexture.hpp"
#include "Graphics/MySwapChain.hpp"
#include "Graphics/Buffers/MyConstantBuffer.hpp"

namespace DX3D {
    class MyDeviceContext {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        MyRenderSystem* renderSystem{ nullptr };

        ID3D11DeviceContext* D3DDeviceContext{ nullptr };
        ID3D11RasterizerState* D3DRasterizerState{ nullptr };
        ID3D11SamplerState* D3DSamplerState{ nullptr };

        friend class MyRenderSystem;
        friend class MyConstantBuffer;
    public:
        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyDeviceContext(ID3D11DeviceContext* D3DDeviceContex, MyRenderSystem* renderSystem);
        ~MyDeviceContext();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        bool ClearRenderTargetColor(const MySwapChainPtr& swapChain, MyVector4 color);
        void SetVertexBuffer(const MyVertexBufferPtr& vertexBuffer);
        void SetIndexBuffer(const MyIndexBufferPtr& indexBuffer);
        void SetViewPortSize(UINT width, UINT height);
        void SetHullShader(const MyHullShaderPtr& hullShader);
        void SetDomainShader(const MyDomainShaderPtr& domainShader);
        void SetVertexShader(const MyVertexShaderPtr& vertexShader);
        void SetPixelShader(const MyPixelShaderPtr& pixelShader);
        void SetConstantBuffer(const MyHullShaderPtr& hullShader, const MyConstantBufferPtr& constantBuffer);
        void SetConstantBuffer(const MyDomainShaderPtr& domainShader, const MyConstantBufferPtr& constantBuffer);
        void SetConstantBuffer(const MyVertexShaderPtr& vertexShader, const MyConstantBufferPtr& constantBuffer);
        void SetConstantBuffer(const MyPixelShaderPtr& pixelShader, const MyConstantBufferPtr& constantBuffer);
        
        // Overloads with slot specification for multiple constant buffers
        void SetConstantBuffer(const MyVertexShaderPtr& vertexShader, const MyConstantBufferPtr& constantBuffer, UINT slot);
        void SetConstantBuffer(const MyPixelShaderPtr& pixelShader, const MyConstantBufferPtr& constantBuffer, UINT slot);
        void SetTexture(const MyVertexShaderPtr& vertexShader, const MyTexturePtr& texture);
        void SetTexture(const MyPixelShaderPtr& pixelShader, const MyTexturePtr& texture);
        void SetSamplerState();
        void SetPrimitiveTopology(bool useTessellation);

        void DrawTriangles(UINT vertexCount, UINT startVertexIndex);
        void DrawIndexedTriangles(UINT indexCount, UINT startVertexIndex, UINT startIndexLocation);

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
    public:

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
        ID3D11DeviceContext* GetD3DDeviceContext() const {
            return this->D3DDeviceContext;
        }

    };
} // namespace DX3D

