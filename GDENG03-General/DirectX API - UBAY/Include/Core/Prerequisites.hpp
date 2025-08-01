#pragma once
#include <memory>

namespace DX3D {
    //* ╔══════════════════════╗
    //* ║ Forward Declarations ║
    //* ╚══════════════════════╝

    //* Rendering Module
    class MySwapChain;
    class MyDeviceContext;
    class MyVertexBuffer;
    class MyConstantBuffer;
    class MyIndexBuffer;
    class MyHullShader;
    class MyDomainShader;
    class MyVertexShader;
    class MyPixelShader;
    class MyRenderSystem;
    class MyGraphicsEngine;

    //* Resources
    class MyResource;
    class MyResourceSystem;
    class MyTexture;
    class MyTextureManager;
    class MyMesh;
    class MyMeshManager;

    //* Core GameObjects
    class MyTransform;
    class MyCamera;

    //* Lighting System
    class MyLight;
    class MyDirectionalLight;
    class MyPointLight;
    class MySpotLight;
    class MyLightManager;

    //* Entity Component System
    class MyEntity;
    class MyComponent;
    class MyTransformComponent;
    class MyMeshComponent;
    class MyDirectionalLightComponent;
    class MyPointLightComponent;
    class MySpotLightComponent;
    class MySystem;
    class MyMeshRenderingSystem;
    class MyLightingSystem;

    //* Utilities
    class MyLogger;

    //* ImGui
    class MyImGuiPanel;
    class MyInspectorPanel;

    //* ╔════════════════╗
    //* ║ Smart Pointers ║
    //* ╚════════════════╝

    //* Rendering Module
    typedef std::shared_ptr<MySwapChain> MySwapChainPtr;
    typedef std::shared_ptr<MyDeviceContext> MyDeviceContextPtr;
    typedef std::shared_ptr<MyVertexBuffer> MyVertexBufferPtr;
    typedef std::shared_ptr<MyConstantBuffer> MyConstantBufferPtr;
    typedef std::shared_ptr<MyIndexBuffer> MyIndexBufferPtr;
    typedef std::shared_ptr<MyHullShader> MyHullShaderPtr;
    typedef std::shared_ptr<MyDomainShader> MyDomainShaderPtr;
    typedef std::shared_ptr<MyVertexShader> MyVertexShaderPtr;
    typedef std::shared_ptr<MyPixelShader> MyPixelShaderPtr;
    typedef std::shared_ptr<MyRenderSystem> MyRenderSystemPtr;
    typedef std::shared_ptr<MyGraphicsEngine> MyGraphicsEnginePtr;

    //* Resources
    typedef std::shared_ptr<MyResource> MyResourcePtr;
    typedef std::shared_ptr<MyResourceSystem> MyResourceSystemPtr;
    typedef std::shared_ptr<MyTexture> MyTexturePtr;
    typedef std::shared_ptr<MyTextureManager> MyTextureManagerPtr;
    typedef std::shared_ptr<MyMesh> MyMeshPtr;
    typedef std::shared_ptr<MyMeshManager> MyMeshManagerPtr;

    //* Core GameObjects
    typedef std::shared_ptr<MyTransform> MyTransformPtr;
    typedef std::shared_ptr<MyCamera> MyCameraPtr;

    //* Lighting System
    typedef std::shared_ptr<MyLight> MyLightPtr;
    typedef std::shared_ptr<MyDirectionalLight> MyDirectionalLightPtr;
    typedef std::shared_ptr<MyPointLight> MyPointLightPtr;
    typedef std::shared_ptr<MySpotLight> MySpotLightPtr;
    typedef std::shared_ptr<MyLightManager> MyLightManagerPtr;

    //* Entity Component System
    typedef std::shared_ptr<MyEntity> MyEntityPtr;
    typedef std::shared_ptr<MyComponent> MyComponentPtr;
    typedef std::shared_ptr<MyTransformComponent> MyTransformComponentPtr;
    typedef std::shared_ptr<MyMeshComponent> MyMeshComponentPtr;
    typedef std::shared_ptr<MyDirectionalLightComponent> MyDirectionalLightComponentPtr;
    typedef std::shared_ptr<MyPointLightComponent> MyPointLightComponentPtr;
    typedef std::shared_ptr<MySpotLightComponent> MySpotLightComponentPtr;
    typedef std::shared_ptr<MySystem> MySystemPtr;
    typedef std::shared_ptr<MyMeshRenderingSystem> MyMeshRenderingSystemPtr;
    typedef std::shared_ptr<MyLightingSystem> MyLightingSystemPtr;

    //* Utilities
    typedef std::shared_ptr<MyLogger> MyLoggerPtr;

    //* ImGui
    typedef std::shared_ptr<MyImGuiPanel> MyImGuiPanelPtr;
    typedef std::shared_ptr<MyInspectorPanel> MyInspectorPanelPtr;

} // namespace DX3D

