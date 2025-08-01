#include "Graphics/Buffers/MyIndexBuffer.hpp"
#include "Core/MyLogger.hpp"

using namespace DX3D;

MyIndexBuffer::MyIndexBuffer(void* indices, UINT indexCount, MyRenderSystem* renderSystem) : renderSystem(renderSystem) {
    if (LOG_INFO_INDEX_BUFFER) std::cout << "[INFO]: MyIndexBuffer constructed" << std::endl;


    if (this->D3DIndexBuffer) {
        if (LOG_INFO_INDEX_BUFFER) std::cout << "[INFO]: Releasing previous D3DIndexBuffer in MyIndexBuffer::Load" << std::endl;
        this->D3DIndexBuffer->Release();
        this->D3DIndexBuffer = nullptr;
    }

    ID3D11Device* D3DDevice = this->renderSystem->D3DDevice;

    if (!D3DDevice) {
        std::cerr << "[ERROR]: D3DDevice is null in MyIndexBuffer::Load" << std::endl;
        throw std::exception("D3DDevice is null in MyIndexBuffer::Load");
        return;
    }
    if (!indices) {
        std::cerr << "[ERROR]: indices pointer is null in MyIndexBuffer::Load" << std::endl;
        throw std::exception("indices pointer is null in MyIndexBuffer::Load");
        return;
    }
    if (indexCount == 0) {
        std::cerr << "[ERROR]: indexCount is zero in MyIndexBuffer::Load" << std::endl;
        throw std::exception("indexCount is zero in MyIndexBuffer::Load");
        return;
    }

    D3D11_BUFFER_DESC bufferDescription = {};
    bufferDescription.Usage = D3D11_USAGE_DEFAULT;
    bufferDescription.ByteWidth = 4 * indexCount;
    bufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bufferDescription.CPUAccessFlags = 0;
    bufferDescription.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA indexData = {};
    indexData.pSysMem = indices;
    this->indexCount = indexCount;

    HRESULT result = D3DDevice->CreateBuffer(
        &bufferDescription,
        &indexData,
        &this->D3DIndexBuffer
    );

    if (FAILED(result)) {
        std::cout << "CreateBuffer failed in MyIndexBuffer::Load. HRESULT: 0x" << std::hex << result << std::endl;
        _com_error err(result);
        std::wcout << L"[ERROR]: " << err.ErrorMessage() << std::endl;
        return;
    }

    if (LOG_INFO_INDEX_BUFFER)
        std::cout << "[INFO]: Index buffer created successfully" << std::endl;
}
MyIndexBuffer::~MyIndexBuffer() {
    if (LOG_INFO_INDEX_BUFFER) std::cout << "[INFO]: MyIndexBuffer destructed" << std::endl;


    if (this->D3DIndexBuffer) {
        this->D3DIndexBuffer->Release();
        this->D3DIndexBuffer = nullptr;
        if (LOG_INFO_INDEX_BUFFER)
            std::cout << "[INFO]: Index buffer released" << std::endl;
    }
}
