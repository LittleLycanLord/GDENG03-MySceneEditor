#pragma once
#include "Core/Entity Component System/Components/MyComponent.hpp"
#include "Game/Lighting/MySpotLight.hpp"
#include "Core/Entity Component System/Entities/MyEntity.hpp"
#include "Core/Prerequisites.hpp"

using namespace DX3D;

namespace DX3D {
    class MySpotLightComponent : public MyComponent {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        MySpotLightPtr spotLight;
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MySpotLightComponent(const MySpotLightPtr& spotLight);
        virtual ~MySpotLightComponent();

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
        MySpotLightPtr GetSpotLight() const { return spotLight; }
        void SetSpotLight(const MySpotLightPtr& newSpotLight) { spotLight = newSpotLight; }
    };
} // namespace DX3D
