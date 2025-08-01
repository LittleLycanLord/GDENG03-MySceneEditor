#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include "Core/Entity Component System/Components/MyComponent.hpp"
#include "Core/Entity Component System/Components/MyTransformComponent.hpp"
#include "Core/Prerequisites.hpp"

namespace DX3D {
    class MyEntity {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        int id;
        std::unordered_map<std::type_index, MyComponentPtr> components;
    public:
        MyTransformComponentPtr transformComponent = nullptr;

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyEntity();
        MyEntity(int id);
        ~MyEntity();


        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
        void AddDefaultTransformComponent();
    public:
        template<typename T, typename... Args>
        std::shared_ptr<T> AddComponent(Args&&... args) {
            // Prevent adding MyTransformComponent via AddComponent (except from AddDefaultTransformComponent)
            if constexpr (std::is_same<T, MyTransformComponent>::value) {
                static_assert(!std::is_same<T, MyTransformComponent>::value, "Cannot add MyTransformComponent via AddComponent. Use AddDefaultTransformComponent instead.");
                return nullptr;
            }
            auto component = std::make_shared<T>(std::forward<Args>(args)...);
            component->SetOwner(this);
            this->components[typeid(T)] = component;
            component->OnAdd();
            return component;
        }
        template<typename T>
        std::shared_ptr<T> GetComponent() {
            auto it = this->components.find(typeid(T));
            if (it != this->components.end())
                return std::static_pointer_cast<T>(it->second);
            return nullptr;
        }

        template<typename T>
        void RemoveComponent() {
            this->components.erase(typeid(T));
        }

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
    public:

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
        int GetID() const { return id; }
        MyTransformPtr GetTransform() {
            if (!transformComponent)
                this->AddDefaultTransformComponent();
            return transformComponent->GetTransform();
        }
    };
} // namespace DX3D

