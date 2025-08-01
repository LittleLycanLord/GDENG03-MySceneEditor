#include "Core/MyRenderSystem.hpp"
#include "Core/MyLogger.hpp"

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyRenderSystem::MyRenderSystem() {
    PERFORMANCE_TIMER("RENDERSYSTEM", "MyRenderSystem Constructor");
    if (LOG_INFO_RENDER_SYSTEM) std::cout << "[INFO]: MyRenderSystem constructed" << std::endl;
    LOG_INFO("RENDERSYSTEM", "Initializing DirectX 11 render system");

    D3D_DRIVER_TYPE driverTypes[] = {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE
    };

    D3D_FEATURE_LEVEL featureLevels[] = {
        D3D_FEATURE_LEVEL_11_0
    };

    HRESULT result = 0;
    for (UINT driverTypeIndex = 0; driverTypeIndex < ARRAYSIZE(driverTypes); ) {
        LOG_DEBUG("RENDERSYSTEM", "Attempting to create D3D11 device with driver type: " + std::to_string(driverTypeIndex));
        result = D3D11CreateDevice(
            NULL,
            driverTypes[driverTypeIndex],
            NULL,
            D3D11_CREATE_DEVICE_DEBUG,
            featureLevels,
            ARRAYSIZE(featureLevels),
            D3D11_SDK_VERSION,
            &this->D3DDevice,
            &this->featureLevel,
            &this->D3DDeviceContext
        );
        if (SUCCEEDED(result)) {
            LOG_INFO("RENDERSYSTEM", "D3D11 device created successfully with driver type: " + std::to_string(driverTypeIndex));
            break;
        }

        driverTypeIndex++;
    }

    if (FAILED(result)) {
        LOG_ERROR("RENDERSYSTEM", "D3D11CreateDevice failed with HRESULT: 0x" + std::to_string(result));
        std::cout << "D3D11CreateDevice failed in MyRenderSystem::Initialize. HRESULT: 0x" << std::hex << result << std::endl;
        _com_error err(result);
        std::wcout << L"[ERROR]: " << err.ErrorMessage() << std::endl;
        return;
    }

    if (LOG_INFO_RENDER_SYSTEM)
        std::cout << "[INFO]: D3D11 Device created successfully" << std::endl;
    LOG_INFO("RENDERSYSTEM", "D3D11 Device and device context created successfully");

    immediateDeviceContext = std::make_shared<MyDeviceContext>(this->D3DDeviceContext, this);

    HRESULT hr = this->D3DDevice->QueryInterface(
        __uuidof(IDXGIDevice),
        (void**)&this->DXGIDevice
    );
    if (FAILED(hr)) {
        std::cout << "QueryInterface for IDXGIDevice failed in MyRenderSystem::Initialize. HRESULT: 0x" << std::hex << hr << std::endl;
        _com_error err(hr);
        std::wcout << L"[ERROR]: " << err.ErrorMessage() << std::endl;
        return;
    }
    hr = this->DXGIDevice->GetParent(
        __uuidof(IDXGIAdapter),
        (void**)&this->DXGIAdapter
    );
    if (FAILED(hr)) {
        std::cout << "GetParent for IDXGIAdapter failed in MyRenderSystem::Initialize. HRESULT: 0x" << std::hex << hr << std::endl;
        _com_error err(hr);
        std::wcout << L"[ERROR]: " << err.ErrorMessage() << std::endl;
        return;
    }
    hr = this->DXGIAdapter->GetParent(
        __uuidof(IDXGIFactory),
        (void**)&this->DXGIFactory
    );
    if (FAILED(hr)) {
        std::cout << "GetParent for IDXGIFactory failed in MyRenderSystem::Initialize. HRESULT: 0x" << std::hex << hr << std::endl;
        _com_error err(hr);
        std::wcout << L"[ERROR]: " << err.ErrorMessage() << std::endl;
        return;
    }

    // Disable face culling for debugging
    // D3D11_RASTERIZER_DESC rasterDesc = {};
    // rasterDesc.FillMode = D3D11_FILL_SOLID;
    // rasterDesc.CullMode = D3D11_CULL_NONE;
    // rasterDesc.FrontCounterClockwise = FALSE;
    // rasterDesc.DepthClipEnable = TRUE;
    // ID3D11RasterizerState* rasterState = nullptr;
    // this->D3DDevice->CreateRasterizerState(&rasterDesc, &rasterState);
    // this->D3DDeviceContext->RSSetState(rasterState);
    // if (rasterState) rasterState->Release();

}
MyRenderSystem::~MyRenderSystem() {
    if (LOG_INFO_RENDER_SYSTEM) std::cout << "[INFO]: MyRenderSystem destructed" << std::endl;

    if (this->DXGIDevice) {
        this->DXGIDevice->Release();
        this->DXGIDevice = nullptr;
    }
    if (this->DXGIAdapter) {
        this->DXGIAdapter->Release();
        this->DXGIAdapter = nullptr;
    }
    if (this->DXGIFactory) {
        this->DXGIFactory->Release();
        this->DXGIFactory = nullptr;
    }
    if (this->D3DDevice) {
        this->D3DDevice->Release();
        this->D3DDevice = nullptr;
    }

    this->immediateDeviceContext = nullptr;
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
MySwapChainPtr MyRenderSystem::CreateSwapChain(HWND windowHandle, UINT width, UINT height) {
    PERFORMANCE_TIMER("RENDERSYSTEM", "CreateSwapChain");
    LOG_INFO("RENDERSYSTEM", "Creating swap chain with dimensions: " + std::to_string(width) + "x" + std::to_string(height));
    
    try {
        MySwapChainPtr swapChain = std::make_shared<MySwapChain>(windowHandle, width, height, this);
        if (!swapChain) {
            LOG_ERROR("RENDERSYSTEM", "Failed to allocate MySwapChain");
            std::cerr << "[ERROR]: Failed to allocate MySwapChain in MyRenderSystem::CreateSwapChain" << std::endl;
            throw std::exception("Failed to allocate MySwapChain in MyRenderSystem::CreateSwapChain");
        }
        LOG_INFO("RENDERSYSTEM", "Swap chain created successfully");
        return swapChain;
    }
    catch (const std::exception& ex) {
        LOG_ERROR("RENDERSYSTEM", "Exception in CreateSwapChain: " + std::string(ex.what()));
        std::cerr << "[ERROR]: Exception in CreateSwapChain: " << ex.what() << std::endl;
        return nullptr;
    }
}

MyVertexBufferPtr MyRenderSystem::CreateVertexBuffer(void* vertexList, UINT vertexSize, UINT vertexCount, void* shaderByteCode, size_t shaderByteCodeSize) {
    try {
        MyVertexBufferPtr vertexBuffer = std::make_shared<MyVertexBuffer>(vertexList, vertexSize, vertexCount, shaderByteCode, shaderByteCodeSize, this);
        if (!vertexBuffer) {
            std::cerr << "[ERROR]: Failed to allocate MyVertexBuffer in MyRenderSystem::CreateVertexBuffer" << std::endl;
            throw std::exception("Failed to allocate MyVertexBuffer in MyRenderSystem::CreateVertexBuffer");
        }
        return vertexBuffer;
    }
    catch (const std::exception& ex) {
        std::cerr << "[ERROR]: Exception in CreateVertexBuffer: " << ex.what() << std::endl;
        return nullptr;
    }
}

MyConstantBufferPtr MyRenderSystem::CreateConstantBuffer(void* buffer, UINT bufferSize) {
    try {
        MyConstantBufferPtr constantBuffer = std::make_shared<MyConstantBuffer>(buffer, bufferSize, this);
        if (!constantBuffer) {
            std::cerr << "[ERROR]: Failed to allocate MyConstantBuffer in MyRenderSystem::CreateConstantBuffer" << std::endl;
            throw std::exception("Failed to allocate MyConstantBuffer in MyRenderSystem::CreateConstantBuffer");
        }
        return constantBuffer;
    }
    catch (const std::exception& ex) {
        std::cerr << "[ERROR]: Exception in CreateConstantBuffer: " << ex.what() << std::endl;
        return nullptr;
    }
}

MyIndexBufferPtr MyRenderSystem::CreateIndexBuffer(void* indices, UINT indexCount) {
    try {
        MyIndexBufferPtr indexBuffer = std::make_shared<MyIndexBuffer>(indices, indexCount, this);
        if (!indexBuffer) {
            std::cerr << "[ERROR]: Failed to allocate MyIndexBuffer in MyRenderSystem::CreateIndexBuffer" << std::endl;
            throw std::exception("Failed to allocate MyIndexBuffer in MyRenderSystem::CreateIndexBuffer");
        }
        return indexBuffer;
    }
    catch (const std::exception& ex) {
        std::cerr << "[ERROR]: Exception in CreateIndexBuffer: " << ex.what() << std::endl;
        return nullptr;
    }
}

MyHullShaderPtr MyRenderSystem::CreateHullShader(const void* shaderByteCode, size_t shaderSize) {
    try {
        MyHullShaderPtr hullShader = std::make_shared<MyHullShader>(shaderByteCode, shaderSize, this);
        if (!hullShader) {
            std::cerr << "[ERROR]: Failed to allocate MyHullShader in MyRenderSystem::CreateHullShader" << std::endl;
            throw std::exception("Failed to allocate MyHullShader in MyRenderSystem::CreateHullShader");
        }
        return hullShader;
    }
    catch (const std::exception& ex) {
        std::cerr << "[ERROR]: Exception in CreateHullShader: " << ex.what() << std::endl;
        return nullptr;
    }
}

MyDomainShaderPtr MyRenderSystem::CreateDomainShader(const void* shaderByteCode, size_t shaderSize) {
    try {
        MyDomainShaderPtr domainShader = std::make_shared<MyDomainShader>(shaderByteCode, shaderSize, this);
        if (!domainShader) {
            std::cerr << "[ERROR]: Failed to allocate MyDomainShader in MyRenderSystem::CreateDomainShader" << std::endl;
            throw std::exception("Failed to allocate MyDomainShader in MyRenderSystem::CreateDomainShader");
        }
        return domainShader;
    }
    catch (const std::exception& ex) {
        std::cerr << "[ERROR]: Exception in CreateDomainShader: " << ex.what() << std::endl;
        return nullptr;
    }
}

MyVertexShaderPtr MyRenderSystem::CreateVertexShader(const void* shaderByteCode, size_t shaderSize) {
    try {
        MyVertexShaderPtr vertexShader = std::make_shared<MyVertexShader>(shaderByteCode, shaderSize, this);
        if (!vertexShader) {
            std::cerr << "[ERROR]: Failed to allocate MyVertexShader in MyRenderSystem::CreateVertexShader" << std::endl;
            throw std::exception("Failed to allocate MyVertexShader in MyRenderSystem::CreateVertexShader");
        }
        return vertexShader;
    }
    catch (const std::exception& ex) {
        std::cerr << "[ERROR]: Exception in CreateVertexShader: " << ex.what() << std::endl;
        return nullptr;
    }
}

MyPixelShaderPtr MyRenderSystem::CreatePixelShader(const void* shaderByteCode, size_t shaderSize) {
    try {
        MyPixelShaderPtr pixelShader = std::make_shared<MyPixelShader>(shaderByteCode, shaderSize, this);
        if (!pixelShader) {
            std::cerr << "[ERROR]: Failed to allocate MyPixelShader in MyRenderSystem::CreatePixelShader" << std::endl;
            throw std::exception("Failed to allocate MyPixelShader in MyRenderSystem::CreatePixelShader");
        }
        return pixelShader;
    }
    catch (const std::exception& ex) {
        std::cerr << "[ERROR]: Exception in CreatePixelShader: " << ex.what() << std::endl;
        return nullptr;
    }
}

bool MyRenderSystem::CompileHullShader(const wchar_t* fileName, const char* entryPoint, void** shaderByteCode, size_t* shaderSize) {
    ID3DBlob* errorBlob = nullptr;

    HRESULT result = D3DCompileFromFile(
        fileName,
        nullptr,
        nullptr,
        entryPoint,
        "hs_5_0",
        0,
        0,
        &this->temporaryBlob,
        &errorBlob
    );

    if (FAILED(result)) {
        std::wcout << L"[ERROR]: D3DCompileFromFile failed for Hull Shader: " << fileName << L". HRESULT: 0x" << std::hex << result << std::endl;
        if (errorBlob) {
            std::cout << "[SHADER ERROR]: " << (char*)errorBlob->GetBufferPointer() << std::endl;
            errorBlob->Release();
        }
        return false;
    }

    if (LOG_INFO_VERTEX_SHADER)
        std::wcout << L"[INFO]: Hull shader compiled successfully: " << fileName << std::endl;

    *shaderByteCode = this->temporaryBlob->GetBufferPointer();
    *shaderSize = this->temporaryBlob->GetBufferSize();

    return SUCCEEDED(result);
}

bool MyRenderSystem::CompileDomainShader(const wchar_t* fileName, const char* entryPoint, void** shaderByteCode, size_t* shaderSize) {
    ID3DBlob* errorBlob = nullptr;

    HRESULT result = D3DCompileFromFile(
        fileName,
        nullptr,
        nullptr,
        entryPoint,
        "ds_5_0",
        0,
        0,
        &this->temporaryBlob,
        &errorBlob
    );

    if (FAILED(result)) {
        std::wcout << L"[ERROR]: D3DCompileFromFile failed for Domain Shader: " << fileName << L". HRESULT: 0x" << std::hex << result << std::endl;
        if (errorBlob) {
            std::cout << "[SHADER ERROR]: " << (char*)errorBlob->GetBufferPointer() << std::endl;
            errorBlob->Release();
        }
        return false;
    }

    if (LOG_INFO_VERTEX_SHADER)
        std::wcout << L"[INFO]: Domain shader compiled successfully: " << fileName << std::endl;

    *shaderByteCode = this->temporaryBlob->GetBufferPointer();
    *shaderSize = this->temporaryBlob->GetBufferSize();

    return SUCCEEDED(result);
}

bool MyRenderSystem::CompileVertexShader(const wchar_t* fileName, const char* entryPoint, void** shaderByteCode, size_t* shaderSize) {
    ID3DBlob* errorBlob = nullptr;

    HRESULT result = D3DCompileFromFile(
        fileName,
        nullptr,
        nullptr,
        entryPoint,
        "vs_5_0",
        0,
        0,
        &this->temporaryBlob,
        &errorBlob
    );

    if (FAILED(result)) {
        std::wcout << L"[ERROR]: D3DCompileFromFile failed for Vertex Shader: " << fileName << L". HRESULT: 0x" << std::hex << result << std::endl;
        if (errorBlob) {
            std::cout << "[SHADER ERROR]: " << (char*)errorBlob->GetBufferPointer() << std::endl;
            errorBlob->Release();
        }
        return false;
    }

    if (LOG_INFO_VERTEX_SHADER)
        std::wcout << L"[INFO]: Vertex shader compiled successfully: " << fileName << std::endl;

    *shaderByteCode = this->temporaryBlob->GetBufferPointer();
    *shaderSize = this->temporaryBlob->GetBufferSize();

    return SUCCEEDED(result);
}

bool MyRenderSystem::CompilePixelShader(const wchar_t* fileName, const char* entryPoint, void** shaderByteCode, size_t* shaderSize) {
    ID3DBlob* errorBlob = nullptr;

    HRESULT result = D3DCompileFromFile(
        fileName,
        nullptr,
        nullptr,
        entryPoint,
        "ps_5_0",
        0,
        0,
        &this->temporaryBlob,
        &errorBlob
    );

    if (FAILED(result)) {
        std::wcout << L"[ERROR]: D3DCompileFromFile failed for Pixel Shader: " << fileName << L". HRESULT: 0x" << std::hex << result << std::endl;
        if (errorBlob) {
            std::cout << "[SHADER ERROR]: " << (char*)errorBlob->GetBufferPointer() << std::endl;
            errorBlob->Release();
        }
        return false;
    }

    if (LOG_INFO_PIXEL_SHADER)
        std::wcout << L"[INFO]: Pixel shader compiled successfully: " << fileName << std::endl;

    *shaderByteCode = this->temporaryBlob->GetBufferPointer();
    *shaderSize = this->temporaryBlob->GetBufferSize();

    return SUCCEEDED(result);
}

bool MyRenderSystem::ReleaseCompiledShader() {
    if (this->temporaryBlob) {
        this->temporaryBlob->Release();
        this->temporaryBlob = nullptr;
    }
    return true;
}


void MyRenderSystem::ToggleWireframeMode(bool enable) {
    // Clean up existing rasterizer state
    if (this->immediateDeviceContext->D3DRasterizerState) {
        this->immediateDeviceContext->D3DRasterizerState->Release();
        this->immediateDeviceContext->D3DRasterizerState = nullptr;
    }

    D3D11_RASTERIZER_DESC rasterizerDescription = {};
    rasterizerDescription.FrontCounterClockwise = FALSE;
    rasterizerDescription.DepthBias = 0;
    rasterizerDescription.DepthBiasClamp = 0.0f;
    rasterizerDescription.SlopeScaledDepthBias = 0.0f;
    rasterizerDescription.DepthClipEnable = TRUE;
    rasterizerDescription.ScissorEnable = FALSE;
    rasterizerDescription.MultisampleEnable = FALSE;
    rasterizerDescription.AntialiasedLineEnable = FALSE;
    
    if (enable) {
        rasterizerDescription.FillMode = D3D11_FILL_WIREFRAME;
        rasterizerDescription.CullMode = D3D11_CULL_NONE;
    }
    else {
        rasterizerDescription.FillMode = D3D11_FILL_SOLID;
        rasterizerDescription.CullMode = D3D11_CULL_BACK;
    }
    
    HRESULT hr = this->D3DDevice->CreateRasterizerState(&rasterizerDescription, &this->immediateDeviceContext->D3DRasterizerState);
    if (FAILED(hr)) {
        std::cout << "CreateRasterizerState failed in MyRenderSystem::ToggleWireframeMode. HRESULT: 0x" << std::hex << hr << std::endl;
        _com_error err(hr);
        std::wcout << L"[ERROR]: " << err.ErrorMessage() << std::endl;
        return;
    }
    
    this->immediateDeviceContext->D3DDeviceContext->RSSetState(this->immediateDeviceContext->D3DRasterizerState);
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