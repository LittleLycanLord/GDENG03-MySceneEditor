#include "Core/Resource System/Managers/MyTexture.hpp"
#include "Core/MyLogger.hpp"

using namespace DX3D;
using namespace DirectX;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyTexture::MyTexture(const wchar_t* resourcePath) : MyResource(resourcePath) {
    if (LOG_INFO_TEXTURE) std::wcout << L"[INFO]: MyTexture constructed for " << resourcePath << std::endl;
    ScratchImage image;

    HRESULT result = LoadFromWICFile(resourcePath, WIC_FLAGS_NONE, nullptr, image);

    if (SUCCEEDED(result)) {
        result = CreateTexture(MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetD3DDevice(),
            image.GetImages(), image.GetImageCount(), image.GetMetadata(), &this->D3DTexture);

        if (FAILED(result)) {
            std::cerr << "[ERROR]: Failed to create D3D texture from image data" << std::endl;
            throw std::runtime_error("Failed to create D3D texture from image data");
        }

        // Use nullptr for SRV description for standard 2D textures
        HRESULT srvResult = MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetD3DDevice()->CreateShaderResourceView(
            this->D3DTexture, nullptr, &this->D3DShaderResourceView);

        if (FAILED(srvResult)) {
            std::cerr << "[ERROR]: Failed to create shader resource view for texture" << std::endl;
            throw std::runtime_error("Failed to create shader resource view for texture");
        }

        if (LOG_INFO_TEXTURE) std::wcout << L"[INFO]: Texture loaded and SRV created: " << resourcePath << std::endl;
    }
    else {
        std::cerr << "[ERROR]: Failed to load texture from file" << std::endl;
        throw std::runtime_error("Failed to load texture from file");
    }
}
MyTexture::~MyTexture() {
    if (LOG_INFO_TEXTURE) std::cout << "[INFO]: MyTexture destructed" << std::endl;
    if (this->D3DShaderResourceView) {
        this->D3DShaderResourceView->Release();
        this->D3DShaderResourceView = nullptr;
        if (LOG_INFO_TEXTURE) std::cout << "[INFO]: Shader resource view released" << std::endl;
    }
    if (this->D3DTexture) {
        this->D3DTexture->Release();
        this->D3DTexture = nullptr;
        if (LOG_INFO_TEXTURE) std::cout << "[INFO]: D3D texture released" << std::endl;
    }
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
