#include "Game/Lighting/MyPointLight.hpp"
#include "Core/MyLogger.hpp"

namespace DX3D {

    MyPointLight::MyPointLight(const MyVector3& color, float intensity, float range)
        : MyLight(LightType::POINT, color, intensity, range)
        , constantAttenuation(1.0f)   // Standard constant value
        , linearAttenuation(0.09f)    // Good for medium range lighting
        , quadraticAttenuation(0.032f) // Realistic quadratic falloff
    {
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyPointLight created with color(" << color.x << ", " << color.y << ", " << color.z << "), intensity(" << intensity << "), range(" << range << ")" << std::endl;
    }

    MyLightData MyPointLight::GetLightData() const {
        MyLightData lightData = MyLight::GetLightData();
        
        // For point lights, position is crucial
        lightData.position = transform->position;
        
        // Store attenuation data in unused direction field for now
        // This is a temporary solution - proper implementation would require shader updates
        
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyPointLight data: position(" << lightData.position.x << ", " << lightData.position.y << ", " << lightData.position.z << "), "
                         << "attenuation(c:" << constantAttenuation << ", l:" << linearAttenuation << ", q:" << quadraticAttenuation << "), "
                         << "intensity(" << intensity << "), range(" << range << ")" << std::endl;
        
        return lightData;
    }

    void MyPointLight::SetAttenuation(float constant, float linear, float quadratic) {
        constantAttenuation = constant;
        linearAttenuation = linear;
        quadraticAttenuation = quadratic;
        
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyPointLight attenuation set to: constant(" << constant << "), linear(" << linear << "), quadratic(" << quadratic << ")" << std::endl;
    }

    void MyPointLight::GetAttenuation(float& constant, float& linear, float& quadratic) const {
        constant = constantAttenuation;
        linear = linearAttenuation;
        quadratic = quadraticAttenuation;
    }

    void MyPointLight::SetAttenuationPreset_Close() {
        SetAttenuation(1.0f, 0.7f, 1.8f);
        range = 7.0f;
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyPointLight attenuation set to Close preset (range: 7)" << std::endl;
    }

    void MyPointLight::SetAttenuationPreset_Medium() {
        SetAttenuation(1.0f, 0.35f, 0.44f);
        range = 13.0f;
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyPointLight attenuation set to Medium preset (range: 13)" << std::endl;
    }

    void MyPointLight::SetAttenuationPreset_Far() {
        SetAttenuation(1.0f, 0.22f, 0.20f);
        range = 20.0f;
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyPointLight attenuation set to Far preset (range: 20)" << std::endl;
    }

    void MyPointLight::SetAttenuationPreset_VeryFar() {
        SetAttenuation(1.0f, 0.09f, 0.032f);
        range = 50.0f;
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyPointLight attenuation set to VeryFar preset (range: 50)" << std::endl;
    }

} // namespace DX3D
