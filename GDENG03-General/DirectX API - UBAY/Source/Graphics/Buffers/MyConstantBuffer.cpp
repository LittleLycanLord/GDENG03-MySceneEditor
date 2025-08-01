#include "Graphics/Buffers/MyConstantBuffer.hpp"
#include "Core/MyLogger.hpp"

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyConstantBuffer::MyConstantBuffer(void* buffer, UINT bufferSize, MyRenderSystem* renderSystem) : renderSystem(renderSystem) {
    if (LOG_INFO_CONSTANT_BUFFER) std::cout << "[INFO]: MyConstantBuffer constructed" << std::endl;

    ID3D11Device* D3DDevice = this->renderSystem->D3DDevice;

    if (!D3DDevice) {
        std::cerr << "[ERROR]: D3DDevice is null in MyConstantBuffer::MyConstantBuffer" << std::endl;
        throw std::exception("D3DDevice is null in MyConstantBuffer::MyConstantBuffer");
    }

    if (!buffer) {
        std::cerr << "[ERROR]: Buffer data is null in MyConstantBuffer::MyConstantBuffer" << std::endl;
        throw std::exception("Buffer data is null in MyConstantBuffer::MyConstantBuffer");
    }

    // Validate buffer size alignment (DirectX requires 16-byte alignment for constant buffers)
    if (bufferSize % 16 != 0) {
        std::cerr << "[WARNING]: Constant buffer size (" << bufferSize
            << ") is not 16-byte aligned. This may cause issues on some hardware." << std::endl;
        // Round up to next 16-byte boundary
        bufferSize = ((bufferSize + 15) / 16) * 16;
        std::cout << "[INFO]: Adjusted buffer size to " << bufferSize << " bytes for alignment." << std::endl;
    }

    D3D11_BUFFER_DESC bufferDescription = {};
    bufferDescription.Usage = D3D11_USAGE_DEFAULT;
    bufferDescription.ByteWidth = bufferSize;
    bufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bufferDescription.CPUAccessFlags = 0;
    bufferDescription.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA constantData = {};
    constantData.pSysMem = buffer;

    HRESULT result = D3DDevice->CreateBuffer(
        &bufferDescription,
        &constantData,
        &this->D3DConstantBuffer
    );

    if (FAILED(result)) {
        std::cout << "CreateBuffer failed in MyConstantBuffer::MyConstantBuffer. HRESULT: 0x" << std::hex << result << std::endl;
        _com_error err(result);
        std::wcout << L"[ERROR]: " << err.ErrorMessage() << std::endl;
        throw std::exception("Failed to create constant buffer");
    }

    if (LOG_INFO_CONSTANT_BUFFER)
        std::cout << "[INFO]: Constant buffer created successfully with size: " << bufferSize << " bytes" << std::endl;
}
MyConstantBuffer::~MyConstantBuffer() {
    if (LOG_INFO_CONSTANT_BUFFER) std::cout << "[INFO]: MyConstantBuffer destructed" << std::endl;

    if (this->D3DConstantBuffer) {
        this->D3DConstantBuffer->Release();
        this->D3DConstantBuffer = nullptr;
        if (LOG_INFO_CONSTANT_BUFFER)
            std::cout << "[INFO]: Constant buffer released" << std::endl;
    }
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
void MyConstantBuffer::Update(MyDeviceContextPtr deviceContext, void* buffer) {
    if (LOG_INFO_CONSTANT_BUFFER)
        std::cout << "[INFO]: Updating constant buffer..." << std::endl;
    deviceContext->D3DDeviceContext->UpdateSubresource(
        this->D3DConstantBuffer,
        NULL,
        NULL,
        buffer,
        NULL,
        NULL
    );
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
