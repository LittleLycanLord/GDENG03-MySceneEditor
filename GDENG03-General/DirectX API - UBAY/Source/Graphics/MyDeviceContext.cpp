#include "Graphics/MyDeviceContext.hpp"
#include "Core/Prerequisites.hpp"
#include "Core/MyLogger.hpp"
#include <iostream>

using namespace DX3D;

MyDeviceContext::MyDeviceContext(ID3D11DeviceContext* D3DDeviceContext, MyRenderSystem* renderSystem) : renderSystem(renderSystem) {
    this->D3DDeviceContext = D3DDeviceContext;
    if (LOG_INFO_DEVICE_CONTEXT) std::cout << "[INFO]: MyDeviceContext constructed" << std::endl;
}
MyDeviceContext::~MyDeviceContext() {
    if (LOG_INFO_DEVICE_CONTEXT) std::cout << "[INFO]: MyDeviceContext destructed" << std::endl;
    
    if (this->D3DRasterizerState) {
        this->D3DRasterizerState->Release();
        this->D3DRasterizerState = nullptr;
    }
    
    if (this->D3DSamplerState) {
        this->D3DSamplerState->Release();
        this->D3DSamplerState = nullptr;
    }

    if (this->D3DDeviceContext) {
        this->D3DDeviceContext->Release();
        this->D3DDeviceContext = nullptr;
    }
}

bool MyDeviceContext::ClearRenderTargetColor(const MySwapChainPtr& swapChain, MyVector4 color) {
    if (LOG_INFO_DEVICE_CONTEXT) std::cout << "[INFO] MyDeviceContext::ClearRenderTargetColor called" << std::endl;
    if (!swapChain || !swapChain->D3D11RenderTargetView) {
        std::cerr << "[ERROR]: swapChain or D3D11RenderTargetView is null in MyDeviceContext::ClearRenderTargetColor" << std::endl;
        throw std::exception("swapChain or D3D11RenderTargetView is null in MyDeviceContext::ClearRenderTargetColor");
        return false;
    }
    if (!this->D3DDeviceContext) {
        std::cerr << "[ERROR]: D3DDeviceContext is null in MyDeviceContext::ClearRenderTargetColor" << std::endl;
        throw std::exception("D3DDeviceContext is null in MyDeviceContext::ClearRenderTargetColor");
        return false;
    }
    FLOAT clearColor[4] = { color.x, color.y, color.z,  color.w };
    this->D3DDeviceContext->ClearRenderTargetView(
        swapChain->D3D11RenderTargetView,
        clearColor
    );
    this->D3DDeviceContext->ClearDepthStencilView(
        swapChain->D3D11DepthStencilView,
        D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0
    );
    this->D3DDeviceContext->OMSetRenderTargets(
        1,
        &swapChain->D3D11RenderTargetView,
        swapChain->D3D11DepthStencilView
    );
    return true;
}

void MyDeviceContext::SetVertexBuffer(const MyVertexBufferPtr& vertexBuffer) {
    if (LOG_INFO_DEVICE_CONTEXT) std::cout << "[INFO]: MyDeviceContext::SetVertexBuffer called" << std::endl;
    if (!vertexBuffer || !vertexBuffer->D3DVertexBuffer || !vertexBuffer->D3DInputLayout) {
        throw std::exception("vertexBuffer, vertexBuffer->vertexBuffer, or inputLayout is null in MyDeviceContext::SetVertexBuffer");
        return;
    }
    if (!this->D3DDeviceContext) {
        throw std::exception("D3DDeviceContext is null in MyDeviceContext::SetVertexBuffer");
        return;
    }
    UINT stride = vertexBuffer->vertexSize;
    UINT offset = 0;
    this->D3DDeviceContext->IASetVertexBuffers(
        0,
        1,
        &vertexBuffer->D3DVertexBuffer,
        &stride,
        &offset
    );
    this->D3DDeviceContext->IASetInputLayout(vertexBuffer->D3DInputLayout);
}

void MyDeviceContext::SetIndexBuffer(const MyIndexBufferPtr& indexBuffer) {
    if (LOG_INFO_DEVICE_CONTEXT) std::cout << "[INFO]: MyDeviceContext::SetIndexBuffer called" << std::endl;
    if (!indexBuffer || !indexBuffer->D3DIndexBuffer) {
        throw std::exception("indexBuffer, indexBuffer->D3DIndexBuffer, is null in MyDeviceContext::SetIndexBuffer");
        return;
    }
    if (!this->D3DDeviceContext) {
        throw std::exception("D3DDeviceContext is null in MyDeviceContext::SetIndexBuffer");
        return;
    }
    this->D3DDeviceContext->IASetIndexBuffer(
        indexBuffer->D3DIndexBuffer,
        DXGI_FORMAT_R32_UINT,
        0
    );
}

