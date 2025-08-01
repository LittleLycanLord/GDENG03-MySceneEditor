#include "Graphics/MySwapChain.hpp"
#include "Core/MyLogger.hpp"

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MySwapChain::MySwapChain(HWND windowHandle, UINT width, UINT height, MyRenderSystem* renderSystem) : renderSystem(renderSystem) {
    if (LOG_INFO_SWAP_CHAIN) std::cout << "[INFO]: MySwapChain constructed" << std::endl;

    ID3D11Device* D3DDevice = this->renderSystem->D3DDevice;

    DXGI_SWAP_CHAIN_DESC description;
    ZeroMemory(&description, sizeof(description));
    description.BufferCount = 1;
    description.BufferDesc.Width = width;
    description.BufferDesc.Height = height;
    description.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    description.BufferDesc.RefreshRate.Numerator = 60;
    description.BufferDesc.RefreshRate.Denominator = 1;
    description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    description.OutputWindow = windowHandle;
    description.SampleDesc.Count = 1;
    description.SampleDesc.Quality = 0;
    description.Windowed = TRUE;

    if (!windowHandle) {
        std::cerr << "[ERROR]: windowHandle is null in MySwapChain::Initialize" << std::endl;
        throw std::exception("windowHandle is null in MySwapChain::Initialize");
        return;
    }
    if (!D3DDevice) {
        std::cerr << "[ERROR]: D3DDevice is null in MySwapChain::Initialize" << std::endl;
        throw std::exception("D3DDevice is null in MySwapChain::Initialize");
        return;
    }
    if (!this->renderSystem->DXGIFactory) {
        std::cerr << "[ERROR]: DXGIFactory is null in MySwapChain::Initialize" << std::endl;
        throw std::exception("DXGIFactory is null in MySwapChain::Initialize");
        return;
    }

    HRESULT result = this->renderSystem->DXGIFactory->CreateSwapChain(
        D3DDevice,
        &description,
        &this->DXGISwapChain
    );

    if (FAILED(result)) {
        std::cout << "CreateSwapChain failed. HRESULT: 0x" << std::hex << result << std::endl;
        _com_error err(result);
        std::wcout << L"[ERROR]: " << err.ErrorMessage() << std::endl;
        return;
    }

    if (LOG_INFO_SWAP_CHAIN)
        std::cout << "[INFO]: SwapChain created successfully" << std::endl;

    ID3D11Texture2D* backBuffer = nullptr;
    HRESULT getBufferResult = this->DXGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    if (FAILED(getBufferResult) || !backBuffer) {
        std::cout << "GetBuffer failed in MySwapChain::Initialize. HRESULT: 0x" << std::hex << getBufferResult << std::endl;
        _com_error err(getBufferResult);
        std::wcout << L"[ERROR]: " << err.ErrorMessage() << std::endl;
        return;
    }

    result = D3DDevice->CreateRenderTargetView(
        backBuffer,
        NULL,
        &D3D11RenderTargetView
    );
    backBuffer->Release();

    if (FAILED(result)) {
        std::cout << "CreateRenderTargetView failed. HRESULT: 0x" << std::hex << result << std::endl;
        _com_error err(result);
        std::wcout << L"[ERROR]: " << err.ErrorMessage() << std::endl;
        return;
    }

    D3D11_TEXTURE2D_DESC textureDescription = {};
    textureDescription.Width = width;
    textureDescription.Height = height;
    textureDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    textureDescription.Usage = D3D11_USAGE_DEFAULT;
    textureDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    textureDescription.MipLevels = 1;
    textureDescription.SampleDesc.Count = 1;
    textureDescription.SampleDesc.Quality = 0;
    textureDescription.MiscFlags = 0;
    textureDescription.ArraySize = 1;
    textureDescription.CPUAccessFlags = 0;

    result = MyGraphicsEngine::GetInstance()->GetRenderSystem()->D3DDevice->CreateTexture2D(&textureDescription, nullptr, &backBuffer);
    if (FAILED(result)) {
        std::cout << "[ERROR]: Failed to create depth buffer in MySwapChain::Initialize" << std::hex << result << std::endl;
        _com_error err(result);
        std::wcout << L"[ERROR]: " << err.ErrorMessage() << std::endl;
        return;
    }

    result = D3DDevice->CreateDepthStencilView(
        backBuffer,
        NULL,
        &this->D3D11DepthStencilView
    );
    backBuffer->Release();

    if (FAILED(result)) {
        std::cout << "[ERROR]: Failed to create depth stencil view in MySwapChain::Initialize" << std::hex << result << std::endl;
        _com_error err(result);
        std::wcout << L"[ERROR]: " << err.ErrorMessage() << std::endl;
        return;
    }
}
MySwapChain::~MySwapChain() {
    if (LOG_INFO_SWAP_CHAIN) std::cout << "[INFO]: MySwapChain destructed" << std::endl;

    if (D3D11RenderTargetView) {
        D3D11RenderTargetView->Release();
        D3D11RenderTargetView = nullptr;
    }
    if (DXGISwapChain) {
        DXGISwapChain->Release();
        DXGISwapChain = nullptr;
    }
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
bool MySwapChain::Present(bool vsync) {
    if (LOG_INFO_SWAP_CHAIN) std::cout << "[INFO]: MySwapChain::Present called" << std::endl;

    if (this->DXGISwapChain)
        this->DXGISwapChain->Present(vsync, 0);
    else
        throw std::exception("DXGISwapChain is null in MySwapChain::Present");
    return true;
}
//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
