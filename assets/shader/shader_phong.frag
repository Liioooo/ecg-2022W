#version 430 core
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

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
vec3[2] calcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3[2] calcPointLight(PointLight light, vec3 fragPos, vec3 normal, vec3 viewDir);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(eyePos - FragPos);

    vec3[2] lightResult = {vec3(0), vec3(0)}; // 0:diff,1:spec

    for (int i = 0; i < dirLightCount; i++) {
        vec3[2] result = calcDirLight(dirLights[i], norm, viewDir);
        lightResult[0] += result[0];
        lightResult[1] += result[1];
    }
    for (int i = 0; i < pointLightCount; i++) {
        vec3[2] result = calcPointLight(pointLights[i], FragPos, norm, viewDir);
        lightResult[0] += result[0];
        lightResult[1] += result[1];
    }

    float ambient = ia * ka;
    vec3 result = baseColor * (ambient + lightResult[0]) + lightResult[1];
    FragColor = vec4(result, 1.0f);
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