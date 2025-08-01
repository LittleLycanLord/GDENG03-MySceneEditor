#include "Core/ImGui/ImGuiPanels/MyInspectorPanel.hpp"

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyInspectorPanel::MyInspectorPanel(MyTransformPtr transform) : targetTransform(transform) {}
MyInspectorPanel::~MyInspectorPanel() {}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
void MyInspectorPanel::Render() {
    if (!targetTransform) return;
    ImGui::Begin("Inspector Panel");
    ImGui::Text("MyTransform Attributes");
    // Position
    float pos[3] = { targetTransform->position.x, targetTransform->position.y, targetTransform->position.z };
    if (ImGui::DragFloat3("Position", pos, 0.01f)) {
        targetTransform->position.x = pos[0];
        targetTransform->position.y = pos[1];
        targetTransform->position.z = pos[2];
    }
    // Rotation
    float rot[3] = { targetTransform->rotation.x, targetTransform->rotation.y, targetTransform->rotation.z };
    if (ImGui::DragFloat3("Rotation", rot, 0.01f)) {
        targetTransform->rotation.x = rot[0];
        targetTransform->rotation.y = rot[1];
        targetTransform->rotation.z = rot[2];
    }
    // Scale
    float scale[3] = { targetTransform->scale.x, targetTransform->scale.y, targetTransform->scale.z };
    if (ImGui::DragFloat3("Scale", scale, 0.01f)) {
        targetTransform->scale.x = scale[0];
        targetTransform->scale.y = scale[1];
        targetTransform->scale.z = scale[2];
    }
    ImGui::End();
}
