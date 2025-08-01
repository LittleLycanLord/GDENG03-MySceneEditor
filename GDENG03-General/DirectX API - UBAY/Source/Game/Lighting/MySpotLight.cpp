#include "Game/Lighting/MySpotLight.hpp"
#include "Core/MyLogger.hpp"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace DX3D {

    MySpotLight::MySpotLight(const MyVector3& color, float intensity, float range, float innerConeAngle, float outerConeAngle)
        : MyLight(LightType::SPOT, color, intensity, range)
        , innerConeAngle(innerConeAngle)
        , outerConeAngle(outerConeAngle)
        , constantAttenuation(1.0f)
        , linearAttenuation(0.09f)
        , quadraticAttenuation(0.032f)
        , explicitDirection(MyVector3(0.0f, -1.0f, 0.0f))
        , useExplicitDirection(false)
    {
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MySpotLight created with color(" << color.x << ", " << color.y << ", " << color.z << "), "
                         << "intensity(" << intensity << "), range(" << range << "), "
                         << "innerAngle(" << innerConeAngle << "°), outerAngle(" << outerConeAngle << "°)" << std::endl;
        
        // Validate cone angles
        if (innerConeAngle > outerConeAngle) {
            if (LOG_ERROR_GENERAL) std::cout << "[ERROR]: MySpotLight: Inner cone angle (" << innerConeAngle << "°) cannot be larger than outer cone angle (" << outerConeAngle << "°)" << std::endl;
            this->innerConeAngle = outerConeAngle * 0.8f; // Set inner to 80% of outer
        }
    }

    MyLightData MySpotLight::GetLightData() const {
        MyLightData lightData = MyLight::GetLightData();
        
        // Position is crucial for spotlights
        lightData.position = transform->position;
        
        // Get direction (explicit or from transform)
        MyVector3 direction;
        if (useExplicitDirection) {
            direction = explicitDirection;
        } else {
            this->CalculateDirection(direction);
        }
        
        // Normalize direction
        float length = sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
        if (length > 0.0f) {
            direction.x /= length;
            direction.y /= length;
            direction.z /= length;
        }
        
        // Store direction
        lightData.direction = direction;
        
        // Store spotlight cone angle in spotAngle field
        lightData.spotAngle = outerConeAngle;
        
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MySpotLight data: position(" << lightData.position.x << ", " << lightData.position.y << ", " << lightData.position.z << "), "
                         << "direction(" << direction.x << ", " << direction.y << ", " << direction.z << "), "
                         << "innerAngle(" << innerConeAngle << "°), outerAngle(" << outerConeAngle << "°), "
                         << "intensity(" << intensity << "), range(" << range << ")" << std::endl;
        
        return lightData;
    }

    void MySpotLight::SetConeAngles(float innerAngle, float outerAngle) {
        if (innerAngle > outerAngle) {
            if (LOG_ERROR_GENERAL) std::cout << "[ERROR]: MySpotLight: Inner cone angle (" << innerAngle << "°) cannot be larger than outer cone angle (" << outerAngle << "°)" << std::endl;
            return;
        }
        
        innerConeAngle = innerAngle;
        outerConeAngle = outerAngle;
        
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MySpotLight cone angles set: inner(" << innerAngle << "°), outer(" << outerAngle << "°)" << std::endl;
    }

    void MySpotLight::GetConeAngles(float& innerAngle, float& outerAngle) const {
        innerAngle = innerConeAngle;
        outerAngle = outerConeAngle;
    }

    void MySpotLight::SetInnerConeAngle(float angle) {
        if (angle > outerConeAngle) {
            if (LOG_ERROR_GENERAL) std::cout << "[ERROR]: MySpotLight: Inner cone angle (" << angle << "°) cannot be larger than outer cone angle (" << outerConeAngle << "°)" << std::endl;
            return;
        }
        innerConeAngle = angle;
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MySpotLight inner cone angle set to " << angle << "°" << std::endl;
    }

    void MySpotLight::SetOuterConeAngle(float angle) {
        if (angle < innerConeAngle) {
            if (LOG_ERROR_GENERAL) std::cout << "[ERROR]: MySpotLight: Outer cone angle (" << angle << "°) cannot be smaller than inner cone angle (" << innerConeAngle << "°)" << std::endl;
            return;
        }
        outerConeAngle = angle;
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MySpotLight outer cone angle set to " << angle << "°" << std::endl;
    }

    float MySpotLight::GetInnerConeAngle() const {
        return innerConeAngle;
    }

    float MySpotLight::GetOuterConeAngle() const {
        return outerConeAngle;
    }

    void MySpotLight::SetAttenuation(float constant, float linear, float quadratic) {
        constantAttenuation = constant;
        linearAttenuation = linear;
        quadraticAttenuation = quadratic;
        
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MySpotLight attenuation set to: constant(" << constant << "), linear(" << linear << "), quadratic(" << quadratic << ")" << std::endl;
    }

    void MySpotLight::GetAttenuation(float& constant, float& linear, float& quadratic) const {
        constant = constantAttenuation;
        linear = linearAttenuation;
        quadratic = quadraticAttenuation;
    }

    void MySpotLight::SetDirection(const MyVector3& direction) {
        explicitDirection = direction;
        useExplicitDirection = true;
        
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MySpotLight direction set explicitly to (" << direction.x << ", " << direction.y << ", " << direction.z << ")" << std::endl;
    }

    MyVector3 MySpotLight::GetDirection() const {
        if (useExplicitDirection) {
            return explicitDirection;
        } else {
            MyVector3 direction;
            this->CalculateDirection(direction);
            return direction;
        }
    }

    void MySpotLight::SetFlashlightPreset() {
        SetConeAngles(10.0f, 15.0f);
        SetAttenuation(1.0f, 0.35f, 0.44f);
        range = 20.0f;
        intensity = 3.0f;
        
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MySpotLight set to Flashlight preset" << std::endl;
    }

    void MySpotLight::SetStageSpotPreset() {
        SetConeAngles(30.0f, 45.0f);
        SetAttenuation(1.0f, 0.14f, 0.07f);
        range = 35.0f;
        intensity = 5.0f;
        
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MySpotLight set to Stage Spot preset" << std::endl;
    }

    void MySpotLight::SetCarHeadlightPreset() {
        SetConeAngles(20.0f, 35.0f);
        SetAttenuation(1.0f, 0.09f, 0.032f);
        range = 50.0f;
        intensity = 4.0f;
        
        if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MySpotLight set to Car Headlight preset" << std::endl;
    }

    float MySpotLight::DegreesToRadians(float degrees) const {
        return degrees * (float)M_PI / 180.0f;
    }

    float MySpotLight::RadiansToDegrees(float radians) const {
        return radians * 180.0f / (float)M_PI;
    }

} // namespace DX3D
