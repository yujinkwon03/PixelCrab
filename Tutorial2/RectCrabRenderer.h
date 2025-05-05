#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iterator>
#include <random>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;
#include "stb_image.h"

using namespace std;

class RectCrabRenderer {
public:
    // Constructor to initialize the renderer
    RectCrabRenderer(float scale = NULL, float xTransformation = NULL, float yTransformation = NULL);

    void drawCrab();

    float moveCrab(float currentTime, float lastToggleTime, float crabSpeed, float walkingSpace);

    // Function to deallocate all resources
    void deallocResources();

    // Function to get the total pixel count
    int getPixelCount() const;

    // Function to get the XCenter of the image
    float getXDim() const;

    // Function to get the YCenter of the image
    float getYDim() const;

    float getPixelSize() const;

    bool getWalkingPhase() const;

    bool getIsMoving() const;

    int getCrabFrame();

    glm::mat4 getTransformation() const;

    // Get the EBO, VBO, VAO vectors
    const unsigned int& getEBO() const;
    const unsigned int& getVBO() const;
    const unsigned int& getVAO() const;

    glm::mat4 Trans = glm::mat4(1.0f);

    vec3 CrabCurrentPos;
    vec3 CrabOriginalPos;
    unsigned int Texture;

    // Data members
    int PixelCount;
    int CrabFrame = 0;

    float XDim;
    float YDim;
    float CrabScale;
    float PixelSize;
    float LastToggleTime;
    float CrabSpeed;

    bool IsMoving = true;
    bool MoveRight = true;
    bool WalkingPhase = 0;


private:

    unsigned int EBO;
    unsigned int VBO;
    unsigned int VAO;

    float Vertices[36];

    // Generate the pixel buffers for all pixels
    void generateRectangle(float scale, float xTransform, float yTransform);

    // Walk crab side-to-side
    void sideWalkCrab();

    // Scale vertices array by a factor
    void scaleArr(float scale, int numVertices, float verticesArr[]);

    // Generate the pixel buffers for OpenGL
    void generatePixelBuffers(unsigned int& EBO, unsigned int& VBO, unsigned int& VAO, float vertices[], unsigned int indices[], size_t vertexCount, size_t indexCount);

    // Debug print for vertices
    void printVertices(float vertices[], int array_size);
};
