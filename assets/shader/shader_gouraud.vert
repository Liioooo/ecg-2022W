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

uniform mat4 model;
uniform mat4 vp;
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

// Prototypes
vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 fragPos, vec3 normal, vec3 viewDir);

void main()
{
    gl_Position = vp * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);

    vec3 fragPos = vec3(model * vec4(aPos, 1.0));

    vec3 norm = normalize(mat3(transpose(inverse(model))) * aNormal);
    vec3 viewDir = normalize(eyePos - fragPos);

    float ambient = ia * ka;
    vec3 lightResult = vec3(0 ,0 ,0);

    for (int i = 0; i < dirLightCount; i++) {
        lightResult += calcDirLight(dirLights[i], norm, viewDir);
    }
    for (int i = 0; i < pointLightCount; i++) {
        lightResult += calcPointLight(pointLights[i], fragPos, norm, viewDir);
    }

    vec3 result = baseColor * (ambient + lightResult);
    vFragColor = result;
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    vec3 reflectDir = reflect(lightDir, normal);
    float spec = ks * pow(max(dot(reflectDir, viewDir), 0.0), alpha);
    float diff = kd * clamp(dot(lightDir, normal), 0, 1);
    return light.color * (spec + diff);
}

vec3 calcPointLight(PointLight light, vec3 fragPos, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 reflectDir = reflect(lightDir, normal);
    float spec = ks * pow(max(dot(reflectDir, viewDir), 0.0), alpha);
    float diff = kd * clamp(dot(lightDir, normal), 0.0, 1.0);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.aConstant + light.aLinear * distance + light.aQuadratic * distance * distance);

    return light.color * attenuation * (spec + diff);
}