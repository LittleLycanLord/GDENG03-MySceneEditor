struct VS_ANIMATED_OUTPUT {
    float4 position : SV_POSITION;
    float3 color : COLOR;
};
cbuffer MyConstant: register(b0) {
    float angle;
};
float4 main(VS_ANIMATED_OUTPUT input) : SV_TARGET {
    return float4(input.color, 1); // White
}