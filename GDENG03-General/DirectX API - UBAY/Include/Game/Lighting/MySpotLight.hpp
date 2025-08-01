#pragma once
#include "Game/Lighting/MyLight.hpp"

namespace DX3D {
    class MySpotLight : public MyLight {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        float innerConeAngle;       // Inner cone angle in degrees (full brightness)
        float outerConeAngle;       // Outer cone angle in degrees (fade to zero)

        float constantAttenuation;  // Base attenuation (usually 1.0)
        float linearAttenuation;    // Linear distance falloff
        float quadraticAttenuation; // Quadratic distance falloff

        MyVector3 explicitDirection; // Optional explicit direction
        bool useExplicitDirection;   // Whether to use explicit direction or transform rotation

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MySpotLight(const MyVector3& color = MyVector3(1.0f, 1.0f, 1.0f),
            float intensity = 1.0f,
            float range = 10.0f,
            float innerConeAngle = 20.0f,  // degrees
            float outerConeAngle = 30.0f); // degrees
        virtual ~MySpotLight() = default;

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    public:
        // Convenience presets
        void SetFlashlightPreset();   // Narrow, focused beam
        void SetStageSpotPreset();    // Wide, dramatic lighting
        void SetCarHeadlightPreset(); // Automotive lighting

    private:
        // Helper functions
        float DegreesToRadians(float degrees) const;
        float RadiansToDegrees(float radians) const;

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    public:
        // Override to provide spotlight specific data
        MyLightData GetLightData() const override;

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
        // Cone angle control (in degrees)
        void SetConeAngles(float innerAngle, float outerAngle);
        void GetConeAngles(float& innerAngle, float& outerAngle) const;

        void SetInnerConeAngle(float angle);
        void SetOuterConeAngle(float angle);
        float GetInnerConeAngle() const;
        float GetOuterConeAngle() const;

        // Attenuation control (inherited from point light behavior)
        void SetAttenuation(float constant, float linear, float quadratic);
        void GetAttenuation(float& constant, float& linear, float& quadratic) const;

        // Direction control (alternative to using transform rotation)
        void SetDirection(const MyVector3& direction);
        MyVector3 GetDirection() const;
    };

} // namespace DX3D
