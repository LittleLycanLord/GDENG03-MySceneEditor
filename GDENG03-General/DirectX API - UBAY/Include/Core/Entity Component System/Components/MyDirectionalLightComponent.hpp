#pragma once
#include "Core/Entity Component System/Components/MyComponent.hpp"
#include "Core/Entity Component System/Entities/MyEntity.hpp"
#include "Game/Lighting/MyDirectionalLight.hpp"
#include "Core/Prerequisites.hpp"

using namespace DX3D;

namespace DX3D {
    class MyDirectionalLightComponent : public MyComponent {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        MyDirectionalLightPtr directionalLight;
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyDirectionalLightComponent(const MyDirectionalLightPtr& directionalLight);
        virtual ~MyDirectionalLightComponent();

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
        MyDirectionalLightPtr GetDirectionalLight() const { return directionalLight; }
        void SetDirectionalLight(const MyDirectionalLightPtr& newDirectionalLight) { directionalLight = newDirectionalLight; }

    };
} // namespace DX3D
