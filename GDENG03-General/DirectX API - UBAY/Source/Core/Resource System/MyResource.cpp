#include "Core/Resource System/MyResource.hpp"
#include "Core/MyLogger.hpp"

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyResource::MyResource(const wchar_t* resourcePath) : resourcePath(resourcePath) {
    if (LOG_INFO_RESOURCE) std::wcout << L"[INFO]: MyResource constructed for " << resourcePath << std::endl;
}
MyResource::~MyResource() {
    if (LOG_INFO_RESOURCE) std::cout << "[INFO]: MyResource destructed" << std::endl;
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
