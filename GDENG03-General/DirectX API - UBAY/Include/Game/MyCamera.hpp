#pragma once

#include <iostream>
#include <comdef.h>
#include <exception>
#include "Core/Prerequisites.hpp"
#include "Math/MyMatrix4x4.hpp"
#include "Math/MyVector3.hpp"
#include "Core/Input System/MyInputSystem.hpp"
#include "Core/Input System/MyInputListener.hpp"
#include "Game/MyTransform.hpp"

namespace DX3D {
    class MyCamera : public MyInputListener {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        float moveSpeed = 1.0f;
        float sensitivity = 0.5f;
        float deltaTime = 0.0f;
        float maxPitch = 45; //* degrees; +-
        MyVector3 movementInput;
        MyVector3 rotationInput;
        MyMatrix4x4 projectionMatrix;
        MyMatrix4x4 viewMatrix;

        friend class MyAppWindow;
    public:
        MyTransformPtr transform;

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyCamera();
        ~MyCamera();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
        void ClampPitch();
    public:
        void Update(float deltaTime);
        void UpdateTransformation();
        void SetOrthographicLeftHand(float width, float height, float nearPlane, float farPlane);
        void SetPerspectiveLeftHand(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
        //* MyInputListener
        virtual void OnKeyDown(int keyCode) override;
        virtual void OnKeyHold(int keyCode) override;
        virtual void OnKeyUp(int keyCode) override;
        virtual void OnMouseMove(const MyVector2& deltaMousePosition) override;
        virtual void OnLMBDown(const MyScreenPoint& mousePosition) override;
        virtual void OnLMBHold(const MyVector2& deltaMousePosition) override;
        virtual void OnLMBUp(const MyScreenPoint& mousePosition) override;
        virtual void OnRMBDown(const MyScreenPoint& mousePosition) override;
        virtual void OnRMBHold(const MyVector2& deltaMousePosition) override;
        virtual void OnRMBUp(const MyScreenPoint& mousePosition) override;
    public:

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
    };
} // namespace DX3D

