Texture2D MyTexture : register(t0);
sampler Sampler : register(s0);

struct VS_TEXTURED_OUTPUT {
    float4 position : SV_POSITION;
    float2 textureCoordinate : TEXCOORD0;
};
cbuffer MyConstant: register(b0) {
    row_major float4x4 world;
    row_major float4x4 view;
    row_major float4x4 projection;
    float time;
};
float4 main(VS_TEXTURED_OUTPUT input) : SV_TARGET {
    return MyTexture.Sample(Sampler, input.textureCoordinate);
}