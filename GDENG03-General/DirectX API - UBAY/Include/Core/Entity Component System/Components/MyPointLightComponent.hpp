#pragma once
#include "Core/Entity Component System/Components/MyComponent.hpp"
#include "Game/Lighting/MyPointLight.hpp"
#include "Core/Entity Component System/Entities/MyEntity.hpp"
#include "Core/Prerequisites.hpp"

using namespace DX3D;

namespace DX3D {
    class MyPointLightComponent : public MyComponent {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        MyPointLightPtr pointLight;
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyPointLightComponent(const MyPointLightPtr& pointLight);
        virtual ~MyPointLightComponent();

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
        MyPointLightPtr GetPointLight() const { return pointLight; }
        void SetPointLight(const MyPointLightPtr& newPointLight) { pointLight = newPointLight; }
    };
} // namespace DX3D
