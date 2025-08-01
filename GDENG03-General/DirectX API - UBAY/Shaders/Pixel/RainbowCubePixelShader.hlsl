struct VS_3D_OUTPUT {
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float3 nextColor : COLOR1;
};
cbuffer MyConstant: register(b0) {
    row_major float4x4 world;
    row_major float4x4 view;
    row_major float4x4 projection;
    float time;
};
float4 main(VS_3D_OUTPUT input) : SV_TARGET {
    // return float4(lerp(input.color, input.nextColor, (sin(time) + 1.0f) / 2.0f), 1.0f);
    return float4(input.color, 1.0f); // Return the color without interpolation
}