#include "Core/Entity Component System/Components/MyMeshComponent.hpp"

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyMeshComponent::MyMeshComponent(const MyMeshPtr& mesh) : mesh(mesh) {}
MyMeshComponent::~MyMeshComponent() {}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
void MyMeshComponent::OnAdd() {
    this->mesh->transform = this->GetOwner()->GetComponent<MyTransformComponent>()->GetTransform();
}

void MyMeshComponent::OnRemove() {}
