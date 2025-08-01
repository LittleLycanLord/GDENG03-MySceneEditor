#include "Core/Resource System/Managers/MyMesh.hpp"
#include "Core/MyLogger.hpp"

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyMesh::MyMesh(const wchar_t* resourcePath) : transform(std::make_shared<MyTransform>()), MyResource(resourcePath), attributes(),
shapes(),
materials(),
vertices(),
indices() {
    if (LOG_INFO_MESH) std::wcout << L"[INFO]: MyMesh constructed for " << resourcePath << std::endl;

    std::filesystem::path filePath = resourcePath;

    if (tinyobj::LoadObj(&this->attributes, &this->shapes, &this->materials, &this->warning, &this->error, filePath.string().c_str())) {
        {
            if (LOG_INFO_MESH) std::wcout << L"[INFO]: Loading MyMesh Vertices..." << std::endl;

            if (this->shapes.size() > 1) {
                std::cerr << "[ERROR]: Failed to load mesh from file" << std::endl;
                throw std::runtime_error("Failed to load mesh from file");
            }

            // Debug: Check if we have shapes and vertices
            if (LOG_INFO_MESH) std::cout << "[DEBUG]: Shapes count: " << this->shapes.size() << std::endl;
            if (LOG_INFO_MESH) std::cout << "[DEBUG]: Vertices count: " << this->attributes.vertices.size() / 3 << std::endl;
            if (LOG_INFO_MESH) std::cout << "[DEBUG]: Normals count: " << this->attributes.normals.size() / 3 << std::endl;
            if (LOG_INFO_MESH) std::cout << "[DEBUG]: Texcoords count: " << this->attributes.texcoords.size() / 2 << std::endl;

            if (this->shapes.empty()) {
                std::cerr << "[ERROR]: No shapes found in OBJ file" << std::endl;
                throw std::runtime_error("No shapes found in OBJ file");
            }

            // Warn about missing data but continue loading
            if (this->attributes.normals.empty()) {
                if (LOG_INFO_MESH) std::cout << "[WARNING]: OBJ file has no normals, using default values" << std::endl;
            }
            if (this->attributes.texcoords.empty()) {
                if (LOG_INFO_MESH) std::cout << "[WARNING]: OBJ file has no texture coordinates, using default values" << std::endl;
            }

            for (size_t shape = 0; shape < this->shapes.size(); shape++) {
                if (LOG_INFO_MESH) std::cout << "[DEBUG]: Processing shape " << shape << ", faces: " << this->shapes[shape].mesh.num_face_vertices.size() << std::endl;

                size_t indexOffset = 0;
                this->vertices.reserve(this->shapes[shape].mesh.indices.size());
                this->indices.reserve(this->shapes[shape].mesh.indices.size());

                for (size_t face = 0; face < this->shapes[shape].mesh.num_face_vertices.size(); face++) {
                    unsigned char vertexPerFace = this->shapes[shape].mesh.num_face_vertices[face];
                    for (unsigned char vertex = 0; vertex < vertexPerFace; vertex++) {
                        //* Vertex Reading
                        tinyobj::index_t index = (tinyobj::index_t)this->shapes[shape].mesh.indices[indexOffset + vertex];

                        //* POSITION - Check bounds for vertex data
                        if (index.vertex_index < 0 || index.vertex_index * 3 + 2 >= this->attributes.vertices.size()) {
                            std::cerr << "[ERROR]: Invalid vertex index: " << index.vertex_index << std::endl;
                            throw std::runtime_error("Invalid vertex index in OBJ file");
                        }

                        tinyobj::real_t x = (tinyobj::real_t)this->attributes.vertices[index.vertex_index * 3 + 0];
                        tinyobj::real_t y = (tinyobj::real_t)this->attributes.vertices[index.vertex_index * 3 + 1];
                        tinyobj::real_t z = (tinyobj::real_t)this->attributes.vertices[index.vertex_index * 3 + 2];

                        //* NORMAL
                        tinyobj::real_t nx = 0.0f;
                        tinyobj::real_t ny = 1.0f; // Default up vector
                        tinyobj::real_t nz = 0.0f;
                        if (index.normal_index >= 0 && !this->attributes.normals.empty()) {
                            // Check bounds for normal data
                            if (index.normal_index * 3 + 2 < this->attributes.normals.size()) {
                                nx = (tinyobj::real_t)this->attributes.normals[index.normal_index * 3 + 0];
                                ny = (tinyobj::real_t)this->attributes.normals[index.normal_index * 3 + 1];
                                nz = (tinyobj::real_t)this->attributes.normals[index.normal_index * 3 + 2];
                            }
                            else {
                                if (LOG_INFO_MESH) std::cout << "[WARNING]: Normal index out of bounds, using default normal" << std::endl;
                            }
                        }

                        //* TEXCOORD
                        tinyobj::real_t u = 0.0f; // Default UV coordinate
                        tinyobj::real_t v = 0.0f; // Default UV coordinate
                        if (index.texcoord_index >= 0 && !this->attributes.texcoords.empty()) {
                            // Check bounds for texture coordinate data
                            if (index.texcoord_index * 2 + 1 < this->attributes.texcoords.size()) {
                                u = (tinyobj::real_t)this->attributes.texcoords[index.texcoord_index * 2 + 0];
                                v = (tinyobj::real_t)this->attributes.texcoords[index.texcoord_index * 2 + 1];
                            }
                            else {
                                if (LOG_INFO_MESH) std::cout << "[WARNING]: Texture coordinate index out of bounds, using default UV" << std::endl;
                            }
                        }

                        this->vertices.push_back(MyMeshVertex(MyVector3(x, y, z), MyVector3(nx, ny, nz), MyVector2(u, v)));
                        this->indices.push_back((unsigned int)indexOffset + vertex);
                    }
                    indexOffset += vertexPerFace;
                }
            }
        }

        MyGraphicsEngine::GetInstance()->GetShaderByteCodeAndSize(&this->layoutShaderByteCode, &this->layoutShaderSize);
        this->vertexBuffer = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreateVertexBuffer(&this->vertices[0], sizeof(MyMeshVertex), (UINT)this->vertices.size(), this->layoutShaderByteCode, this->layoutShaderSize);
        this->indexBuffer = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreateIndexBuffer(&this->indices[0], (UINT)this->indices.size());

        this->constantData.world = this->transform->worldMatrix; // Initial world matrix
        this->constantData.view.SetIdentity();                   // Set to identity or camera view
        this->constantData.projection.SetIdentity();             // Set to identity or camera projection
        this->constantData.time = 0.0f;                          // Initial time
        this->constantBuffer = MyGraphicsEngine::GetInstance()->GetRenderSystem()->CreateConstantBuffer(&this->constantData, sizeof(MyConstant));
    }
    else {
        if (!this->error.empty())
            std::cerr << "[ERROR]: Failed to load mesh from file: " << this->error << std::endl;
        else
            std::cerr << "[ERROR]: Failed to load mesh from file" << std::endl;

        throw std::runtime_error("Failed to load mesh from file");
    }
}
MyMesh::~MyMesh() {
    if (LOG_INFO_MESH) std::cout << "[INFO]: MyMesh destructed" << std::endl;
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
void MyMesh::Update(float deltaTime) {
    this->lifetime += deltaTime;

    //* Transform Unit Test - DISABLED for lighting testing
    // float radius = 3.0f;
    // this->transform->position.x = radius * cosf(this->lifetime);
    // this->transform->position.z = radius * sinf(this->lifetime);
    // this->transform->rotation.y = this->lifetime;
    // this->transform->scale = MyVector3(1.0f + 0.5f * sinf(this->lifetime)) * 0.1f;

    this->transform->Update(deltaTime);
}
void MyMesh::Draw(MyVertexShaderPtr vertexShader, MyHullShaderPtr hullShader, MyDomainShaderPtr domainShader, MyPixelShaderPtr pixelShader,
    const MyMatrix4x4& view, const MyMatrix4x4& projection, float time) {
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

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
