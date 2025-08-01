#define NUM_CONTROL_POINTS 3

struct VS_TEXTURED_OUTPUT {
    float4 position : SV_POSITION;
    float2 textureCoordinate : TEXCOORD0;
    float3 normal : NORMAL0;
    float3 worldPosition : TEXCOORD1;
    float3 viewDirection : TEXCOORD2;
};

struct HS_CONTROL_POINT_OUTPUT {
    float4 position : SV_POSITION;
    float2 textureCoordinate : TEXCOORD0;
    float3 normal : NORMAL0;
    float3 worldPosition : TEXCOORD1;
    float3 viewDirection : TEXCOORD2;
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

// Patch constant function - minimal tessellation (1.0 = no subdivision)
HS_CONSTANT_DATA_OUTPUT PatchConstants(InputPatch<VS_TEXTURED_OUTPUT, NUM_CONTROL_POINTS> patch, uint patchID : SV_PrimitiveID)
{
    HS_CONSTANT_DATA_OUTPUT output;

    // No tessellation - just pass through (1.0 = no subdivision)
    output.edges[0] = 1.0f;
    output.edges[1] = 1.0f;
    output.edges[2] = 1.0f;
    output.inside = 1.0f;

    return output;
}

[domain("tri")]
[partitioning("integer")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(NUM_CONTROL_POINTS)]
[patchconstantfunc("PatchConstants")]
HS_CONTROL_POINT_OUTPUT main(InputPatch<VS_TEXTURED_OUTPUT, NUM_CONTROL_POINTS> patch, uint pointID : SV_OutputControlPointID, uint patchID : SV_PrimitiveID)
{
    HS_CONTROL_POINT_OUTPUT output;

    output.position = patch[pointID].position;
    output.textureCoordinate = patch[pointID].textureCoordinate;
    output.normal = patch[pointID].normal;
    output.worldPosition = patch[pointID].worldPosition;
    output.viewDirection = patch[pointID].viewDirection;

    return output;
}
