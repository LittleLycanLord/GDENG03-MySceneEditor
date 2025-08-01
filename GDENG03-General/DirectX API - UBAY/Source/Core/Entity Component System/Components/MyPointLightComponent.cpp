#include "Core/Entity Component System/Components/MyPointLightComponent.hpp"

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyPointLightComponent::MyPointLightComponent(const MyPointLightPtr& pointLight) : pointLight(pointLight) {}
MyPointLightComponent::~MyPointLightComponent() {}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
void MyPointLightComponent::OnAdd() {
    this->pointLight->transform = this->GetOwner()->GetComponent<MyTransformComponent>()->GetTransform();
}
void MyPointLightComponent::OnRemove() {}