void MyDeviceContext::SetViewPortSize(UINT width, UINT height) {
    if (LOG_INFO_DEVICE_CONTEXT) std::cout << "[INFO]: MyDeviceContext::SetViewPortSize called" << std::endl;
    if (!this->D3DDeviceContext) {
        throw std::exception("D3DDeviceContext is null in MyDeviceContext::SetViewPortSize");
        return;
    }
    D3D11_VIEWPORT viewport = {};
    viewport.Width = (FLOAT)width;
    viewport.Height = (FLOAT)height;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = 0.0f;
    viewport.TopLeftY = 0.0f;
    this->D3DDeviceContext->RSSetViewports(1, &viewport);
}

void MyDeviceContext::SetHullShader(const MyHullShaderPtr& hullShader) {
    if (LOG_INFO_DEVICE_CONTEXT) std::cout << "[INFO]: MyDeviceContext::SetHullShader called" << std::endl;
    if (!this->D3DDeviceContext) {
        throw std::exception("D3DDeviceContext is null in MyDeviceContext::SetHullShader");
        return;
    }
    
    // Allow null hull shader to disable tessellation
    if (!hullShader) {
        this->D3DDeviceContext->HSSetShader(nullptr, nullptr, 0);
        return;
    }
    
    if (!hullShader->D3DHullShader) {
        throw std::exception("D3DHullShader is null in MyDeviceContext::SetHullShader");
        return;
    }
    
    this->D3DDeviceContext->HSSetShader(
        hullShader->D3DHullShader,
        nullptr,
        0
    );
}

void MyDeviceContext::SetDomainShader(const MyDomainShaderPtr& domainShader) {
    if (LOG_INFO_DEVICE_CONTEXT) std::cout << "[INFO]: MyDeviceContext::SetDomainShader called" << std::endl;
    if (!this->D3DDeviceContext) {
        throw std::exception("D3DDeviceContext is null in MyDeviceContext::SetDomainShader");
        return;
    }
    
    // Allow null domain shader to disable tessellation
    if (!domainShader) {
        this->D3DDeviceContext->DSSetShader(nullptr, nullptr, 0);
        return;
    }
    
    if (!domainShader->D3DDomainShader) {
        throw std::exception("D3DDomainShader is null in MyDeviceContext::SetDomainShader");
        return;
    }
    
    this->D3DDeviceContext->DSSetShader(
        domainShader->D3DDomainShader,
        nullptr,
        0
    );
}

void MyDeviceContext::SetVertexShader(const MyVertexShaderPtr& vertexShader) {
    if (LOG_INFO_DEVICE_CONTEXT) std::cout << "[INFO]: MyDeviceContext::SetVertexShader called" << std::endl;
    if (!vertexShader || !vertexShader->D3DVertexShader) {
        throw std::exception("vertexShader or D3DVertexShader is null in MyDeviceContext::SetVertexShader");
        return;
    }
    if (!this->D3DDeviceContext) {
        throw std::exception("D3DDeviceContext is null in MyDeviceContext::SetVertexShader");
        return;
    }
    this->D3DDeviceContext->VSSetShader(
        vertexShader->D3DVertexShader,
        nullptr,
        0
    );
}

void MyDeviceContext::SetPixelShader(const MyPixelShaderPtr& pixelShader) {
    if (LOG_INFO_DEVICE_CONTEXT) std::cout << "[INFO]: MyDeviceContext::SetPixelShader called" << std::endl;
    if (!pixelShader || !pixelShader->D3DPixelShader) {
        throw std::exception("pixelShader or D3DPixelShader is null in MyDeviceContext::SetPixelShader");
        return;
    }
    if (!this->D3DDeviceContext) {
        throw std::exception("D3DDeviceContext is null in MyDeviceContext::SetPixelShader");
        return;
    }
    this->D3DDeviceContext->PSSetShader(
        pixelShader->D3DPixelShader,
        nullptr,
        0
    );
}

void MyDeviceContext::SetConstantBuffer(const MyHullShaderPtr& hullShader, const MyConstantBufferPtr& constantBuffer) {
    this->D3DDeviceContext->HSSetConstantBuffers(
        0,
        1,
        &constantBuffer->D3DConstantBuffer
    );
}

void MyDeviceContext::SetConstantBuffer(const MyDomainShaderPtr& domainShader, const MyConstantBufferPtr& constantBuffer) {
    this->D3DDeviceContext->DSSetConstantBuffers(
        0,
        1,
        &constantBuffer->D3DConstantBuffer
    );
}

