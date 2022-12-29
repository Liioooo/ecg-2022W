//
// Created by preis on 29/12/2022.
//

#include "CubeTexture.h"
#include "Utils.h"

/**
 *
 * @param textures Paths to texture parts in following order:
 * +X (right)
 * -X (left)
 * +Y (top)
 * -Y (bottom)
 * +Z (front)
 * -Z (back)
 */
CubeTexture::CubeTexture(const std::vector<std::string> &textures) {
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    for (unsigned int i = 0; i < textures.size(); i++) {
        DDSImage ddsImage = loadDDS(textures[i].c_str());
        glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, ddsImage.format, ddsImage.width, ddsImage.height, 0, ddsImage.size, ddsImage.data);
    }
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
}

void CubeTexture::bindTexture(Shader *shader, const int &textureUnit, const string &uniformName) const {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    shader->setInt(uniformName, textureUnit);
}
