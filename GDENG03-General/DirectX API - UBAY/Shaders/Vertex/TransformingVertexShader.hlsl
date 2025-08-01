struct VS_INPUT {
    float3 position : POSITION;
    float3 nextPosition : POSITION1;
    float3 color : COLOR;
    float3 nextColor : COLOR1;
};
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
VS_3D_OUTPUT main(VS_INPUT input) {
    VS_3D_OUTPUT output;
    //WORLD SPACE
    output.position = mul(float4(input.position, 1.0f), world);
    //VIEW SPACE
    output.position = mul(output.position, view);
    //SCREEN SPACE
    output.position = mul(output.position, projection);
    output.color = input.color;
    output.nextColor = input.nextColor;
    return output;
}