#pragma once
#include <d3d11.h>
#include "Core/Prerequisites.hpp"
#include "Math/MyVector3.hpp"
#include "Math/MyVector2.hpp"

namespace DX3D {
    class MyMeshVertex {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    public:
        MyVector3 position;
        MyVector3 normal;
        MyVector2 textureCoordinates;

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyMeshVertex() : position(), normal(), textureCoordinates() {}

        MyMeshVertex(MyVector3 position, MyVector3 normal, MyVector2 textureCoordinates)
            : position(position), normal(normal), textureCoordinates(textureCoordinates) {
        }

        // Backward compatibility constructor (provides default normal)
        MyMeshVertex(MyVector3 position, MyVector2 textureCoordinates)
            : position(position), normal(MyVector3(0.0f, 1.0f, 0.0f)), textureCoordinates(textureCoordinates) {
        }

        MyMeshVertex(const MyMeshVertex& other)
            : position(other.position), normal(other.normal), textureCoordinates(other.textureCoordinates) {
        }

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    public:
        // Get the input layout description for this vertex format
        static D3D11_INPUT_ELEMENT_DESC* GetInputLayout() {
            static D3D11_INPUT_ELEMENT_DESC layout[] = {
                { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,                                         D3D11_INPUT_PER_VERTEX_DATA, 0 },
                { "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(MyMeshVertex, normal),           D3D11_INPUT_PER_VERTEX_DATA, 0 },
                { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, offsetof(MyMeshVertex, textureCoordinates), D3D11_INPUT_PER_VERTEX_DATA, 0 }
            };
            return layout;
        }

        static UINT GetInputLayoutCount() {
            return 3;
        }

        static UINT GetVertexSize() {
            return sizeof(MyMeshVertex);
        }

        // Validate vertex data
        bool IsValid() const {
            return position.IsValid() && normal.IsValid() && textureCoordinates.IsValid();
        }
    };
} // namespace DX3D


