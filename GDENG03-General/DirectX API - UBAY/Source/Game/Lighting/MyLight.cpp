#include "Game/Lighting/MyLight.hpp"
#include "Core/MyLogger.hpp"
#include <cmath>

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyLight::MyLight(LightType type, const MyVector3& color, float intensity, float range) 
    : lightType(type), color(color), intensity(intensity), range(range), enabled(true) {
    
    // Create transform component
    this->transform = std::make_shared<MyTransform>();
    
    if (LOG_INFO_LIGHTING) std::cout << "[INFO]: MyLight base class constructed with type: " 
                                     << static_cast<int>(type) << std::endl;
    LOG_INFO("LIGHTING", "MyLight base class created");
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
void MyLight::SetEnabled(bool enabled) {
    this->enabled = enabled;
    if (LOG_INFO_LIGHTING) std::cout << "[INFO]: Light enabled state set to " << (enabled ? "true" : "false") << std::endl;
}

void MyLight::SetColor(const MyVector3& color) {
    this->color = color;
    if (LOG_INFO_LIGHTING) std::cout << "[INFO]: Light color set to (" << color.x << ", " << color.y << ", " << color.z << ")" << std::endl;
}

void MyLight::SetIntensity(float intensity) {
    this->intensity = intensity;
    if (LOG_INFO_LIGHTING) std::cout << "[INFO]: Light intensity set to " << intensity << std::endl;
}

void MyLight::SetRange(float range) {
    this->range = range;
    if (LOG_INFO_LIGHTING) std::cout << "[INFO]: Light range set to " << range << std::endl;
}

void MyLight::Update(float deltaTime) {
    // Update transform
    if (this->transform) {
        this->transform->Update(deltaTime);
    }
}

void MyLight::CalculateDirection(MyVector3& direction) const {
    // Convert rotation to direction vector
    // Default forward direction is (0, 0, 1)
    float pitch = this->transform->rotation.x * 3.14159265f / 180.0f;
    float yaw = this->transform->rotation.y * 3.14159265f / 180.0f;
    
    direction.x = sin(yaw) * cos(pitch);
    direction.y = -sin(pitch);
    direction.z = cos(yaw) * cos(pitch);
    
    // Normalize
    float length = sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
    if (length > 0.0f) {
        direction.x /= length;
        direction.y /= length;
        direction.z /= length;
    }
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
MyLightData MyLight::GetLightData() const {
    MyLightData data;
    
    // Clear all data first (important for GPU buffer)
    memset(&data, 0, sizeof(MyLightData));
    
    // Fill common light data
    data.position = this->transform->position;
    data.type = static_cast<int>(this->lightType);
    data.color = this->color;
    data.intensity = this->intensity;
    data.range = this->range;
    
    // Calculate direction from transform rotation
    MyVector3 direction;
    this->CalculateDirection(direction);
    data.direction = direction;
    
    return data;
}

MyVector3 MyLight::GetColor() const {
    return this->color;
}

float MyLight::GetIntensity() const {
    return this->intensity;
}

float MyLight::GetRange() const {
    return this->range;
}

LightType MyLight::GetType() const {
    return this->lightType;
}

bool MyLight::IsEnabled() const {
    return this->enabled;
}
