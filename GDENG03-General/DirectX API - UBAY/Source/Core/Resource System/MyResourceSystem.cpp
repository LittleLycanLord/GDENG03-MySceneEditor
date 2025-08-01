#include "Core/Resource System/MyResourceSystem.hpp"
#include "Core/MyLogger.hpp"

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyResourceSystem::MyResourceSystem() {
    if (LOG_INFO_RESOURCE_SYSTEM) std::cout << "[INFO]: MyResourceSystem constructed" << std::endl;
}
MyResourceSystem::~MyResourceSystem() {
    if (LOG_INFO_RESOURCE_SYSTEM) std::cout << "[INFO]: MyResourceSystem destructed" << std::endl;
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
MyResourcePtr MyResourceSystem::CreateResourceFromFile(const wchar_t* resourcePath) {
    if (!resourcePath) {
        std::cerr << "[ERROR]: Resource path is empty in MyResourceSystem::CreateResourceFromFile" << std::endl;
        throw std::invalid_argument("Resource path cannot be empty");
    }

    std::wstring fullPath = std::filesystem::absolute(resourcePath);
    if (LOG_INFO_RESOURCE_SYSTEM) std::wcout << L"[INFO]: Attempting to create resource from file: " << fullPath << std::endl;
    std::map<std::wstring, MyResourcePtr>::iterator existingResource = this->resources.find(fullPath);
    if (existingResource != this->resources.end()) {
        if (LOG_INFO_RESOURCE_SYSTEM) std::wcout << L"[INFO]: Resource already loaded: " << fullPath << std::endl;
        return existingResource->second;
    }

    MyResource* rawResource = nullptr;
    try {
        rawResource = CreateResourceFromFileConcrete(fullPath.c_str());
    } catch (const std::exception& ex) {
        std::cerr << "[ERROR]: Exception in CreateResourceFromFileConcrete: " << ex.what() << std::endl;
        throw;
    }
    if (rawResource) {
        MyResourcePtr newResource(rawResource);
        this->resources[fullPath] = newResource;
        if (LOG_INFO_RESOURCE_SYSTEM) std::wcout << L"[INFO]: Resource created and cached: " << fullPath << std::endl;
        return newResource;
    }

    std::cerr << "[ERROR]: Failed to create resource from file" << std::endl;
    throw std::runtime_error("Failed to create resource from file");
    return nullptr;
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
