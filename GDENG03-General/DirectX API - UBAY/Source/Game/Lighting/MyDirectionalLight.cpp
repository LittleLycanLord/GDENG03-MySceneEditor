#include "Game/Lighting/MyDirectionalLight.hpp"

namespace DX3D {

    MyDirectionalLight::MyDirectionalLight(const MyVector3& color, float intensity, float range)
        : MyLight(LightType::DIRECTIONAL, color, intensity, range) {
        explicitDirection = MyVector3(0.0f, -1.0f, 0.0f);
        useExplicitDirection = false;
        this->range = range;
    }

    MyLightData MyDirectionalLight::GetLightData() const {
        MyLightData lightData = MyLight::GetLightData();

        MyVector3 direction;
        if (useExplicitDirection) {
            direction = explicitDirection;
        }
        else {
            this->CalculateDirection(direction);
        }

        // Normalize the direction
        float length = sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
        if (length > 0.0f) {
            direction.x /= length;
            direction.y /= length;
            direction.z /= length;
        }

        lightData.direction = direction;
        return lightData;
    }

    void MyDirectionalLight::SetDirection(const MyVector3& dir) {
        explicitDirection = dir;
        useExplicitDirection = true;
    }

    MyVector3 MyDirectionalLight::GetDirection() const {
        if (useExplicitDirection) {
            MyVector3 result;
            result.x = explicitDirection.x;
            result.y = explicitDirection.y;
            result.z = explicitDirection.z;
            return result;
        }
        else {
            MyVector3 direction;
            this->CalculateDirection(direction);
            return direction;
        }
    }

} // namespace DX3D
