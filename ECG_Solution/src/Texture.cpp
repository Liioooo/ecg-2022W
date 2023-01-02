//
// Created by preis on 28/12/2022.
//

#include "Texture.h"
#include "Utils.h"

Texture::Texture(const std::string &path) {
    DDSImage ddsImage = loadDDS(path.c_str());
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glCompressedTexImage2D(GL_TEXTURE_2D, 0, ddsImage.format, ddsImage.width, ddsImage.height, 0, ddsImage.size, ddsImage.data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture() {
    glDeleteTextures(1, &textureId);
}

void Texture::bindTexture(Shader *shader, const int &textureUnit, const std::string &uniformName) const {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, textureId);
    shader->setInt(uniformName, textureUnit);
}
