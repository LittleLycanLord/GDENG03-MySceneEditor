Texture2D MyTexture : register(t0);
sampler Sampler : register(s0);

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

struct LightData {
    float3 position;
    int type;
    float3 direction;
    float intensity;
    float3 color;
    float range;
    float spotAngle;
    float padding1;
    float padding2;
    float padding3;
};

cbuffer LightingData: register(b1) {
    LightData lights[32];
    int numDirectionalLights;
    int numPointLights;
    int numSpotLights;
    int totalActiveLights;
    float3 ambientLight;
    float ambientIntensity;
    float lightingPadding[8];
};

float4 main(VS_TEXTURED_OUTPUT input) : SV_TARGET {
    float4 textureColor = MyTexture.Sample(Sampler, input.textureCoordinate);

    float3 surfaceNormal = normalize(input.normal);
    float3 viewDirection = normalize(input.viewDirection);

    float3 totalDiffuse = float3(0.0f, 0.0f, 0.0f);
    float3 totalSpecular = float3(0.0f, 0.0f, 0.0f);

    float shininess = 32.0f;

    // Loop through all active lights
    for (int i = 0; i < totalActiveLights; i++) {
        LightData light = lights[i];

        float3 lightDirection;
        float attenuation = 1.0f;

        if (light.type == 0) {
            // Directional light
            lightDirection = normalize(-light.direction);
        }
        else if (light.type == 1) {
            // Point light
            float3 lightVector = light.position - input.worldPosition;
            float lightDistance = length(lightVector);
            lightDirection = normalize(lightVector);
            attenuation = 1.0f / (1.0f + 0.1f * lightDistance + 0.01f * lightDistance * lightDistance);
        }
        else if (light.type == 2) {
            // Spot light
            float3 lightVector = light.position - input.worldPosition;
            float lightDistance = length(lightVector);
            lightDirection = normalize(lightVector);

            float distanceAttenuation = 1.0f / (1.0f + 0.1f * lightDistance + 0.01f * lightDistance * lightDistance);

            float spotAngle = dot(-lightDirection, normalize(light.direction));
            float innerConeAngle = cos(radians(light.spotAngle * 0.5f));
            float outerConeAngle = cos(radians(light.spotAngle));
            float spotFactor = smoothstep(outerConeAngle, innerConeAngle, spotAngle);

            attenuation = distanceAttenuation * spotFactor;
        }

        // Calculate diffuse lighting
        float diffuseFactor = max(0.0f, dot(surfaceNormal, lightDirection));

        // Calculate specular lighting
        float3 reflectionDirection = reflect(-lightDirection, surfaceNormal);
        float specularFactor = pow(max(0.0f, dot(viewDirection, reflectionDirection)), shininess);

        // Accumulate lighting contributions
        totalDiffuse += light.color * diffuseFactor * light.intensity * attenuation;
        totalSpecular += light.color * specularFactor * light.intensity * attenuation * 0.5f;
    }

    // Apply ambient lighting and combine with diffuse and specular
    float3 finalColor = textureColor.rgb * (ambientLight * ambientIntensity + totalDiffuse) + totalSpecular;

    return float4(finalColor, textureColor.a);
}