#include "Core/Entity Component System/Systems/MyLightingSystem.hpp"

using namespace DX3D;

MyLightingSystemPtr MyLightingSystem::instance = nullptr;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyLightingSystem::MyLightingSystem()
    : lightingConstantBuffer(nullptr)
    , ambientLight(MyVector3(0.2f, 0.2f, 0.2f))
    , ambientIntensity(0.1f)
    , needsUpdate(true) {
    if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLightingSystem initialized" << std::endl;

    // Initialize lighting data structure
    memset(&lightingData, 0, sizeof(MyLightingData));
    lightingData.ambientLight = ambientLight;
    lightingData.ambientIntensity = ambientIntensity;
}

MyLightingSystem::~MyLightingSystem() {
    RemoveAllLights();
    lightingConstantBuffer = nullptr; // Smart pointer will auto-cleanup
    if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLightingSystem destroyed" << std::endl;
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
void MyLightingSystem::Create() {
    if (!instance) {
        instance = std::make_shared<MyLightingSystem>();
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLightingSystem singleton created" << std::endl;
    }
}

void MyLightingSystem::Release() {
    if (instance) {
        instance.reset();
        instance = nullptr;
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLightingSystem singleton released" << std::endl;
    }
}

MyLightingSystemPtr MyLightingSystem::GetInstance() {
    return instance;
}

void MyLightingSystem::AddLight(std::shared_ptr<MyLight> light) {
    if (!light) {
        if (LOG_ERROR_GENERAL) std::cout << "[ERROR]: MyLightingSystem::AddLight - Cannot add null light" << std::endl;
        return;
    }

    if (lights.size() >= MAX_LIGHTS) {
        if (LOG_ERROR_GENERAL) std::cout << "[ERROR]: MyLightingSystem::AddLight - Maximum light count (" << MAX_LIGHTS << ") exceeded" << std::endl;
        return;
    }

    lights.push_back(light);
    needsUpdate = true;

    if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLightingSystem::AddLight - Light added, total count: " << lights.size() << "/" << MAX_LIGHTS << std::endl;
}

void MyLightingSystem::RemoveLight(std::shared_ptr<MyLight> light) {
    auto it = std::find(lights.begin(), lights.end(), light);
    if (it != lights.end()) {
        lights.erase(it);
        needsUpdate = true;
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLightingSystem::RemoveLight - Light removed, total count: " << lights.size() << "/" << MAX_LIGHTS << std::endl;
    }
    else {
        if (LOG_WARNING_GENERAL) std::cout << "[WARNING]: MyLightingSystem::RemoveLight - Light not found in manager" << std::endl;
    }
}

void MyLightingSystem::RemoveAllLights() {
    lights.clear();
    needsUpdate = true;
    if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLightingSystem::RemoveAllLights - All lights removed" << std::endl;
}

std::shared_ptr<MyDirectionalLight> MyLightingSystem::AddDirectionalLight(const MyVector3& color, float intensity) {
    auto light = std::make_shared<MyDirectionalLight>(color, intensity);
    AddLight(light);
    return light;
}

std::shared_ptr<MyPointLight> MyLightingSystem::AddPointLight(const MyVector3& color, float intensity, float range) {
    auto light = std::make_shared<MyPointLight>(color, intensity, range);
    AddLight(light);
    return light;
}

std::shared_ptr<MySpotLight> MyLightingSystem::AddSpotLight(const MyVector3& color, float intensity, float range) {
    auto light = std::make_shared<MySpotLight>(color, intensity, range);
    AddLight(light);
    return light;
}

std::shared_ptr<MyLight> MyLightingSystem::GetLight(size_t index) const {
    if (index < lights.size()) {
        return lights[index];
    }
    return nullptr;
}

int MyLightingSystem::GetDirectionalLightCount() const {
    return std::count_if(lights.begin(), lights.end(),
        [](const std::shared_ptr<MyLight>& light) {
            return light->GetType() == LightType::DIRECTIONAL;
        });
}

int MyLightingSystem::GetPointLightCount() const {
    return std::count_if(lights.begin(), lights.end(),
        [](const std::shared_ptr<MyLight>& light) {
            return light->GetType() == LightType::POINT;
        });
}

int MyLightingSystem::GetSpotLightCount() const {
    return std::count_if(lights.begin(), lights.end(),
        [](const std::shared_ptr<MyLight>& light) {
            return light->GetType() == LightType::SPOT;
        });
}

void MyLightingSystem::SetAmbientLight(const MyVector3& color, float intensity) {
    ambientLight = color;
    ambientIntensity = intensity;
    needsUpdate = true;

    if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLightingSystem::SetAmbientLight - Color(" << color.x << ", " << color.y << ", " << color.z << "), Intensity(" << intensity << ")" << std::endl;
}

void MyLightingSystem::UpdateLightingData() {
    if (!needsUpdate) return;

    // Clear data
    memset(&lightingData, 0, sizeof(MyLightingData));

    // Set ambient lighting
    lightingData.ambientLight = ambientLight;
    lightingData.ambientIntensity = ambientIntensity;

    // Count lights by type
    int directionalCount = 0, pointCount = 0, spotCount = 0;

    // Pack light data
    int lightIndex = 0;
    for (const auto& light : lights) {
        if (!light || !light->IsEnabled() || lightIndex >= MAX_LIGHTS) continue;

        lightingData.lights[lightIndex] = light->GetLightData();

        switch (light->GetType()) {
        case LightType::DIRECTIONAL: directionalCount++; break;
        case LightType::POINT: pointCount++; break;
        case LightType::SPOT: spotCount++; break;
        }

        lightIndex++;
    }

    // Update counts
    lightingData.numDirectionalLights = directionalCount;
    lightingData.numPointLights = pointCount;
    lightingData.numSpotLights = spotCount;
    lightingData.totalActiveLights = lightIndex;

    needsUpdate = false;

    if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLightingSystem::UpdateLightingData - Total: " << lightIndex << ", Dir: " << directionalCount << ", Point: " << pointCount << ", Spot: " << spotCount << std::endl;
}

void MyLightingSystem::CreateLightingConstantBuffer() {
    if (!lightingConstantBuffer) {
        auto renderSystem = MyGraphicsEngine::GetInstance()->GetRenderSystem();
        lightingConstantBuffer = renderSystem->CreateConstantBuffer(&lightingData, sizeof(MyLightingData));
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLightingSystem::CreateLightingConstantBuffer - Lighting constant buffer created" << std::endl;
    }
}

void MyLightingSystem::UpdateLightingConstantBuffer() {
    if (lightingConstantBuffer) {
        UpdateLightingData();
        auto renderSystem = MyGraphicsEngine::GetInstance()->GetRenderSystem();
        auto deviceContext = renderSystem->GetImmediateDeviceContext();
        lightingConstantBuffer->Update(deviceContext, &lightingData);
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLightingSystem::UpdateLightingConstantBuffer - Lighting constant buffer updated" << std::endl;
    }
}

void MyLightingSystem::LogLightingSummary() const {
    if (LOG_INFO_LIGHTING) {
        std::cout << "[INFO]: === MyLightingSystem Summary ===" << std::endl;
        std::cout << "[INFO]: Total Lights: " << lights.size() << "/" << MAX_LIGHTS << std::endl;
        std::cout << "[INFO]: Directional: " << GetDirectionalLightCount() << std::endl;
        std::cout << "[INFO]: Point: " << GetPointLightCount() << std::endl;
        std::cout << "[INFO]: Spot: " << GetSpotLightCount() << std::endl;
        std::cout << "[INFO]: Ambient: (" << ambientLight.x << ", " << ambientLight.y << ", " << ambientLight.z << ") * " << ambientIntensity << std::endl;
        std::cout << "[INFO]: ===============================" << std::endl;
    }
}

void MyLightingSystem::EnableAllLights() {
    for (auto& light : lights) {
        if (light) light->SetEnabled(true);
    }
    needsUpdate = true;
    if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLightingSystem::EnableAllLights - All lights enabled" << std::endl;
}

void MyLightingSystem::DisableAllLights() {
    for (auto& light : lights) {
        if (light) light->SetEnabled(false);
    }
    needsUpdate = true;
    if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLightingSystem::DisableAllLights - All lights disabled" << std::endl;
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
void MyLightingSystem::Update(float deltaTime) {
    if (this->needsUpdate) {
        this->UpdateLightingData();
        this->UpdateLightingConstantBuffer();
    }
}
