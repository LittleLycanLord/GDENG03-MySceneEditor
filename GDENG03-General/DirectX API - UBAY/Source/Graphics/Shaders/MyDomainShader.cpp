#include "Graphics/Shaders/MyDomainShader.hpp"
#include "Core/MyLogger.hpp"
#include <iostream>
#include <comdef.h>

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyDomainShader::MyDomainShader(const void* shaderByteCode, size_t shaderSize, MyRenderSystem* renderSystem) : renderSystem(renderSystem) {
    HRESULT result = this->renderSystem->D3DDevice->CreateDomainShader(
        shaderByteCode,
        shaderSize,
        NULL,
        &this->D3DDomainShader
    );
    if (FAILED(result)) {
        std::cout << "CreateDomainShader failed in MyDomainShader::Initialize. HRESULT: 0x" << std::hex << result << std::endl;
        _com_error err(result);
        std::wcout << L"[ERROR]: " << err.ErrorMessage() << std::endl;
        return;
    }
    if (LOG_INFO_DOMAIN_SHADER)
        std::cout << "[INFO]: Domain shader created successfully" << std::endl;
}
MyDomainShader::~MyDomainShader() {
    if (this->D3DDomainShader) {
        this->D3DDomainShader->Release();
        this->D3DDomainShader = nullptr;
        if (LOG_INFO_DOMAIN_SHADER)
            std::cout << "[INFO]: Domain shader released" << std::endl;
    }
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
