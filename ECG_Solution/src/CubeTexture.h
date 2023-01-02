//
// Created by preis on 29/12/2022.
//

#ifndef ECG_SOLUTION_CUBETEXTURE_H
#define ECG_SOLUTION_CUBETEXTURE_H


#include <vector>
#include <string>
#include "Shader.h"

class CubeTexture {
public:
    explicit CubeTexture(const std::vector<std::string>& textures);
    ~CubeTexture();

    void bindTexture(Shader *shader, const int &textureUnit, const std::string &uniformName) const;

private:
    unsigned int textureId;
};


#endif //ECG_SOLUTION_CUBETEXTURE_H
