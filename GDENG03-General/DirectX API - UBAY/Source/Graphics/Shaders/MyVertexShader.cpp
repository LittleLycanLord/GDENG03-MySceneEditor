#include "Graphics/Shaders/MyVertexShader.hpp"
#include "Core/MyLogger.hpp"

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyVertexShader::MyVertexShader(const void* shaderByteCode, size_t shaderSize, MyRenderSystem* renderSystem) : renderSystem(renderSystem) {
    HRESULT result = this->renderSystem->D3DDevice->CreateVertexShader(
        shaderByteCode,
        shaderSize,
        NULL,
        &this->D3DVertexShader
    );
    if (FAILED(result)) {
        std::cout << "CreateVertexShader failed in MyVertexShader::Initialize. HRESULT: 0x" << std::hex << result << std::endl;
        _com_error err(result);
        std::wcout << L"[ERROR]: " << err.ErrorMessage() << std::endl;
        return;
    }
    if (LOG_INFO_VERTEX_SHADER)
        std::cout << "[INFO]: Vertex shader created successfully" << std::endl;
}
MyVertexShader::~MyVertexShader() {
    if (this->D3DVertexShader) {
        this->D3DVertexShader->Release();
        this->D3DVertexShader = nullptr;
        if (LOG_INFO_VERTEX_SHADER)
            std::cout << "[INFO]: Vertex shader released" << std::endl;
    }
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
