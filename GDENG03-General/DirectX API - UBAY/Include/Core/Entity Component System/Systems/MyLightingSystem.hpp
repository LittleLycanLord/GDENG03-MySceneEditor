#pragma once
#include "Core/Entity Component System/Systems/MySystem.hpp"
#include "Core/MyLogger.hpp"
#include "Graphics/Buffers/MyConstantBuffer.hpp"
#include "Graphics/MyGraphicsEngine.hpp"
#include "Core/Prerequisites.hpp"
#include "Core/MyRenderSystem.hpp"
#include "Math/MyLightData.hpp"
#include "Game/Lighting/MyLight.hpp"
#include "Game/Lighting/MyDirectionalLight.hpp"
#include "Game/Lighting/MyPointLight.hpp"
#include "Game/Lighting/MySpotLight.hpp"
#include "Math/MyLightData.hpp"
#include <algorithm>
#include <vector>
#include <memory>

namespace DX3D {
    // Forward declarations
    class MyConstantBuffer;

    class MyLightingSystem : public MySystem {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        static MyLightingSystemPtr instance;

        std::vector<std::shared_ptr<MyLight>> lights;
        MyLightingData lightingData;
        MyConstantBufferPtr lightingConstantBuffer;

        // Ambient lighting
        MyVector3 ambientLight;
        float ambientIntensity;

        // Internal management
        bool needsUpdate;

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyLightingSystem();
        ~MyLightingSystem();

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    public:
        // Singleton management
        static void Create();
        static void Release();
        static MyLightingSystemPtr GetInstance();

        // Light management
        void AddLight(std::shared_ptr<MyLight> light);
        void RemoveLight(std::shared_ptr<MyLight> light);
        void RemoveAllLights();

        // Convenience add functions
        std::shared_ptr<MyDirectionalLight> AddDirectionalLight(const MyVector3& color = MyVector3(1, 1, 1), float intensity = 1.0f);
        std::shared_ptr<MyPointLight> AddPointLight(const MyVector3& color = MyVector3(1, 1, 1), float intensity = 1.0f, float range = 10.0f);
        std::shared_ptr<MySpotLight> AddSpotLight(const MyVector3& color = MyVector3(1, 1, 1), float intensity = 1.0f, float range = 10.0f);

        // GPU data management
        void UpdateLightingData();

        // Constant buffer management
        void CreateLightingConstantBuffer();
        void UpdateLightingConstantBuffer();

        // Debug & utility
        void LogLightingSummary() const;
        void EnableAllLights();
        void DisableAllLights();

    private:
        // Helper functions
        void SortLightsByType();
        void PackLightingData();
        void ValidateLightCount();

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
        // Light access
        const std::vector<std::shared_ptr<MyLight>>& GetLights() const { return lights; }
        std::shared_ptr<MyLight> GetLight(size_t index) const;
        size_t GetLightCount() const { return lights.size(); }

        // Light type counts
        int GetDirectionalLightCount() const;
        int GetPointLightCount() const;
        int GetSpotLightCount() const;

        // Ambient lighting
        void SetAmbientLight(const MyVector3& color, float intensity = 0.1f);
        MyVector3 GetAmbientLight() const { return ambientLight; }
        float GetAmbientIntensity() const { return ambientIntensity; }

        // GPU data access
        const MyLightingData& GetLightingData() const { return lightingData; }
        MyConstantBufferPtr GetLightingConstantBuffer() const { return lightingConstantBuffer; }

        // Update control
        void SetNeedsUpdate(bool needsUpdate) { this->needsUpdate = needsUpdate; }

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    public:
        virtual void Update(float deltaTime) override;
    };
} // namespace DX3D
