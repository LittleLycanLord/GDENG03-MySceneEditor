#pragma once

#include <tiny_obj_loader.h>
#include <iostream>
#include <comdef.h>
#include <filesystem>
#include <vector>
#include <exception>
#include <d3d11.h>
#include <DirectXTex.h>
#include <windows.h>
#include "Core/Prerequisites.hpp"
#include "Core/Resource System/MyResource.hpp"
#include "Graphics/MyGraphicsEngine.hpp"
#include "Graphics/Buffers/MyVertexBuffer.hpp"
#include "Graphics/Buffers/MyIndexBuffer.hpp"
#include "Math/MyConstant.hpp"
#include "Math/MyMeshVertex.hpp"
#include "Math/MyVector3.hpp"
#include "Math/MyVector2.hpp"
#include "Game/MyTransform.hpp"

namespace DX3D {
    class MyMesh : public MyResource {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        //* TinyObjLoader
        tinyobj::attrib_t attributes;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warning = "";
        std::string error = "";
        std::vector<MyMeshVertex> vertices;
        std::vector<unsigned int> indices;

        MyVertexBufferPtr vertexBuffer;
        MyIndexBufferPtr indexBuffer;
        MyConstant constantData;
        MyConstantBufferPtr constantBuffer;
        void* layoutShaderByteCode;
        size_t layoutShaderSize = 0;



        friend class MyDeviceContext;
    public:
        MyTransformPtr transform;
        float lifetime = 0;
        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyMesh(const wchar_t* resourcePath);
        ~MyMesh();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        void Update(float deltaTime);
        void Draw(MyVertexShaderPtr vertexShader, MyHullShaderPtr hullShader, MyDomainShaderPtr domainShader, MyPixelShaderPtr pixelShader,
            const MyMatrix4x4& view, const MyMatrix4x4& projection, float time);

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
    public:

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
        const MyVertexBufferPtr& GetVertexBuffer() { return this->vertexBuffer; }
        const MyIndexBufferPtr& GetIndexBuffer() { return this->indexBuffer; }
    };
} // namespace DX3D

