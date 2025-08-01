#include "Graphics/Shaders/MyHullShader.hpp"
#include "Core/MyLogger.hpp"
#include <iostream>
#include <comdef.h>

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyHullShader::MyHullShader(const void* shaderByteCode, size_t shaderSize, MyRenderSystem* renderSystem) : renderSystem(renderSystem) {
    HRESULT result = this->renderSystem->D3DDevice->CreateHullShader(
        shaderByteCode,
        shaderSize,
        NULL,
        &this->D3DHullShader
    );
    if (FAILED(result)) {
        std::cout << "CreateHullShader failed in MyHullShader::Initialize. HRESULT: 0x" << std::hex << result << std::endl;
        _com_error err(result);
        std::wcout << L"[ERROR]: " << err.ErrorMessage() << std::endl;
        return;
    }
    if (LOG_INFO_HULL_SHADER)
        std::cout << "[INFO]: Hull shader created successfully" << std::endl;
}
MyHullShader::~MyHullShader() {
    if (this->D3DHullShader) {
        this->D3DHullShader->Release();
        this->D3DHullShader = nullptr;
        if (LOG_INFO_HULL_SHADER)
            std::cout << "[INFO]: Hull shader released" << std::endl;
    }
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
