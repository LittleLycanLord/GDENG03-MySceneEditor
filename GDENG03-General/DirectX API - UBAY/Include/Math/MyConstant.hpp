#pragma once
#include "Math/MyMatrix4x4.hpp"
#include "Math/MyVector3.hpp"

namespace DX3D {
    // GPU constant buffer alignment - must be 16-byte aligned
    __declspec(align(16))
    struct MyConstant {
        MyMatrix4x4 world;
        MyMatrix4x4 view;
        MyMatrix4x4 projection;
        float time = 0.0f;
        MyVector3 cameraPosition;
    };

    // Note: Lighting data is now handled by MyLightManager's separate constant buffer
    // This keeps the transform data and lighting data in separate buffers for better performance
    // and organization. The lighting constant buffer is bound to register(b1) in shaders.
} // namespace DX3D

// namespace DX3D {
//     __declspec(align(16))
//         struct MyConstant {
//         float angle;
//     };
// } // namespace DX3D

