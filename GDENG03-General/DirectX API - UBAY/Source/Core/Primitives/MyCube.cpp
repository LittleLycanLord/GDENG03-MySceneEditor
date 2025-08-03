#include "Core/Primitives/MyCube.h""

MyCube::MyCube() : MyPrimitive()
{
	MyPrimitiveVertex list[] =
	{
		//FRONT FACE
		{MyVector3(-0.5f, -0.5f, -0.5f),	MyVector3(1, 0, 0)},
		{MyVector3(-0.5f, 0.5f, -0.5f),		MyVector3(0, 1, 0)},
		{MyVector3(0.5f, 0.5f, -0.5f),		MyVector3(0, 0, 1)},
		{MyVector3(0.5f, -0.5f, -0.5f),		MyVector3(1, 0, 1)},

		//BACK FACE
		{MyVector3(0.5f, -0.5f, 0.5f),	MyVector3(1, 0, 0)},
		{MyVector3(0.5f, 0.5f, 0.5f),	MyVector3(1, 1, 0)},
		{MyVector3(-0.5f, 0.5f, 0.5f),	MyVector3(0, 0, 1)},
		{MyVector3(-0.5f, -0.5f, 0.5f),	MyVector3(1, 0, 1)},
	};

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,
		2,3,0,

		//BACK SIDE
		4,5,6,
		6,7,4,

		//TOP SIDE
		1,6,5,
		5,2,1,

		//BOTTOM SIDE
		7,0,3,
		3,4,7,

		//RIGHT SIDE
		3,2,5,
		5,4,3,

		//LEFT SIDE
		7,6,1,
		1,0,7

	};

	UINT size_list = ARRAYSIZE(list);
	UINT size_index_list = ARRAYSIZE(index_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	vertexBuffer = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreateVertexBuffer(list, sizeof(MyPrimitiveVertex), size_list, shader_byte_code, size_shader);
	indexBuffer = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreateIndexBuffer(index_list, size_index_list);

	//GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	//m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);
	//m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	//GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	//GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	//m_ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);

	//GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	constantBuffer = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreateConstantBuffer(&this->constantData, sizeof(MyConstant));
}
