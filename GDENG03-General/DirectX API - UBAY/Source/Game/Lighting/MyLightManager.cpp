#include "Game/Lighting/MyLightManager.hpp"
#include "Core/MyLogger.hpp"
#include "Graphics/Buffers/MyConstantBuffer.hpp"
#include "Graphics/MyGraphicsEngine.hpp"
#include "Core/MyRenderSystem.hpp"
#include "Math/MyLightData.hpp"
#include <algorithm>

namespace DX3D {

    MyLightManager* MyLightManager::instance = nullptr;

    MyLightManager::MyLightManager()
        : lightingConstantBuffer(nullptr)
        , ambientLight(MyVector3(0.2f, 0.2f, 0.2f))
        , ambientIntensity(0.1f)
        , needsUpdate(true) {
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLightManager initialized" << std::endl;

        // Initialize lighting data structure
        memset(&lightingData, 0, sizeof(MyLightingData));
        lightingData.ambientLight = ambientLight;
        lightingData.ambientIntensity = ambientIntensity;
    }

    MyLightManager::~MyLightManager() {
        RemoveAllLights();
        lightingConstantBuffer = nullptr; // Smart pointer will auto-cleanup
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLightManager destroyed" << std::endl;
    }

    void MyLightManager::Create() {
        if (!instance) {
            instance = new MyLightManager();
            if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLightManager singleton created" << std::endl;
        }
    }

    void MyLightManager::Release() {
        if (instance) {
            delete instance;
            instance = nullptr;
            if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLightManager singleton released" << std::endl;
        }
    }

    MyLightManager* MyLightManager::GetInstance() {
        return instance;
    }

    void MyLightManager::AddLight(std::shared_ptr<MyLight> light) {
        if (!light) {
            if (LOG_ERROR_GENERAL) std::cout << "[ERROR]: MyLightManager::AddLight - Cannot add null light" << std::endl;
            return;
        }

        if (lights.size() >= MAX_LIGHTS) {
            if (LOG_ERROR_GENERAL) std::cout << "[ERROR]: MyLightManager::AddLight - Maximum light count (" << MAX_LIGHTS << ") exceeded" << std::endl;
            return;
        }

        lights.push_back(light);
        needsUpdate = true;

        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLightManager::AddLight - Light added, total count: " << lights.size() << "/" << MAX_LIGHTS << std::endl;
    }

    void MyLightManager::RemoveLight(std::shared_ptr<MyLight> light) {
        auto it = std::find(lights.begin(), lights.end(), light);
        if (it != lights.end()) {
            lights.erase(it);
            needsUpdate = true;
            if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLightManager::RemoveLight - Light removed, total count: " << lights.size() << "/" << MAX_LIGHTS << std::endl;
        }
        else {
            if (LOG_WARNING_GENERAL) std::cout << "[WARNING]: MyLightManager::RemoveLight - Light not found in manager" << std::endl;
        }
    }

    void MyLightManager::RemoveAllLights() {
        lights.clear();
        needsUpdate = true;
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLightManager::RemoveAllLights - All lights removed" << std::endl;
    }

    std::shared_ptr<MyDirectionalLight> MyLightManager::AddDirectionalLight(const MyVector3& color, float intensity) {
        auto light = std::make_shared<MyDirectionalLight>(color, intensity);
        AddLight(light);
        return light;
    }

    std::shared_ptr<MyPointLight> MyLightManager::AddPointLight(const MyVector3& position, const MyVector3& color, float intensity, float range) {
        auto light = std::make_shared<MyPointLight>(color, intensity, range);
        light->transform->position = position;
        AddLight(light);
        return light;
    }

    std::shared_ptr<MySpotLight> MyLightManager::AddSpotLight(const MyVector3& position, const MyVector3& direction, const MyVector3& color, float intensity, float range) {
        auto light = std::make_shared<MySpotLight>(color, intensity, range);
        light->transform->position = position;
        light->SetDirection(direction);
        AddLight(light);
        return light;
    }

    std::shared_ptr<MyLight> MyLightManager::GetLight(size_t index) const {
        if (index < lights.size()) {
            return lights[index];
        }
        return nullptr;
    }

    int MyLightManager::GetDirectionalLightCount() const {
        return std::count_if(lights.begin(), lights.end(),
            [](const std::shared_ptr<MyLight>& light) {
                return light->GetType() == LightType::DIRECTIONAL;
            });
    }

    int MyLightManager::GetPointLightCount() const {
        return std::count_if(lights.begin(), lights.end(),
            [](const std::shared_ptr<MyLight>& light) {
                return light->GetType() == LightType::POINT;
            });
    }

    int MyLightManager::GetSpotLightCount() const {
        return std::count_if(lights.begin(), lights.end(),
            [](const std::shared_ptr<MyLight>& light) {
                return light->GetType() == LightType::SPOT;
            });
    }

    void MyLightManager::SetAmbientLight(const MyVector3& color, float intensity) {
        ambientLight = color;
        ambientIntensity = intensity;
        needsUpdate = true;

        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLightManager::SetAmbientLight - Color(" << color.x << ", " << color.y << ", " << color.z << "), Intensity(" << intensity << ")" << std::endl;
    }

    void MyLightManager::UpdateLightingData() {
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

        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLightManager::UpdateLightingData - Total: " << lightIndex << ", Dir: " << directionalCount << ", Point: " << pointCount << ", Spot: " << spotCount << std::endl;
    }

    void MyLightManager::CreateLightingConstantBuffer() {
        if (!lightingConstantBuffer) {
            auto renderSystem = MyGraphicsEngine::GetInstance()->GetRenderSystem();
            lightingConstantBuffer = renderSystem->CreateConstantBuffer(&lightingData, sizeof(MyLightingData));
            if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLightManager::CreateLightingConstantBuffer - Lighting constant buffer created" << std::endl;
        }
    }

    void MyLightManager::UpdateLightingConstantBuffer() {
        if (lightingConstantBuffer) {
            UpdateLightingData();
            auto renderSystem = MyGraphicsEngine::GetInstance()->GetRenderSystem();
            auto deviceContext = renderSystem->GetImmediateDeviceContext();
            lightingConstantBuffer->Update(deviceContext, &lightingData);
            if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLightManager::UpdateLightingConstantBuffer - Lighting constant buffer updated" << std::endl;
        }
    }

    void MyLightManager::LogLightingSummary() const {
        if (LOG_INFO_LIGHTING) {
            std::cout << "[INFO]: === MyLightManager Summary ===" << std::endl;
            std::cout << "[INFO]: Total Lights: " << lights.size() << "/" << MAX_LIGHTS << std::endl;
            std::cout << "[INFO]: Directional: " << GetDirectionalLightCount() << std::endl;
            std::cout << "[INFO]: Point: " << GetPointLightCount() << std::endl;
            std::cout << "[INFO]: Spot: " << GetSpotLightCount() << std::endl;
            std::cout << "[INFO]: Ambient: (" << ambientLight.x << ", " << ambientLight.y << ", " << ambientLight.z << ") * " << ambientIntensity << std::endl;
            std::cout << "[INFO]: ===============================" << std::endl;
        }
    }

    void MyLightManager::EnableAllLights() {
        for (auto& light : lights) {
            if (light) light->SetEnabled(true);
        }
        needsUpdate = true;
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLightManager::EnableAllLights - All lights enabled" << std::endl;
    }

    void MyLightManager::DisableAllLights() {
        for (auto& light : lights) {
            if (light) light->SetEnabled(false);
        }
        needsUpdate = true;
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLightManager::DisableAllLights - All lights disabled" << std::endl;
    }

} // namespace DX3D
