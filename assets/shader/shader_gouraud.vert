#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 vFragColor;

struct DirLight {
    vec3 direction;
    vec3 color;
};

struct PointLight {
    vec3 position;
    vec3 color;
    float aConstant;
    float aLinear;
    float aQuadratic;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    vec3 color;
    float cutOff;
    float aConstant;
    float aLinear;
    float aQuadratic;
};

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 eyePos;
uniform float ia;
uniform vec3 baseColor;
uniform float ka;
uniform float kd;
uniform float ks;
uniform float alpha;
uniform DirLight dirLights[8];
uniform int dirLightCount;
uniform PointLight pointLights[8];
uniform int pointLightCount;
uniform SpotLight spotLights[8];
uniform int spotLightCount;

// Prototypes
vec3[2] calcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3[2] calcPointLight(PointLight light, vec3 fragPos, vec3 normal, vec3 viewDir);
vec3[2] calcSpotLight(SpotLight light, vec3 fragPos, vec3 normal, vec3 viewDir);

void main()
{
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);

    vec3 fragPos = vec3(model * vec4(aPos, 1.0));

    vec3 norm = normalize(mat3(transpose(inverse(model))) * aNormal);
    vec3 viewDir = normalize(eyePos - fragPos);

    vec3[2] lightResult = {vec3(0), vec3(0)}; // 0:diff,1:spec

    for (int i = 0; i < dirLightCount; i++) {
        vec3[2] result = calcDirLight(dirLights[i], norm, viewDir);
        lightResult[0] += result[0];
        lightResult[1] += result[1];
    }
    for (int i = 0; i < pointLightCount; i++) {
        vec3[2] result = calcPointLight(pointLights[i], fragPos, norm, viewDir);
        lightResult[0] += result[0];
        lightResult[1] += result[1];
    }
    for (int i = 0; i < spotLightCount; i++) {
        vec3[2] result = calcSpotLight(spotLights[i], fragPos, norm, viewDir);
        lightResult[0] += result[0];
        lightResult[1] += result[1];
    }

    float ambient = ia * ka;
    vec3 result = baseColor * (ambient + lightResult[0]) + lightResult[1];
    vFragColor = result;
}

vec3[2] calcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    vec3 reflectDir = reflect(lightDir, normal);
    float spec = ks * pow(max(dot(reflectDir, viewDir), 0.0), alpha);
    float diff = kd * clamp(dot(lightDir, normal), 0.0, 1.0);

    vec3[2] lOut = {light.color * diff, light.color * spec};
    return lOut;
}

vec3[2] calcPointLight(PointLight light, vec3 fragPos, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 reflectDir = reflect(lightDir, normal);
    float spec = ks * pow(max(dot(reflectDir, viewDir), 0.0), alpha);
    float diff = kd * clamp(dot(lightDir, normal), 0.0, 1.0);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.aConstant + light.aLinear * distance + light.aQuadratic * distance * distance);

    vec3[2] lOut = {light.color * attenuation * diff, light.color * attenuation * spec};
    return lOut;
}

vec3[2] calcSpotLight(SpotLight light, vec3 fragPos, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);

    float theta = acos(dot(lightDir, normalize(-light.direction)));

    float intensity = smoothstep(0, 0.03, max(light.cutOff - theta, 0));

    vec3 reflectDir = reflect(lightDir, normal);
    float spec = ks * pow(max(dot(reflectDir, viewDir), 0.0), alpha);
    float diff = kd * clamp(dot(lightDir, normal), 0.0, 1.0);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.aConstant + light.aLinear * distance + light.aQuadratic * distance * distance);

    vec3[2] lOut = { light.color * attenuation * intensity * diff, light.color * attenuation * intensity * spec };
    return lOut;
}