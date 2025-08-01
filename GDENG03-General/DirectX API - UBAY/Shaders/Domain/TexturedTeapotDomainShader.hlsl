#define NUM_CONTROL_POINTS 3

struct HS_CONTROL_POINT_OUTPUT {
    float4 position : SV_POSITION;
    float2 textureCoordinate : TEXCOORD0;
};

struct VS_TEXTURED_OUTPUT {
    float4 position : SV_POSITION;
    float2 textureCoordinate : TEXCOORD0;
};

struct HS_CONSTANT_DATA_OUTPUT {
    float edges[3] : SV_TessFactor;
    float inside : SV_InsideTessFactor;
};

cbuffer MyConstant : register(b0) {
    row_major float4x4 world;
    row_major float4x4 view;
    row_major float4x4 projection;
    float time;
};

[domain("tri")]
VS_TEXTURED_OUTPUT main(HS_CONSTANT_DATA_OUTPUT input,
                        const OutputPatch<HS_CONTROL_POINT_OUTPUT, NUM_CONTROL_POINTS> patch,
                        float3 barycentricCoordinates : SV_DomainLocation)
{
    VS_TEXTURED_OUTPUT output;

    // Interpolate position and UV
    output.position =
        patch[0].position * barycentricCoordinates.x +
        patch[1].position * barycentricCoordinates.y +
        patch[2].position * barycentricCoordinates.z;

    output.textureCoordinate =
        patch[0].textureCoordinate * barycentricCoordinates.x +
        patch[1].textureCoordinate * barycentricCoordinates.y +
        patch[2].textureCoordinate * barycentricCoordinates.z;

    return output;
}
