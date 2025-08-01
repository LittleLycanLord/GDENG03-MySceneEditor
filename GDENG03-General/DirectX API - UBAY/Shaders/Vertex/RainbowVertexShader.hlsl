struct VS_INPUT {
    float3 position : POSITION;
    float3 color : COLOR;
};
struct VS_RAINBOW_OUTPUT {
    float4 position : SV_POSITION;
    float3 color : COLOR;
};
VS_RAINBOW_OUTPUT main(VS_INPUT input) {
    VS_RAINBOW_OUTPUT output;
    output.position = float4(input.position, 1.0f);
    output.color = input.color;
    return output;
}