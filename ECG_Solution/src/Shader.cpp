//
// Created by preis on 05/10/2022.
//

#include "Shader.h"
#include "Utils.h"
#include <fstream>

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
    std::string vertCode;
    std::string fragCode;

    std::ifstream vertIn ;
    std::ifstream fragIn;
    vertIn.exceptions(std::ifstream::badbit);
    fragIn.exceptions(std::ifstream::badbit);

    try {
        vertIn.open(vertexPath);
        fragIn.open(fragmentPath);

        std::string line;
        while (std::getline(vertIn, line)) {
            vertCode += line + "\n";
        }
        while (std::getline(fragIn, line)) {
            fragCode += line + "\n";
        }
    } catch (const std::ifstream::failure& e) {
        EXIT_WITH_ERROR(e.what())
    }

    vertIn.close();
    fragIn.close();
    const char* vertCString = vertCode.c_str();
    const char* fragCString = fragCode.c_str();

    unsigned int vert, frag;

    vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vertCString, nullptr);
    glCompileShader(vert);
    checkErrors(vert, "SHADER");

    frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fragCString, nullptr);
    glCompileShader(frag);
    checkErrors(frag, "SHADER");


    programId = glCreateProgram();
    glAttachShader(programId, vert);
    glAttachShader(programId, frag);
    glLinkProgram(programId);
    checkErrors(programId, "PROGRAM");

    glDeleteShader(vert);
    glDeleteShader(frag);
}

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath, const std::string& geometryPath) {
    std::string vertCode;
    std::string fragCode;
    std::string geomCode;

    std::ifstream vertIn ;
    std::ifstream fragIn;
    std::ifstream geomIn;
    vertIn.exceptions(std::ifstream::badbit);
    fragIn.exceptions(std::ifstream::badbit);
    geomIn.exceptions(std::ifstream::badbit);

    try {
        vertIn.open(vertexPath);
        fragIn.open(fragmentPath);
        geomIn.open(geometryPath);

        std::string line;
        while (std::getline(vertIn, line)) {
            vertCode += line + "\n";
        }
        while (std::getline(fragIn, line)) {
            fragCode += line + "\n";
        }
        while (std::getline(geomIn, line)) {
            geomCode += line + "\n";
        }
    } catch (const std::ifstream::failure& e) {
        EXIT_WITH_ERROR(e.what())
    }

    vertIn.close();
    fragIn.close();
    geomIn.close();
    const char* vertCString = vertCode.c_str();
    const char* fragCString = fragCode.c_str();
    const char* geomCString = geomCode.c_str();

    unsigned int vert, frag, geom;

    vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vertCString, nullptr);
    glCompileShader(vert);
    checkErrors(vert, "VERTEX");

    frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fragCString, nullptr);
    glCompileShader(frag);
    checkErrors(frag, "FRAGMENT");

    geom = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geom, 1, &geomCString, nullptr);
    glCompileShader(geom);
    checkErrors(geom, "GEOMETRY");

    programId = glCreateProgram();
    glAttachShader(programId, vert);
    glAttachShader(programId, frag);
    glAttachShader(programId, geom);
    glLinkProgram(programId);
    checkErrors(programId, "PROGRAM");

    glDeleteShader(vert);
    glDeleteShader(frag);
    glDeleteShader(geom);
}

Shader::~Shader() {
    glDeleteProgram(programId);
}

void Shader::use() const {
    glUseProgram(programId);
}

void Shader::setBool(const std::string &name, bool value) {
    glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
}

void Shader::setInt(const std::string &name, int value) {
    glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) {
    glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &vec) {
    glUniform3f(glGetUniformLocation(programId, name.c_str()), vec.x, vec.y, vec.z);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) {
    glUniformMatrix4fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::checkErrors(unsigned int id, const std::string &type) const {
    int isCompiled;
    int maxLength;

    if (type == "PROGRAM") {
        glGetProgramiv(id, GL_LINK_STATUS, &isCompiled);
        if (!isCompiled) {
            glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);
            char* infoLog = new char[maxLength];
            glGetProgramInfoLog(id, maxLength, &maxLength, infoLog);
            EXIT_WITH_ERROR(type + " ERROR: " + infoLog);
        }
    } else {
        glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
        if (!isCompiled) {
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
            char* infoLog = new char[maxLength];
            glGetShaderInfoLog(id, maxLength, &maxLength, infoLog);
            EXIT_WITH_ERROR(type + " ERROR: " + infoLog);
        }
    }
}
