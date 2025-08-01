struct VS_INPUT {
    float3 position : POSITION0;
    float3 normal : NORMAL0;
    float2 textureCoordinate : TEXCOORD0;
};
struct VS_TEXTURED_OUTPUT {
    float4 position : SV_POSITION;
    float3 normal : NORMAL0;
    float2 textureCoordinate : TEXCOORD0;
};
VS_TEXTURED_OUTPUT main(VS_INPUT input) {
    VS_TEXTURED_OUTPUT output = (VS_TEXTURED_OUTPUT)0;
    return output;
}