void MyDeviceContext::SetConstantBuffer(const MyVertexShaderPtr& vertexShader, const MyConstantBufferPtr& constantBuffer) {
    this->D3DDeviceContext->VSSetConstantBuffers(
        0,
        1,
        &constantBuffer->D3DConstantBuffer
    );
}

void MyDeviceContext::SetConstantBuffer(const MyPixelShaderPtr& pixelShader, const MyConstantBufferPtr& constantBuffer) {
    this->D3DDeviceContext->PSSetConstantBuffers(
        0,
        1,
        &constantBuffer->D3DConstantBuffer
    );
}

// Overloaded methods with slot specification
void MyDeviceContext::SetConstantBuffer(const MyVertexShaderPtr& vertexShader, const MyConstantBufferPtr& constantBuffer, UINT slot) {
    this->D3DDeviceContext->VSSetConstantBuffers(
        slot,
        1,
        &constantBuffer->D3DConstantBuffer
    );
}

void MyDeviceContext::SetConstantBuffer(const MyPixelShaderPtr& pixelShader, const MyConstantBufferPtr& constantBuffer, UINT slot) {
    this->D3DDeviceContext->PSSetConstantBuffers(
        slot,
        1,
        &constantBuffer->D3DConstantBuffer
    );
}

void MyDeviceContext::DrawTriangles(UINT vertexCount, UINT startVertexIndex) {
    if (LOG_INFO_DEVICE_CONTEXT) std::cout << "[INFO]: MyDeviceContext::DrawTriangles called with vertexCount=" << vertexCount << ", startVertexIndex=" << startVertexIndex << std::endl;
    if (!this->D3DDeviceContext) {
        throw std::exception("D3DDeviceContext is null in MyDeviceContext::DrawTriangles");
        return;
    }
    // Primitive topology should be set externally via SetPrimitiveTopology
    this->D3DDeviceContext->Draw(vertexCount, startVertexIndex);
}

void MyDeviceContext::DrawIndexedTriangles(UINT indexCount, UINT startVertexIndex, UINT startIndexLocation) {
    if (LOG_INFO_DEVICE_CONTEXT) std::cout << "[INFO]: MyDeviceContext::DrawIndexedTriangles called with indexCount=" << indexCount << ", startVertexIndex=" << startVertexIndex << ", startIndexLocation=" << startIndexLocation << std::endl;
    if (!this->D3DDeviceContext) {
        throw std::exception("D3DDeviceContext is null in MyDeviceContext::DrawIndexedTriangles");
        return;
    }
    // Primitive topology should be set externally via SetPrimitiveTopology
    this->D3DDeviceContext->DrawIndexed(indexCount, startIndexLocation, startVertexIndex);
}

void MyDeviceContext::SetPrimitiveTopology(bool useTessellation) {
    if (LOG_INFO_DEVICE_CONTEXT) std::cout << "[INFO]: MyDeviceContext::SetPrimitiveTopology called with useTessellation=" << useTessellation << std::endl;
    if (!this->D3DDeviceContext) {
        throw std::exception("D3DDeviceContext is null in MyDeviceContext::SetPrimitiveTopology");
        return;
    }
    
    if (useTessellation) {
        this->D3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);
    } else {
        this->D3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }
}

void MyDeviceContext::SetTexture(const MyVertexShaderPtr& vertexShader, const MyTexturePtr& texture) {
    this->D3DDeviceContext->VSSetShaderResources(
        0,
        1,
        &texture->D3DShaderResourceView
    );
}

void MyDeviceContext::SetTexture(const MyPixelShaderPtr& pixelShader, const MyTexturePtr& texture) {
    this->D3DDeviceContext->PSSetShaderResources(
        0,
        1,
        &texture->D3DShaderResourceView
    );
}

void MyDeviceContext::SetSamplerState() {
    if (!this->D3DSamplerState) {
        D3D11_SAMPLER_DESC samplerDesc = {};
        samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
        samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
        samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
        samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
        samplerDesc.MinLOD = 0;
        samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
        HRESULT result = MyGraphicsEngine::GetInstance()->GetRenderSystem()->D3DDevice->CreateSamplerState(&samplerDesc, &this->D3DSamplerState);
        if (FAILED(result)) {
            std::cerr << "[ERROR]: Failed to create sampler state" << std::endl;
            throw std::runtime_error("Failed to create sampler state");
        }
    }
    this->D3DDeviceContext->PSSetSamplers(0, 1, &this->D3DSamplerState);
}

