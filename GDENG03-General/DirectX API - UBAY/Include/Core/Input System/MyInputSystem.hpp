#pragma once
#include <map>
#include <iostream>
#include <Windows.h>
#include <exception>
#include "Core/Input System/MyInputListener.hpp"
#include "Math/MyScreenPoint.hpp"
#include "Math/MyVector2.hpp"

namespace DX3D {
    class MyInputSystem {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        static MyInputSystem* instance;

        std::map<MyInputListener*, MyInputListener*> inputListeners;
        unsigned char newKeyStates[256] = { 0 };
        unsigned char oldKeyStates[256] = { 0 };

        bool firstFrame = true;
        MyVector2 rawMouseDelta = { 0.0f, 0.0f };

        MyScreenPoint newMousePosition = { 0, 0 };
        MyScreenPoint oldMousePosition = { 0, 0 };
        MyVector2 deltaMousePosition = { 0.0f, 0.0f };
        HWND windowHandle;
    public:
        bool lockMouse = true;
        unsigned int windowWidth;
        unsigned int windowHeight;

        //* ╔═════════════════════════════╗
        //* ║ Singleton Instance Accessor ║
        //* ╚═════════════════════════════╝
    public:
        static MyInputSystem* GetInstance() {
            static MyInputSystem instance;
            return &instance;
        }

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    private:
        MyInputSystem();
        ~MyInputSystem();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        static void Create();
        static void Release();
        void Update();
        void AddListener(MyInputListener* inputListener);
        void RemoveListener(MyInputListener* inputListener);

        void AddRawMouseDelta(float deltaX, float deltaY);
        void SetCursorPosition(const MyScreenPoint& position);
        void SetCursorVisibility(bool showCursor);

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
    public:

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
        void SetWindowHandle(HWND handle) {
            this->windowHandle = handle;
        }

        unsigned char GetNewKeyState(unsigned char key) const {
            return newKeyStates[key];
        }

        unsigned char GetOldKeyState(unsigned char key) const {
            return oldKeyStates[key];
        }

    };
} // namespace DX3D

