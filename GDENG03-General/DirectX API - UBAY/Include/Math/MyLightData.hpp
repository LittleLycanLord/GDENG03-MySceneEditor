#pragma once
#include "Game/Lighting/MyLight.hpp"
#include "Math/MyVector3.hpp"

namespace DX3D {
    static const int MAX_LIGHTS = 32;  // Maximum lights supported by shaders

    // GPU-compatible lighting data structure
    __declspec(align(16))
    struct MyLightingData {
        MyLightData lights[MAX_LIGHTS];  // Array of light data
        int numDirectionalLights;        // Count of directional lights
        int numPointLights;              // Count of point lights  
        int numSpotLights;               // Count of spot lights
        int totalActiveLights;           // Total number of active lights
        MyVector3 ambientLight;          // Global ambient lighting
        float ambientIntensity;          // Ambient light intensity
        float padding[8];                // Ensure 16-byte alignment
    };

} // namespace DX3D
