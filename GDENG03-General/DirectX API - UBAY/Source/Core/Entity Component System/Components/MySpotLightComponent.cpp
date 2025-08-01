#include "Core/Entity Component System/Components/MySpotLightComponent.hpp"

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MySpotLightComponent::MySpotLightComponent(const MySpotLightPtr& spotLight) : spotLight(spotLight) {}
MySpotLightComponent::~MySpotLightComponent() {}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
void MySpotLightComponent::OnAdd() {
    this->spotLight->transform = this->GetOwner()->GetComponent<MyTransformComponent>()->GetTransform();
}
void MySpotLightComponent::OnRemove() {}
