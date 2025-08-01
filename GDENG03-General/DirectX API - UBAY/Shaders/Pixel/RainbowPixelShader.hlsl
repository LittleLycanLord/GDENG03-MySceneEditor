struct VS_RAINBOW_OUTPUT {
    float4 position : SV_POSITION;
    float3 color : COLOR;
};
float4 main(VS_RAINBOW_OUTPUT input) : SV_TARGET {
    return float4(input.color, 1); // White
}