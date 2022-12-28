//
// Created by preis on 28/12/2022.
//

#ifndef ECG_SOLUTION_TEXTURE_H
#define ECG_SOLUTION_TEXTURE_H


#include <string>
#include "Shader.h"

class Texture {
public:
    explicit Texture(const std::string &path);

    void bindTexture(Shader *shader, const int &textureUnit, const std::string &uniformName) const;

private:
    unsigned int textureId;
};


#endif //ECG_SOLUTION_TEXTURE_H
