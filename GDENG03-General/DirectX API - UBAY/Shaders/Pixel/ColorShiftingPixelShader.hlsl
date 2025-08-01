struct VS_ANIMATED_OUTPUT {
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float3 nextColor : COLOR1;
};
cbuffer MyConstant: register(b0) {
    float angle;
};
float4 main(VS_ANIMATED_OUTPUT input) : SV_TARGET {
    return float4(lerp(input.color, input.nextColor, (sin(angle) + 1.0f) / 2.0f), 1.0f);
}