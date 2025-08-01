#define NUM_CONTROL_POINTS 3

struct VS_TEXTURED_OUTPUT {
    float4 position : SV_POSITION;
    float2 textureCoordinate : TEXCOORD0;
};

struct HS_CONTROL_POINT_OUTPUT {
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

// Patch constant function
HS_CONSTANT_DATA_OUTPUT PatchConstants(InputPatch<VS_TEXTURED_OUTPUT, NUM_CONTROL_POINTS> patch, uint patchID : SV_PrimitiveID)
{
    HS_CONSTANT_DATA_OUTPUT output;

    // Dynamic tessellation factor, can be animated
    // float tessFactor = 5.0f + sin(time) * 2.0f;
    // float tessFactor = tessFactor = 1.0 + sin(time) * 5.0;
    float tessFactor = 3.0 + sin(time * 2.0) * 2.0;

    output.edges[0] = tessFactor;
    output.edges[1] = tessFactor;
    output.edges[2] = tessFactor;
    output.inside = tessFactor;

    return output;
}

[domain("tri")]
[partitioning("fractional_even")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(NUM_CONTROL_POINTS)]
[patchconstantfunc("PatchConstants")]
HS_CONTROL_POINT_OUTPUT main(InputPatch<VS_TEXTURED_OUTPUT, NUM_CONTROL_POINTS> patch, uint i : SV_OutputControlPointID)
{
    HS_CONTROL_POINT_OUTPUT output;
    output.position = patch[i].position;
    output.textureCoordinate = patch[i].textureCoordinate;
    return output;
}
