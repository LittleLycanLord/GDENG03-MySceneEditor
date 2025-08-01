#include "Graphics/Shaders/MyPixelShader.hpp"
#include "Core/MyLogger.hpp"

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyPixelShader::MyPixelShader(const void* shaderByteCode, size_t shaderSize, MyRenderSystem* renderSystem) : renderSystem(renderSystem) {
    HRESULT result = this->renderSystem->D3DDevice->CreatePixelShader(
        shaderByteCode,
        shaderSize,
        NULL,
        &this->D3DPixelShader
    );
    if (FAILED(result)) {
        std::cout << "CreatePixelShader failed in MyPixelShader::Initialize. HRESULT: 0x" << std::hex << result << std::endl;
        _com_error err(result);
        std::wcout << L"[ERROR]: " << err.ErrorMessage() << std::endl;
        return;
    }
    if (LOG_INFO_PIXEL_SHADER)
        std::cout << "[INFO]: Pixel shader created successfully" << std::endl;

}
MyPixelShader::~MyPixelShader() {
    if (this->D3DPixelShader) {
        this->D3DPixelShader->Release();
        this->D3DPixelShader = nullptr;
        if (LOG_INFO_PIXEL_SHADER)
            std::cout << "[INFO]: Pixel shader released" << std::endl;
    }
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
