#pragma once
#include "Game/Lighting/MyLight.hpp"

namespace DX3D {
    class MyPointLight : public MyLight {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
        float constantAttenuation;  // Base attenuation (usually 1.0)
        float linearAttenuation;    // Linear distance falloff
        float quadraticAttenuation; // Quadratic distance falloff

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyPointLight(const MyVector3& color = MyVector3(1.0f, 1.0f, 1.0f),
            float intensity = 1.0f,
            float range = 10.0f);
        virtual ~MyPointLight() = default;

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    public:
        // Convenience functions for common attenuation presets
        void SetAttenuationPreset_Close();     // Good for 7 unit range
        void SetAttenuationPreset_Medium();    // Good for 13 unit range  
        void SetAttenuationPreset_Far();       // Good for 20 unit range
        void SetAttenuationPreset_VeryFar();   // Good for 50 unit range

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    public:
        // Override to provide point light specific data
        MyLightData GetLightData() const override;

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:
        // Attenuation control
        void SetAttenuation(float constant, float linear, float quadratic);
        void GetAttenuation(float& constant, float& linear, float& quadratic) const;
    };

} // namespace DX3D
