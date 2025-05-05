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

using namespace std;

class PixelCrabRenderer {
public:
    // Constructor to initialize the renderer
    PixelCrabRenderer(float scale = NULL, float xTransformation = NULL, float yTransformation = NULL);

    void drawCrabBody();
    void drawCrabEyes();
    void drawCrabLegs();
    void drawCrabStillLegs();
    void drawCrabMovingLegs();

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

    glm::mat4 getTransformation() const;
    vector<float> CrabCurrentPos;

    // Get the EBO, VBO, VAO vectors
    const vector<unsigned int>& getEBOs() const;
    const vector<unsigned int>& getVBOs() const;
    const vector<unsigned int>& getVAOs() const;

    const vector<int>& getCrabBodyIndices() const;
    const vector<int>& getCrabEyesIndices() const;
    const vector<int>& getCrabLegsIndices() const;

    glm::mat4 Trans = glm::mat4(1.0f);

    vector<float> CrabXCoor;
    vector<float> CrabOriginalPos;

private:
    // Data members
    int PixelCount;
    float XCenter;
    float YCenter;
    float CrabScale; 
    float PixelSize;

    bool IsMoving = true;
    bool MoveRight = true;
    bool WalkingPhase = 0;

    vector<unsigned int> EBOs;
    vector<unsigned int> VBOs;
    vector<unsigned int> VAOs;

    vector<int> CrabBodyIndices;
    vector<int> CrabEyesIndices;
    vector<int> CrabLegsIndices;
    vector<int> CrabMovingLegsIndices;

    vector<vector<int>> CrabImap =
    {
        {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 2, 0, 0, 2, 0, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 3, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 3, 0, 0},
        {0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0},
        {0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0}
    };
   
    // changes crab stance
    void changeWalkingStance();

    // Process the iMap and calculate the necessary data
    void processImap(const vector<vector<int>>& iMap);

    // Initialize a single pixel's buffers
    void initializePixel(int row, int col, float xTransform, float yTransform, float scale, unsigned int& EBO, unsigned int& VBO, unsigned int& VAO);

    // Generate the pixel buffers for all pixels
    void generatePixelObject(float scale, float xTransform, float yTransform);

    // Scale vertices array by a factor
    void scaleArr(float scale, int numVertices, float verticesArr[]);

    // Generate the pixel buffers for OpenGL
    void generatePixelBuffers(unsigned int& EBO, unsigned int& VBO, unsigned int& VAO, float vertices[], unsigned int indices[], size_t vertexCount, size_t indexCount);

    // Debug print for vertices
    void printVertices(float vertices[], int array_size);
};
