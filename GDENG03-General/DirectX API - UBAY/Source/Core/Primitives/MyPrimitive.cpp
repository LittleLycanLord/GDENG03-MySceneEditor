#include "Core/Primitives/MyPrimitive.h""

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyPrimitive::MyPrimitive() {}

void MyPrimitive::Update(float deltaTime)
{
	this->transform->Update(deltaTime);
}

void MyPrimitive::Draw(MyVertexShaderPtr vertexShader, MyHullShaderPtr hullShader, MyDomainShaderPtr domainShader, MyPixelShaderPtr pixelShader, const MyMatrix4x4& view, const MyMatrix4x4& projection, float time)
{
    this->constantData.world = this->transform->worldMatrix;
    this->constantData.view = view;
    this->constantData.projection = projection;
    this->constantData.time = time;

    this->constantBuffer->Update(MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext(), &this->constantData);

    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(vertexShader, this->constantBuffer);
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(hullShader, this->constantBuffer);
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(domainShader, this->constantBuffer);
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(pixelShader, this->constantBuffer);

    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetVertexBuffer(this->vertexBuffer);
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->SetIndexBuffer(this->indexBuffer);
    MyGraphicsEngine::GetInstance()->GetRenderSystem()->GetImmediateDeviceContext()->DrawIndexedTriangles(this->indexBuffer->GetIndexCount(), 0, 0);
}
