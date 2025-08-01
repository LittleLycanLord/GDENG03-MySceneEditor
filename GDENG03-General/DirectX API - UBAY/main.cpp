#include "Core/Input System/MyInputSystem.hpp"
#include "Graphics/MyGraphicsEngine.hpp"
#include "Window/MyAppWindow.hpp"
#include "Core/MyLogger.hpp"
#include <string>
#include <iostream>

extern const std::wstring LAYOUT_SHADER_DIRECTORY = L"Shaders/Layout/MeshVertexLayoutShader.hlsl";
extern const std::wstring HULL_SHADER_DIRECTORY = L"Shaders/Hull/TexturedTeapotHullShader.hlsl";
extern const std::wstring DOMAIN_SHADER_DIRECTORY = L"Shaders/Domain/TexturedTeapotDomainShader.hlsl";
extern const std::wstring VERTEX_SHADER_DIRECTORY = L"Shaders/Vertex/TexturedTeapotVertexShader.hlsl";
extern const std::wstring PIXEL_SHADER_DIRECTORY = L"Shaders/Pixel/TexturedTeapotPixelShader.hlsl";

// Lighting Shader Paths - New dedicated lighting shaders
extern const std::wstring LIGHTING_VERTEX_SHADER_DIRECTORY = L"Shaders/Vertex/LightingVertexShader.hlsl";
extern const std::wstring LIGHTING_PIXEL_SHADER_DIRECTORY = L"Shaders/Pixel/LightingPixelShader.hlsl";
extern const std::wstring LIGHTING_HULL_SHADER_DIRECTORY = L"Shaders/Hull/LightingHullShader.hlsl";
extern const std::wstring LIGHTING_DOMAIN_SHADER_DIRECTORY = L"Shaders/Domain/LightingDomainShader.hlsl";

extern const std::wstring SAMPLE_TEXTURE_DIRECTORY = L"Assets/Textures/Brick.png";
extern const std::wstring SAMPLE_MESH_DIRECTORY = L"Assets/Meshes/Teapot.obj";
extern const std::wstring IMGUI_LOGO_DIRECTORY = L"Assets/Textures/dlsu_logo.png";
using namespace DX3D;

int main() {
    std::cout << "[INFO]: Application started" << std::endl;

    // Initialize Logger first
    try {
        MyLogger::Create();
        MyLogger::GetInstance()->Initialize("GDENG03-Engine.log", true, true);
        LOG_INFO("APPLICATION", "GDENG03 DirectX Engine starting up...");
    }
    catch (const std::exception& ex) {
        std::cerr << "[ERROR]: Failed to create MyLogger: " << ex.what() << std::endl;
        return -3;
    }

    try {
        MyGraphicsEngine::Create();
        LOG_INFO("APPLICATION", "Graphics Engine initialized successfully");
    }
    catch (const std::exception& ex) {
        LOG_ERROR("APPLICATION", "Failed to create MyGraphicsEngine: " + std::string(ex.what()));
        MyLogger::Release();
        return -1;
    }

    try {
        MyInputSystem::Create();
        LOG_INFO("APPLICATION", "Input System initialized successfully");
    }
    catch (const std::exception& ex) {
        LOG_ERROR("APPLICATION", "Failed to create MyInputSystem: " + std::string(ex.what()));
        MyGraphicsEngine::Release();
        MyLogger::Release();
        return -2;
    }

    try {
        MyAppWindow appWindow;
        MyInputSystem::GetInstance()->SetWindowHandle(appWindow.windowHandle);
        LOG_INFO("APPLICATION", "Entering main application loop");
        while (appWindow.IsRunning());
        LOG_INFO("APPLICATION", "Application loop ended");
    }
    catch (const std::exception& ex) {
        LOG_ERROR("APPLICATION", "Exception in main loop: " + std::string(ex.what()));
        MyGraphicsEngine::Release();
        MyInputSystem::Release();
        MyLogger::Release();
        return -1;
    }

    LOG_INFO("APPLICATION", "Application shutting down gracefully");
    std::cout << "[INFO]: Application exiting" << std::endl;

    MyGraphicsEngine::Release();
    MyInputSystem::Release();
    MyLogger::Release();

    return 0;
}

