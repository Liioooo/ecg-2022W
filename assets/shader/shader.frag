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
vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(eyePos - FragPos);

    float ambient = ia * ka;
    vec3 lightResult = vec3(0 ,0 ,0);

    for (int i = 0; i < dirLightCount; i++) {
        lightResult += calcDirLight(dirLights[i], norm, viewDir);
    }

    vec3 result = baseColor * (ambient + lightResult);
    FragColor = vec4(result, 1.0f);
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    vec3 reflectDir = reflect(lightDir, normal);
    float spec = ks * pow(max(dot(reflectDir, viewDir), 0.0), alpha);
    float diff = kd * clamp(dot(lightDir, normal), 0, 1);
    return light.color * (spec + diff);
}