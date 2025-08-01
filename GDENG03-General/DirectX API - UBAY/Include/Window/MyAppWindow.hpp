#pragma once
#include <Windows.h>
#include <vector>
#include <exception>
#include <iostream>
#include "imgui.h"
#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"
#include "Window/MyWindow.hpp"
#include "Math/MyMatrix4x4.hpp"
#include "Math/MyVector3.hpp"
#include "Math/MyVector2.hpp"
#include "Math/MyConstant.hpp"
#include "Math/MyVertex.hpp"
#include "Game/MyCamera.hpp"
#include "Core/Primitives/MyTriangle.hpp"
#include "Core/Primitives/MyQuad.hpp"
#include "Core/Input System/MyInputSystem.hpp"
#include "Core/Input System/MyInputListener.hpp"
#include "Core/MyLogger.hpp"
#include "Core/Resource System/Managers/MyTextureManager.hpp"
#include "Core/Resource System/Managers/MyMeshManager.hpp"
#include "Core/Resource System/Managers/MyTexture.hpp"
#include "Core/Resource System/Managers/MyMesh.hpp"
#include "Game/Lighting/MyLightManager.hpp"
#include "Graphics/MyGraphicsEngine.hpp"
#include "Graphics/MyDeviceContext.hpp"
#include "Graphics/MySwapChain.hpp"
#include "Graphics/Buffers/MyVertexBuffer.hpp"
#include "Graphics/Buffers/MyConstantBuffer.hpp"
#include "Graphics/Buffers/MyIndexBuffer.hpp"
#include "Graphics/Shaders/MyVertexShader.hpp"
#include "Graphics/Shaders/MyPixelShader.hpp"
#include "Core/ImGui/ImGuiPanels/MyInspectorPanel.hpp"
#include "Core/Entity Component System/Entities/MyEntity.hpp"
#include "Core/Entity Component System/Components/MyComponent.hpp"
#include "Core/Entity Component System/Components/MyMeshComponent.hpp"
#include "Core/Entity Component System/Components/MyDirectionalLightComponent.hpp"
#include "Core/Entity Component System/Components/MyPointLightComponent.hpp"
#include "Core/Entity Component System/Components/MySpotLightComponent.hpp"
#include "Core/Entity Component System/Components/MyTransformComponent.hpp"
#include "Core/Entity Component System/Systems/MySystem.hpp"
#include "Core/Entity Component System/Systems/MyMeshRenderingSystem.hpp"
#include "Core/Entity Component System/Systems/MyLightingSystem.hpp"

namespace DX3D {
    class MyAppWindow : public MyWindow, public MyInputListener {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        //* ╔═════════════════════╗
        //* ║ Rendering Resources ║
        //* ╚═════════════════════╝
        MySwapChainPtr swapChain{ nullptr };
        MyVertexBufferPtr vertexBuffer{ nullptr };
        MyConstant globalConstantData;
        MyConstantBufferPtr globalConstantBuffer{ nullptr };
        MyIndexBufferPtr indexBuffer{ nullptr };
        MyHullShaderPtr hullShader{ nullptr };
        MyDomainShaderPtr domainShader{ nullptr };
        MyVertexShaderPtr vertexShader{ nullptr };
        MyPixelShaderPtr pixelShader{ nullptr };

        //* ╔═════════════════╗
        //* ║ Lighting System ║
        //* ╚═════════════════╝
        enum class LightingMode {
            STANDARD = 0,
            BASIC_LIGHTING = 1,
            HIGH_CONTRAST = 2,
            DEBUG_NORMALS = 3
        };

        MyVertexShaderPtr lightingVertexShader{ nullptr };
        MyPixelShaderPtr lightingPixelShader{ nullptr };
        MyPixelShaderPtr highContrastPixelShader{ nullptr };
        MyPixelShaderPtr debugNormalsPixelShader{ nullptr };
        MyHullShaderPtr lightingHullShader{ nullptr };
        MyDomainShaderPtr lightingDomainShader{ nullptr };
        LightingMode currentLightingMode{ LightingMode::STANDARD };
        bool useLightingShaders{ true };
        bool useTessellation{ false }; // Default to off for lighting compatibility

        //* ╔═══════════════════════╗
        //* ║ Game Objects & Camera ║
        //* ╚═══════════════════════╝
        bool freeMouse{ false };
        bool shouldCloseWindow{ false }; // Flag to defer window closing until end of frame
        MyCameraPtr activeCamera{ nullptr };
        std::vector<MyCameraPtr> cameras;
        std::vector<MyMeshPtr> meshes;
        // ECS mesh entities (for ECS migration)
        std::vector<MyEntityPtr> entities;
        std::vector<MySystemPtr> systems;
        // ECS mesh system instance
        MyMeshRenderingSystemPtr meshRenderingSystem{ nullptr };
        MyLightingSystemPtr lightingSystem{ nullptr };

        //* ╔══════════════════════╗
        //* ║ Timing & Performance ║
        //* ╚══════════════════════╝
        ULONGLONG oldTime = 0;
        ULONGLONG newTime = 0;
        float deltaTime = 0;
        float experimentalDelta = 0;

        //* ╔═══════════════╗
        //* ║ Sample Assets ║
        //* ╚═══════════════╝
        MyTexturePtr sampleTexture{ nullptr };
        MyMeshPtr sampleMesh{ nullptr };

        //* ╔════════════════════════╗
        //* ║ Graphic User Interface ║
        //* ╚════════════════════════╝
        std::vector<MyImGuiPanelPtr> panels;

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyAppWindow();
        ~MyAppWindow();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
        //* Initialization
        void InitializeShaders();
        void InitializeLightingShaders();
        void InitializeLightingSystem();
        void InitializeConstantData();
        void DebugLaunchFunction();

        //* Runtime
        void ImGuiUpdate();
        void InitializeImGuiPanels();

        void UpdateDeltaTime();
        void UpdateObjects();
        void UpdateConstantBuffer();
        void UpdateShaders();
        void DrawLoop();
    public:

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
    public:
        //* MyWindow
        virtual void OnCreate() override;
        virtual void OnUpdate() override;
        virtual void OnDestroy() override;
        virtual void OnSetFocus() override;
        virtual void OnKillFocus() override;

        //* MyInputListener
        virtual void OnKeyDown(int keyCode) override;
        virtual void OnKeyHold(int keyCode) override;
        virtual void OnKeyUp(int keyCode) override;
        virtual void OnMouseMove(const MyVector2& deltaMousePosition) override;
        virtual void OnLMBDown(const MyScreenPoint& mousePosition) override;
        virtual void OnLMBHold(const MyVector2& deltaMousePosition) override;
        virtual void OnLMBUp(const MyScreenPoint& mousePosition) override;
        virtual void OnRMBDown(const MyScreenPoint& mousePosition) override;
        virtual void OnRMBHold(const MyVector2& deltaMousePosition) override;
        virtual void OnRMBUp(const MyScreenPoint& mousePosition) override;

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
        // Request window closure at the end of the current frame
        void RequestWindowClose() { shouldCloseWindow = true; }

        // Check if window is marked for closing
        bool IsWindowClosing() const { return shouldCloseWindow; }
    };
} // namespace DX3D

