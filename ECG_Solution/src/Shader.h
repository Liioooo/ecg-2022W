//
// Created by preis on 05/10/2022.
//
#pragma once


#include <string>
#include "glm/fwd.hpp"

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void use();
    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setVec3(const std::string &name, const glm::vec3 &vec);
    void setMat4(const std::string &name, const glm::mat4 &mat);

private:
    unsigned int programId;

    void checkErrors(unsigned int id, const std::string& type);
};