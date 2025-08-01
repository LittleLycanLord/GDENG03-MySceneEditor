struct VS_INPUT {
    float3 position : POSITION0;
    float3 normal : NORMAL0;
    float2 textureCoordinate : TEXCOORD0;
};
struct VS_TEXTURED_OUTPUT {
    float4 position : SV_POSITION;
    float2 textureCoordinate : TEXCOORD0;
    float3 normal : NORMAL0;
    float3 worldPosition : TEXCOORD1;
    float3 viewDirection : TEXCOORD2;
};
cbuffer MyConstant: register(b0) {
    row_major float4x4 world;
    row_major float4x4 view;
    row_major float4x4 projection;
    float time;
    float3 cameraPosition;
    float padding;
};
VS_TEXTURED_OUTPUT main(VS_INPUT input) {
    VS_TEXTURED_OUTPUT output;

    float4 worldPosition = mul(float4(input.position, 1.0f), world);
    output.worldPosition = worldPosition.xyz;

    output.position = mul(worldPosition, view);
    output.position = mul(output.position, projection);

    output.textureCoordinate = input.textureCoordinate;

    float3x3 normalMatrix = (float3x3)transpose(world);
    output.normal = normalize(mul(input.normal, normalMatrix));

    output.viewDirection = normalize(cameraPosition - output.worldPosition);

    return output;
}