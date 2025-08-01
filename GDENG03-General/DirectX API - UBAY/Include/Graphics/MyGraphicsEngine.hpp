#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <iostream>
#include <comdef.h>
#include <exception>
#include "Core/Prerequisites.hpp"
#include "Core/MyRenderSystem.hpp"
#include "Core/Resource System/Managers/MyTextureManager.hpp"
#include "Core/Resource System/Managers/MyMeshManager.hpp"

namespace DX3D {
    class MyGraphicsEngine {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        static MyGraphicsEngine* instance;

        MyRenderSystem* renderSystem{ nullptr };
        MyTextureManager* textureManager{ nullptr };
        MyMeshManager* meshManager{ nullptr };

        unsigned char layoutShaderByteCode[1024];
        size_t layoutShaderSize = 0;

        //* ╔═════════════════════════════╗
        //* ║ Singleton Instance Accessor ║
        //* ╚═════════════════════════════╝
    public:
        static MyGraphicsEngine* GetInstance() {
            static MyGraphicsEngine graphicsEngine;
            return &graphicsEngine;
        }

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    private:
        MyGraphicsEngine();
        ~MyGraphicsEngine();
    public:

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        static void Create();
        static void Release();

        void GetShaderByteCodeAndSize(void** shaderByteCode, size_t* shaderSize);
        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
    public:

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
        MyRenderSystem* GetRenderSystem() const { return this->renderSystem; }
        MyTextureManager* GetTextureManager() const { return this->textureManager; }
        MyMeshManager* GetMeshManager() const { return this->meshManager; }
    };
} // namespace DX3D

