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

using namespace DX3D;

class MyPrimitive
{
	public:
		MyPrimitive();
		void Update(float deltaTime);
		void Draw(MyVertexShaderPtr vertexShader, MyHullShaderPtr hullShader, MyDomainShaderPtr domainShader, MyPixelShaderPtr pixelShader,
			const MyMatrix4x4& view, const MyMatrix4x4& projection, float time);
	public:
		MyTransformPtr transform;
		MyConstant constantData;
		MyConstantBufferPtr constantBuffer;
		MyVertexBufferPtr vertexBuffer;
		MyIndexBufferPtr indexBuffer;
};

