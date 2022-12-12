//
// Created by preis on 11/12/2022.
//

#include "Material.h"

void Material::setUniforms(Shader *shader) const {
    shader->setVec3("baseColor", baseColor);
    shader->setFloat("ka", ka);
    shader->setFloat("kd", kd);
    shader->setFloat("ks", ks);
    shader->setFloat("alpha", alpha);
}
