//
// Created by preis on 07/12/2022.
//

#ifndef ECG_SOLUTION_LIGHT_H
#define ECG_SOLUTION_LIGHT_H

#include "Shader.h"

class Light {
public:
    virtual void setUniforms(Shader* shader, int arrayPos) const = 0;
    virtual std::string getLightAmountUniformName() const = 0;
};

#endif //ECG_SOLUTION_LIGHT_H
