#pragma once
#include "Core/Entity Component System/Systems/MySystem.hpp"
#include "Core/Entity Component System/Components/MyMeshComponent.hpp"
#include "Core/Entity Component System/Components/MyTransformComponent.hpp"
#include "Core/MyLogger.hpp"
#include "Core/Prerequisites.hpp"

namespace DX3D {
    class MyMeshRenderingSystem : public MySystem {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        static MyMeshRenderingSystemPtr instance;
        // No extra attributes for now
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyMeshRenderingSystem();
        virtual ~MyMeshRenderingSystem();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    public:
        // Singleton management
        static void Create();
        static void Release();
        static MyMeshRenderingSystemPtr GetInstance();

        void RenderMeshes(
            MyVertexShaderPtr vertexShader,
            MyHullShaderPtr hullShader,
            MyDomainShaderPtr domainShader,
            MyPixelShaderPtr pixelShader,
            const MyMatrix4x4& cameraWorldMatrix,
            const MyMatrix4x4& cameraProjectionMatrix,
            float time
        );

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    public:
        virtual void Update(float deltaTime) override;
    };
} // namespace DX3D
