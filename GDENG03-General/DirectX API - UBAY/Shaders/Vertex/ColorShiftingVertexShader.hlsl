struct VS_INPUT {
    float3 position : POSITION;
    float3 nextPosition : POSITION1;
    float3 color : COLOR;
    float3 nextColor : COLOR1;
};
struct VS_ANIMATED_OUTPUT {
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float3 nextColor : COLOR1;
};
cbuffer MyConstant: register(b0) {
    float angle;
};
VS_ANIMATED_OUTPUT main(VS_INPUT input) {
    VS_ANIMATED_OUTPUT output;
    output.position = float4(lerp(input.position, input.nextPosition, (sin(angle) + 1.0f) / 2.0f), 1.0f);
    output.color = input.color;
    output.nextColor = input.nextColor;
    return output;
}