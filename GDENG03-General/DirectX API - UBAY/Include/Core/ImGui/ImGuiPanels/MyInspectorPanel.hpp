#pragma once
#include "Core/ImGui/MyImGuiPanel.hpp"
#include "Game/MyTransform.hpp"
#include "Core/Prerequisites.hpp"

namespace DX3D {
    class MyInspectorPanel : public MyImGuiPanel {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        MyTransformPtr targetTransform{ nullptr };
    public:

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyInspectorPanel(MyTransformPtr transform);
        virtual ~MyInspectorPanel();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        // Override Render to show MyTransform attributes
        virtual void Render() override;

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
    public:

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
        // Optionally, set a new target transform
        void SetTarget(MyTransformPtr transform) { targetTransform = transform; }
    };
} // namespace DX3D

