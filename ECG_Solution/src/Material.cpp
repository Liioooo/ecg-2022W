//
// Created by preis on 11/12/2022.
//

#include "Material.h"

void Material::setUniforms(Shader *shader) const {
    if (diffTexture != nullptr) {
        diffTexture->bindTexture(shader, 0, "diffTexture");
    }
    if (specTexture != nullptr) {
        specTexture->bindTexture(shader, 1, "specTexture");
    }
    shader->setBool("hasMatDiffTexture", diffTexture != nullptr);
    shader->setBool("hasMatSpecTexture", specTexture != nullptr);
    shader->setVec3("baseColor", baseColor);
    shader->setFloat("ka", ka);
    shader->setFloat("kd", kd);
    shader->setFloat("ks", ks);
    shader->setFloat("alpha", alpha);
}
