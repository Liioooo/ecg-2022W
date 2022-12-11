//
// Created by preis on 06/11/2022.
//
#ifndef ECG_SOLUTION_BOX_H
#define ECG_SOLUTION_BOX_H

#include "DrawableMesh.h"
#include "Material.h"

class Box : public DrawableMesh {
public:
    Box(Shader* shader, Material* material, float width, float height, float depth) :
    DrawableMesh(shader, material), width(width), height(height), depth(depth) {}

protected:
    void generateMesh() override {

        // Front Face
        vertices.emplace_back(-0.5f * width, 0.5f * height, 0.5f * depth, 0.0f,  0.0f,  1.0f); // left_top_front
        vertices.emplace_back(-0.5f * width,  -0.5f * height, 0.5f * depth, 0.0f,  0.0f,  1.0f); // left_bottom_front
        vertices.emplace_back(0.5f * width,  0.5f * height, 0.5f * depth, 0.0f,  0.0f,  1.0f); // right_top_front
        vertices.emplace_back(0.5f * width, -0.5f * height, 0.5f * depth, 0.0f,  0.0f,  1.0f); // right_bottom_front

        // Right Face
        vertices.emplace_back(0.5f * width,  0.5f * height, 0.5f * depth, 1.0f,  0.0f,  0.0f); // right_top_front
        vertices.emplace_back(0.5f * width, -0.5f * height, 0.5f * depth, 1.0f,  0.0f,  0.0f); // right_bottom_front
        vertices.emplace_back(0.5f * width, 0.5f * height, -0.5f * depth, 1.0f,  0.0f,  0.0f); // right_top_back
        vertices.emplace_back(0.5f * width, -0.5f * height, -0.5f * depth, 1.0f,  0.0f,  0.0f); // right_bottom_back

        // Left Face
        vertices.emplace_back(-0.5f * width, 0.5f * height, 0.5f * depth, -1.0f,  0.0f,  0.0f); // left_top_front
        vertices.emplace_back(-0.5f * width,  -0.5f * height, 0.5f * depth, -1.0f,  0.0f,  0.0f); // left_bottom_front
        vertices.emplace_back(-0.5f * width, 0.5f * height, -0.5f * depth, -1.0f,  0.0f,  0.0f); // left_top_back
        vertices.emplace_back(-0.5f * width, -0.5f * height, -0.5f * depth, -1.0f,  0.0f,  0.0f); // left_bottom_back

        // Back Face
        vertices.emplace_back(0.5f * width, 0.5f * height, -0.5f * depth, 0.0f,  0.0f,  -1.0f); // right_top_back
        vertices.emplace_back(0.5f * width, -0.5f * height, -0.5f * depth, 0.0f,  0.0f,  -1.0f); // right_bottom_back
        vertices.emplace_back(-0.5f * width, 0.5f * height, -0.5f * depth, 0.0f,  0.0f,  -1.0f); // left_top_back
        vertices.emplace_back(-0.5f * width, -0.5f * height, -0.5f * depth, 0.0f,  0.0f,  -1.0f); // left_bottom_back

        // Top Face
        vertices.emplace_back(0.5f * width,  0.5f * height, 0.5f * depth, 0.0f,  1.0f,  0.0f); // right_top_front
        vertices.emplace_back(-0.5f * width, 0.5f * height, 0.5f * depth, 0.0f,  1.0f,  0.0f); // left_top_front
        vertices.emplace_back(0.5f * width, 0.5f * height, -0.5f * depth, 0.0f,  1.0f,  0.0f); // right_top_back
        vertices.emplace_back(-0.5f * width, 0.5f * height, -0.5f * depth, 0.0f,  1.0f,  0.0f); // left_top_back

        // Bottom Face
        vertices.emplace_back(0.5f * width, -0.5f * height, 0.5f * depth, 0.0f,  -1.0f,  0.0f); // right_bottom_front
        vertices.emplace_back(-0.5f * width,  -0.5f * height, 0.5f * depth, 0.0f,  -1.0f,  0.0f); // left_bottom_front
        vertices.emplace_back(0.5f * width, -0.5f * height, -0.5f * depth, 0.0f,  -1.0f,  0.0f); // right_bottom_back
        vertices.emplace_back(-0.5f * width, -0.5f * height, -0.5f * depth, 0.0f,  -1.0f,  0.0f); // left_bottom_back

        // front
        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);

        indices.push_back(2);
        indices.push_back(1);
        indices.push_back(3);

        // right
        indices.push_back(5);
        indices.push_back(7);
        indices.push_back(6);

        indices.push_back(4);
        indices.push_back(5);
        indices.push_back(6);

        // left
        indices.push_back(9);
        indices.push_back(8);
        indices.push_back(11);

        indices.push_back(8);
        indices.push_back(10);
        indices.push_back(11);

        // back
        indices.push_back(13);
        indices.push_back(15);
        indices.push_back(12);

        indices.push_back(14);
        indices.push_back(12);
        indices.push_back(15);

        // top
        indices.push_back(17);
        indices.push_back(16);
        indices.push_back(18);

        indices.push_back(17);
        indices.push_back(18);
        indices.push_back(19);

        // bottom
        indices.push_back(21);
        indices.push_back(22);
        indices.push_back(20);

        indices.push_back(22);
        indices.push_back(21);
        indices.push_back(23);
    }

private:
    float width;
    float height;
    float depth;
};

#endif // ECG_SOLUTION_BOX_H
