#include "Core/Resource System/Managers/MyMeshManager.hpp"
#include "Core/MyLogger.hpp"

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyMeshManager::MyMeshManager() {
    if (LOG_INFO_MESH_SYSTEM) std::cout << "[INFO]: MyMeshManager constructed" << std::endl;
}
MyMeshManager::~MyMeshManager() {
    if (LOG_INFO_MESH_SYSTEM) std::cout << "[INFO]: MyMeshManager destructed" << std::endl;
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
MyMeshPtr MyMeshManager::CreateUniqueMeshFromFile(const wchar_t* resourcePath) {
    return std::make_shared<MyMesh>(resourcePath);
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
MyResource* MyMeshManager::CreateResourceFromFileConcrete(const wchar_t* resourcePath) {
    if (!resourcePath) {
        std::cerr << "[ERROR]: Resource path is empty in MyMeshManager::CreateResourceFromFileConcrete" << std::endl;
        throw std::invalid_argument("Resource path cannot be empty");
        return nullptr;
    }
    if (LOG_INFO_MESH_SYSTEM) std::wcout << L"[INFO]: Loading mesh from file: " << resourcePath << std::endl;
    MyMesh* newMesh = nullptr;
    try {
        newMesh = new MyMesh(resourcePath);
    }
    catch (const std::exception& ex) {
        std::cerr << "[ERROR]: Failed to create MyMesh from file: " << ex.what() << std::endl;
        throw std::runtime_error("Failed to create MyMesh from file");
        return nullptr;
    }
    if (LOG_INFO_MESH_SYSTEM) std::wcout << L"[INFO]: Mesh loaded successfully: " << resourcePath << std::endl;
    return newMesh;
}
