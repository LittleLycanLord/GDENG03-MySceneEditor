#include "Core/Entity Component System/Entities/MyEntity.hpp"

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyEntity::MyEntity() : id(0) {
    AddDefaultTransformComponent();
}
MyEntity::MyEntity(int id) : id(id) {
    AddDefaultTransformComponent();
}
MyEntity::~MyEntity() {}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
void MyEntity::AddDefaultTransformComponent() {
    auto newTransformComponent = std::make_shared<MyTransformComponent>();
    newTransformComponent->SetOwner(this);
    this->components[typeid(MyTransformComponent)] = newTransformComponent;
    newTransformComponent->OnAdd();
    this->transformComponent = newTransformComponent;
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
