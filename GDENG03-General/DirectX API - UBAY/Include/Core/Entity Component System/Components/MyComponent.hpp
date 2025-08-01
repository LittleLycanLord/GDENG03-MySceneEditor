#pragma once
#include "Core/Prerequisites.hpp"

namespace DX3D {
    class MyEntity;
}

namespace DX3D {
    class MyComponent {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        MyEntity* owner = nullptr;
    public:


        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyComponent();
        virtual ~MyComponent();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        virtual void OnAdd() = 0;
        virtual void OnRemove() = 0;

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
    public:

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
        MyEntity* GetOwner() const { return owner; }
        void SetOwner(MyEntity* entity) { owner = entity; }
    };
} // namespace DX3D

