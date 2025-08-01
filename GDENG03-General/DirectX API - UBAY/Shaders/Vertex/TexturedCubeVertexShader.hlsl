struct VS_INPUT {
    float3 position : POSITION0;
    float2 textureCoordinate : TEXCOORD0;
};
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
VS_TEXTURED_OUTPUT main(VS_INPUT input) {
    VS_TEXTURED_OUTPUT output;
    //WORLD SPACE
    output.position = mul(float4(input.position, 1.0f), world);
    //VIEW SPACE
    output.position = mul(output.position, view);
    //SCREEN SPACE
    output.position = mul(output.position, projection);
    output.textureCoordinate = input.textureCoordinate;
    return output;
}