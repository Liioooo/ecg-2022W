//
// Created by preis on 11/12/2022.
//

#ifndef ECG_SOLUTION_MATERIAL_H
#define ECG_SOLUTION_MATERIAL_H


#include "Shader.h"
#include "glm/detail/type_vec3.hpp"
#include "Texture.h"

class Material {
public:
    Material(glm::vec3 baseColor, const float ka, const float kd, const float ks, const float alpha) : baseColor(baseColor), ka(ka), kd(kd), ks(ks), alpha(alpha) {};
    Material(Texture* texture, const float ka, const float kd, const float ks, const float alpha) : texture(texture), ka(ka), kd(kd), ks(ks), alpha(alpha) {};

    void setUniforms(Shader* shader) const;

private:
    glm::vec3 baseColor;
    Texture* texture = nullptr;
    float ka;
    float kd;
    float ks;
    float alpha;
};


#endif //ECG_SOLUTION_MATERIAL_H
