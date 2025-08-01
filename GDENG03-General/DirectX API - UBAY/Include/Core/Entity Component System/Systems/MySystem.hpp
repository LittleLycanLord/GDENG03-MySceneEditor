#pragma once

#include <vector>
#include "Core/Entity Component System/Entities/MyEntity.hpp"
#include "Core/Prerequisites.hpp"

namespace DX3D {
    class MySystem {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        std::vector<MyEntityPtr> entities;
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MySystem();
        virtual ~MySystem();
        void AddEntity(MyEntityPtr entity) {
            entities.push_back(entity);
        }

        void RemoveEntity(int id) {
            entities.erase(
                std::remove_if(entities.begin(), entities.end(),
                    [id](const MyEntityPtr& e) { return e->GetID() == id; }),
                entities.end()
            );
        }

        // Override this in derived systems
        virtual void Update(float deltaTime) {}

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
    public:

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
        const std::vector<MyEntityPtr>& GetEntities() const { return entities; }
    };
} // namespace DX3D

