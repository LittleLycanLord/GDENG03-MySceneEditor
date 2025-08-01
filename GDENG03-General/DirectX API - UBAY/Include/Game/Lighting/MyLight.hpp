#pragma once
#include "Game/MyTransform.hpp"
#include "Math/MyVector3.hpp"
#include <memory>

namespace DX3D {
    // Light data structure for GPU constant buffer
    __declspec(align(16))
        struct MyLightData {
        MyVector3 position;     // World position (point/spot lights)
        int type;               // 0=Directional, 1=Point, 2=Spot

        MyVector3 direction;    // Direction (directional/spot lights)
        float intensity;        // Light intensity multiplier

        MyVector3 color;        // RGB color values (0.0-1.0)
        float range;            // Maximum light range

        float spotAngle;        // Spot light cone angle (degrees)
        float padding1;         // 16-byte alignment padding
        float padding2;         // 16-byte alignment padding
        float padding3;         // 16-byte alignment padding
    };

    enum class LightType {
        DIRECTIONAL = 0,
        POINT = 1,
        SPOT = 2
    };

    class MyLight {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    public:
        std::shared_ptr<MyTransform> transform;

    protected:
        MyVector3 color;
        float intensity;
        float range;
        LightType lightType;
        bool enabled;

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    protected:
        // Protected constructor - only derived classes can create lights
        MyLight(LightType type, const MyVector3& color = MyVector3(1.0f, 1.0f, 1.0f),
            float intensity = 1.0f, float range = 100.0f);

    public:
        virtual ~MyLight() = default;

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    public:
        // Enable/disable the light
        void SetEnabled(bool enabled);

        // Update light (called per frame)
        virtual void Update(float deltaTime);

    protected:
        virtual void CalculateDirection(MyVector3& direction) const;

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    public:
        // Get light data for GPU constant buffer
        virtual MyLightData GetLightData() const;

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
        // Light properties
        void SetColor(const MyVector3& color);
        void SetIntensity(float intensity);
        void SetRange(float range);

        MyVector3 GetColor() const;
        float GetIntensity() const;
        float GetRange() const;
        LightType GetType() const;
        bool IsEnabled() const;
    };

} // namespace DX3D
