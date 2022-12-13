//
// Created by preis on 06/11/2022.
//
#ifndef ECG_SOLUTION_DRAWABLEMESH_H
#define ECG_SOLUTION_DRAWABLEMESH_H

#include "Drawable.h"

struct Vertex {
    float position[3];
    float normal[3];

    Vertex(float pX, float pY, float pZ, float nX, float nY, float nZ)
    : position{pX, pY, pZ}, normal{nX, nY, nZ} {};
};

class DrawableMesh : public Drawable {
public:
    explicit DrawableMesh(Shader* shader, Material* material) : Drawable(shader, material) {}
    ~DrawableMesh();

    /**
     * Calls generateMesh() and must be called before drawing the Drawable
     */
    void init();
    void draw() override;
    void drawDebug(Shader* shader) override;

protected:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    virtual void preDraw() {};
    virtual void generateMesh() = 0;

private:
    GLuint vao{};
};

#endif // ECG_SOLUTION_DRAWABLEMESH_H
