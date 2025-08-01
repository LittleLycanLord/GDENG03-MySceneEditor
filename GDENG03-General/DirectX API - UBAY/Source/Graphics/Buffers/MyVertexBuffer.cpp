#include "Graphics/Buffers/MyVertexBuffer.hpp"
#include "Core/MyLogger.hpp"
#include "Math/MyMeshVertex.hpp"

using namespace DX3D;

MyVertexBuffer::MyVertexBuffer(void* vertexList, UINT vertexSize, UINT vertexCount, void* shaderByteCode, size_t shaderByteCodeSize, MyRenderSystem* renderSystem) : renderSystem(renderSystem) {
    if (LOG_INFO_VERTEX_BUFFER) std::cout << "[INFO]: MyVertexBuffer constructed" << std::endl;

    ID3D11Device* D3DDevice = this->renderSystem->D3DDevice;

    if (!D3DDevice) {
        std::cerr << "[ERROR]: D3DDevice is null in MyVertexBuffer::Load" << std::endl;
        throw std::exception("D3DDevice is null in MyVertexBuffer::Load");
        return;
    }

    D3D11_BUFFER_DESC bufferDescription = {};
    bufferDescription.Usage = D3D11_USAGE_DEFAULT;
    bufferDescription.ByteWidth = vertexSize * vertexCount;
    bufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bufferDescription.CPUAccessFlags = 0;
    bufferDescription.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA vertexData = {};
    vertexData.pSysMem = vertexList;

    this->vertexSize = vertexSize;
    this->vertexCount = vertexCount;

    HRESULT result = D3DDevice->CreateBuffer(
        &bufferDescription,
        &vertexData,
        &this->D3DVertexBuffer
    );

    if (FAILED(result)) {
        std::cout << "CreateBuffer failed in MyVertexBuffer::Load. HRESULT: 0x" << std::hex << result << std::endl;
        _com_error err(result);
        std::wcout << L"[ERROR]: " << err.ErrorMessage() << std::endl;
        return;
    }

    if (!shaderByteCode || shaderByteCodeSize == 0) {
        std::cerr << "[ERROR]: Invalid shader bytecode in MyVertexBuffer::MyVertexBuffer" << std::endl;
        throw std::exception("Invalid shader bytecode in MyVertexBuffer::MyVertexBuffer");
    }

    // Use the centralized layout from MyMeshVertex to ensure consistency
    D3D11_INPUT_ELEMENT_DESC* layout = MyMeshVertex::GetInputLayout();
    UINT layoutElementCount = MyMeshVertex::GetInputLayoutCount();

    result = D3DDevice->CreateInputLayout(
        layout,
        layoutElementCount,
        shaderByteCode,
        shaderByteCodeSize,
        &this->D3DInputLayout
    );

    if (FAILED(result)) {
        std::cout << "CreateInputLayout failed in MyVertexBuffer::Load. HRESULT: 0x" << std::hex << result << std::endl;
        _com_error err(result);
        std::wcout << L"[ERROR]: " << err.ErrorMessage() << std::endl;
        return;
    }

    if (LOG_INFO_VERTEX_BUFFER)
        std::cout << "[INFO]: Vertex buffer and input layout created successfully" << std::endl;

}
MyVertexBuffer::~MyVertexBuffer() {
    if (LOG_INFO_VERTEX_BUFFER) std::cout << "[INFO]: MyVertexBuffer destructed" << std::endl;

    if (this->D3DInputLayout) this->D3DInputLayout->Release();
    if (this->D3DVertexBuffer) this->D3DVertexBuffer->Release();
}