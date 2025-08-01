# DirectX 3D Game Engine - Lighting System Documentation

## Overview
Your lighting implementation supports three types of lights:
- **Directional Lights** (Type 0): Simulate sunlight with parallel rays
- **Point Lights** (Type 1): Emit light in all directions from a point
- **Spot Lights** (Type 2): Emit light in a cone shape

## Issues Fixed

### 1. Constant Buffer Alignment
**Problem**: The `MyConstant` structure had misaligned data that could cause corruption when transferred to the GPU.

**Solution**: Added proper padding between `lightCount` and `lights` array:
```cpp
struct MyConstant {
    MyMatrix4x4 world;
    MyMatrix4x4 view;
    MyMatrix4x4 projection;
    float time;
    int lightCount;
    float padding1;      // Added
    float padding2;      // Added
    MyLightData lights[16];
};
```

### 2. Improved Lighting Calculations
**Problem**: The pixel shader had hardcoded light limits and suboptimal attenuation formulas.

**Solution**: 
- Removed the hardcoded limit of 3 lights
- Improved attenuation formula for more realistic lighting
- Added proper spot light cone calculations
- Added tone mapping for better color representation

### 3. Normal Transformation
**Problem**: Normals weren't being properly normalized after transformation.

**Solution**: Added normalization in the vertex shader:
```hlsl
output.worldNormal = normalize(mul(input.normal, (float3x3)world));
```

### 4. Memory Safety
**Problem**: No bounds checking for shader bytecode buffer.

**Solution**: Added proper size validation before copying shader bytecode.

### 5. Light Data Initialization

### 6. Normal Data Support (Latest Update)
**Problem**: MyMesh was not storing or processing normal vectors, preventing proper lighting calculations.

**Solution**: 
- Updated `MyMeshVertex` structure to include normal data:
```cpp
class MyMeshVertex {
public:
    MyVector3 position;
    MyVector3 normal;           // Added normal support
    MyVector2 textureCoordinates;
};
```

- Modified mesh loading to read normals from OBJ files:
```cpp
// NORMAL - Read from tinyobj loader
tinyobj::real_t nx = 0.0f, ny = 0.0f, nz = 0.0f;
if (index.normal_index >= 0 && !this->attributes.normals.empty()) {
    nx = this->attributes.normals[index.normal_index * 3 + 0];
    ny = this->attributes.normals[index.normal_index * 3 + 1];
    nz = this->attributes.normals[index.normal_index * 3 + 2];
}
```

- Updated vertex input layout to include NORMAL semantic:
```cpp
static D3D11_INPUT_ELEMENT_DESC layout[] = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,           D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(MyMeshVertex, normal), D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, offsetof(MyMeshVertex, textureCoordinates), D3D11_INPUT_PER_VERTEX_DATA, 0 }
};
```

- Updated layout shader to process normal data properly
- Modified DrawLoop to use lighting shaders by default when `useLightingShaders` is enabled
**Problem**: Uninitialized light data could cause unpredictable behavior.

**Solution**: Clear all light data before filling with actual light information.

## Usage Guide

### Creating Lights

```cpp
// Point Light
auto pointLight = std::make_shared<MyPointLight>(
    MyVector3(1.0f, 1.0f, 1.0f),  // Color (RGB)
    50.0f,                         // Intensity
    100.0f                         // Range
);
pointLight->transform->position = MyVector3(0.0f, 1.0f, 0.0f);
pointLight->transform->Update(0.0f);

// Directional Light
auto directionalLight = std::make_shared<MyDirectionalLight>(
    MyVector3(1.0f, 0.8f, 0.6f),  // Warm sunlight color
    2.0f,                          // Intensity
    1000.0f                        // Range (not used for directional)
);
directionalLight->transform->rotation = MyVector3(-45.0f, 30.0f, 0.0f);
directionalLight->transform->Update(0.0f);

// Spot Light
auto spotLight = std::make_shared<MySpotLight>(
    MyVector3(0.0f, 1.0f, 0.0f),  // Green color
    40.0f,                         // Intensity
    50.0f,                         // Range
    30.0f                          // Spot angle in degrees
);
spotLight->transform->position = MyVector3(5.0f, 5.0f, 5.0f);
spotLight->transform->rotation = MyVector3(-45.0f, -45.0f, 0.0f);
spotLight->transform->Update(0.0f);
```

### Adding Lights to Scene

```cpp
this->lights.push_back(pointLight);
this->lights.push_back(directionalLight);
this->lights.push_back(spotLight);
```

## Debugging Tips

### Using the Debug Shader
Switch to `DebugLightingPixelShader.hlsl` to troubleshoot lighting issues:

- **Magenta**: No lights in scene
- **Yellow**: Light is disabled
- **Dark Red**: Out of light range
- **Dark Blue**: Outside spot light cone
- **Red tint**: Directional light active
- **Green tint**: Point light active
- **Blue tint**: Spot light active

### Common Issues and Solutions

1. **Lights not visible**:
   - Check if `enabled = true`
   - Verify light intensity > 0
   - Ensure objects are within light range
   - Update light transforms after setting position/rotation

2. **Strange lighting artifacts**:
   - Verify normal calculations
   - Check for proper matrix transformations
   - Ensure constant buffer is properly updated

3. **Performance issues**:
   - Limit active lights (16 max supported)
   - Use appropriate light ranges
   - Consider light culling for distant lights

### Recommended Light Settings

**Outdoor Scene (Sunlight)**:
```cpp
auto sun = std::make_shared<MyDirectionalLight>(
    MyVector3(1.0f, 0.95f, 0.8f), // Warm sunlight
    3.0f,                          // Strong intensity
    1000.0f                        // Large range
);
sun->transform->rotation = MyVector3(-30.0f, 45.0f, 0.0f);
```

**Indoor Scene (Room lighting)**:
```cpp
auto roomLight = std::make_shared<MyPointLight>(
    MyVector3(1.0f, 0.9f, 0.7f),  // Warm white
    25.0f,                         // Moderate intensity
    15.0f                          // Limited range
);
```

**Flashlight/Spotlight**:
```cpp
auto flashlight = std::make_shared<MySpotLight>(
    MyVector3(1.0f, 1.0f, 0.9f),  // Cool white
    50.0f,                         // High intensity
    30.0f,                         // Medium range
    15.0f                          // Narrow cone
);
```

## Technical Details

- **Maximum Lights**: 16 simultaneous lights
- **Light Types**: 0=Directional, 1=Point, 2=Spot
- **Attenuation Formula**: `1.0 / (1.0 + 0.09 * distance + 0.032 * distance²)`
- **Memory Alignment**: All structures are 16-byte aligned for GPU compatibility

The lighting system now provides robust, realistic lighting with proper error handling and debugging capabilities.
