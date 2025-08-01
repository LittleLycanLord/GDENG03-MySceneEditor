#pragma once
#include "Core/Entity Component System/Components/MyComponent.hpp"
#include "Core/Entity Component System/Entities/MyEntity.hpp"
#include "Core/Resource System/Managers/MyMesh.hpp"
#include "Core/Prerequisites.hpp"

using namespace DX3D;

namespace DX3D {
    class MyMeshComponent : public MyComponent {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        MyMeshPtr mesh;
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyMeshComponent(const MyMeshPtr& mesh);
        virtual ~MyMeshComponent();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    public:

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    public:
        void OnAdd() override;
        void OnRemove() override;

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
        MyMeshPtr GetMesh() const { return mesh; }
        void SetMesh(const MyMeshPtr& newMesh) { mesh = newMesh; }
    };
} // namespace DX3D
