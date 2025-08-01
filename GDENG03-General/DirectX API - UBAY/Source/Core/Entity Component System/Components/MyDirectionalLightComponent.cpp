#include "Core/Entity Component System/Components/MyDirectionalLightComponent.hpp"

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyDirectionalLightComponent::MyDirectionalLightComponent(const MyDirectionalLightPtr& directionalLight) : directionalLight(directionalLight) {}
MyDirectionalLightComponent::~MyDirectionalLightComponent() {}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
void MyDirectionalLightComponent::OnAdd() {
    this->directionalLight->transform = this->GetOwner()->GetComponent<MyTransformComponent>()->GetTransform();
}
void MyDirectionalLightComponent::OnRemove() {}
