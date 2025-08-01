#include "Core/Entity Component System/Systems/MyMeshRenderingSystem.hpp"

using namespace DX3D;

MyMeshRenderingSystemPtr MyMeshRenderingSystem::instance = nullptr;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyMeshRenderingSystem::MyMeshRenderingSystem() {}
MyMeshRenderingSystem::~MyMeshRenderingSystem() {}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
void MyMeshRenderingSystem::Create() {
    if (!instance) {
        instance = std::make_shared<MyMeshRenderingSystem>();
        if (LOG_INFO_MESH_SYSTEM) std::cout << "[INFO]: MyMeshRenderingSystem singleton created" << std::endl;
    }
}

void MyMeshRenderingSystem::Release() {
    if (instance) {
        instance.reset();
        if (LOG_INFO_MESH_SYSTEM) std::cout << "[INFO]: MyMeshRenderingSystem singleton released" << std::endl;
    }
}

MyMeshRenderingSystemPtr MyMeshRenderingSystem::GetInstance() {
    return instance;
}

void MyMeshRenderingSystem::RenderMeshes(
    MyVertexShaderPtr vertexShader,
    MyHullShaderPtr hullShader,
    MyDomainShaderPtr domainShader,
    MyPixelShaderPtr pixelShader,
    const MyMatrix4x4& cameraWorldMatrix,
    const MyMatrix4x4& cameraProjectionMatrix,
    float time
) {
    for (const auto& entity : GetEntities()) {
        auto meshComp = entity->GetComponent<MyMeshComponent>();
        auto transformComp = entity->GetComponent<MyTransformComponent>();
        if (meshComp && transformComp) {
            meshComp->GetMesh()->transform = transformComp->GetTransform();

            meshComp->GetMesh()->Draw(
                vertexShader,
                hullShader,
                domainShader,
                pixelShader,
                cameraWorldMatrix,
                cameraProjectionMatrix,
                time
            );
        }
    }
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
void MyMeshRenderingSystem::Update(float deltaTime) {}