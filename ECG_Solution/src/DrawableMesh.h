//
// Created by preis on 06/11/2022.
//
#ifndef ECG_SOLUTION_DRAWABLEMESH_H
#define ECG_SOLUTION_DRAWABLEMESH_H

#include "Drawable.h"

class DrawableMesh : public Drawable {
public:
    explicit DrawableMesh(Shader* shader) : Drawable(shader) {}
    ~DrawableMesh();

    /**
     * Calls generateMesh() and must be called before drawing the Drawable
     */
    void init();

protected:
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;

    void drawMesh() const;
    virtual void generateMesh() = 0;

private:
    GLuint vao{};
};

#endif // ECG_SOLUTION_DRAWABLEMESH_H
