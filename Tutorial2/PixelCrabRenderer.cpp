#include "PixelCrabRenderer.h"


PixelCrabRenderer::PixelCrabRenderer(float scale, float xTransform, float yTransform)
{
    std::random_device rd;  // Seed
    std::mt19937 gen(rd()); // Mersenne Twister engine

    if(scale == NULL) {
        // Create a random number
        std::uniform_real_distribution<> dis(0.0, 0.15); // Range [0, 1)
        scale = dis(gen);
    }
    if(xTransform == NULL) {
        // Create a random number
        std::uniform_real_distribution<> dis(-1.0 + scale, 1.0 - scale); // Range [0, 1)
        xTransform = dis(gen);
    }
    if (yTransform == NULL) {
        // Create a random number
        std::uniform_real_distribution<> dis(-1.0 + scale, 1.0 - scale); // Range [0, 1)
        yTransform = dis(gen);
    }
    CrabScale = scale;
    processImap(CrabImap);
    generatePixelObject(scale, xTransform, yTransform);
    
    PixelSize = scale / (getXDim() / 2);
    CrabXCoor = {xTransform - (PixelSize * (getXDim() / 2)), xTransform + (PixelSize * (getXDim() / 2)) };
    CrabOriginalPos = {xTransform, yTransform};
    CrabCurrentPos = { xTransform, yTransform };
}


void PixelCrabRenderer::drawCrabBody() {
    for (int i = 0; i < CrabBodyIndices.size(); i++) {
        glBindVertexArray(VAOs[CrabBodyIndices[i]]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

void PixelCrabRenderer::drawCrabEyes() {
    for (int i = 0; i < CrabEyesIndices.size(); i++) {
        glBindVertexArray(VAOs[CrabEyesIndices[i]]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

void PixelCrabRenderer::drawCrabLegs() {
    for (int i = 0; i < CrabLegsIndices.size(); i++) {
        glBindVertexArray(VAOs[CrabLegsIndices[i]]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

void PixelCrabRenderer::drawCrabMovingLegs() {

    for (int i = 0; i < CrabMovingLegsIndices.size(); i++) {
        glBindVertexArray(VAOs[CrabMovingLegsIndices[i]]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

void PixelCrabRenderer::drawCrabStillLegs() {
    vector<int> stillLegsIndices;
    set_difference(CrabLegsIndices.begin(), CrabLegsIndices.end(), CrabMovingLegsIndices.begin(), CrabMovingLegsIndices.end(), back_inserter(stillLegsIndices));
    for (int i = 0; i < stillLegsIndices.size(); i++) {
        glBindVertexArray(VAOs[stillLegsIndices[i]]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

float PixelCrabRenderer::moveCrab(float currentTime, float lastToggleTime, float crabSpeed, float walkingSpace) {
    if (currentTime - lastToggleTime >= crabSpeed) {
        // Toggle the isMoving flag
        float crabWalkTranslation = PixelSize;
        if (CrabXCoor[1] >= CrabOriginalPos[0] +  walkingSpace / 2 || CrabXCoor[1] >= 1.0 || CrabXCoor[0] <= CrabOriginalPos[0] - (walkingSpace / 2) || CrabXCoor[0] <= -1.0) MoveRight = !MoveRight;
        if (!MoveRight) crabWalkTranslation *= -1;
        WalkingPhase = !WalkingPhase;
        for (size_t i = 0; i < CrabXCoor.size(); i++)
        {
            CrabXCoor[i] += crabWalkTranslation;
        }
        CrabCurrentPos[0] += crabWalkTranslation;
        Trans = glm::translate(Trans, glm::vec3(crabWalkTranslation, 0.0f, 0.0f));
        // Update the last toggle time
        lastToggleTime = currentTime;
    }
    return lastToggleTime;
}

void PixelCrabRenderer::deallocResources() {
    for (int i = 0; i < VAOs.size(); i++) {
        glDeleteVertexArrays(1, &VAOs[i]);
        glDeleteBuffers(1, &VBOs[i]);
        glDeleteBuffers(1, &EBOs[i]);
    }
}

int PixelCrabRenderer::getPixelCount() const { return PixelCount; }

bool PixelCrabRenderer::getWalkingPhase() const { return WalkingPhase; }

bool PixelCrabRenderer::getIsMoving() const { return IsMoving; }

float PixelCrabRenderer::getPixelSize() const { return PixelSize; }

float PixelCrabRenderer::getXDim() const { return XCenter * 2; }

float PixelCrabRenderer::getYDim() const { return YCenter * 2; }

glm::mat4 PixelCrabRenderer::getTransformation() const {return Trans;}

const vector<unsigned int>& PixelCrabRenderer::getEBOs() const { return EBOs; }

const vector<unsigned int>& PixelCrabRenderer::getVBOs() const { return VBOs; }

const vector<unsigned int>& PixelCrabRenderer::getVAOs() const { return VAOs; }

const vector<int>& PixelCrabRenderer::getCrabBodyIndices() const { return CrabBodyIndices; }

const vector<int>& PixelCrabRenderer::getCrabEyesIndices() const { return CrabEyesIndices; }

const vector<int>& PixelCrabRenderer::getCrabLegsIndices() const { return CrabLegsIndices; }

void PixelCrabRenderer::processImap(const vector<vector<int>>& iMap)
{
    int pixelCount = 0;
    int maxRow = 0;
    int maxCol = 0;

    int rows = (int)iMap.size();
    int cols = (int)iMap[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (iMap[i][j] == 0) continue;
            pixelCount++;
            // find 'width' of Imap
            if (j > maxCol) maxCol = j;
        }
        // find 'height' of Imap
        if (i > maxRow) maxRow = i;
    }

    float xCenter = ((float)maxCol + 1) / 2;
    float yCenter = ((float)maxRow + 1) / 2;

    PixelCount = pixelCount;
    XCenter = xCenter;
    YCenter = yCenter;
}

void PixelCrabRenderer::initializePixel(int row, int col, float xTransform, float yTransform, float scale, unsigned int& EBO, unsigned int& VBO, unsigned int& VAO)
{
    float yCoordiante = -row;
    float yCenterCoordinate = -YCenter;
    float crabSize = XCenter;

    // This is getting mirrored so that it translates correctly
    float topRightVertexX = ((float)col - XCenter + 1) / crabSize;
    float topRightVertexY = (yCoordiante - yCenterCoordinate) / crabSize;
    float bottomRightVertexX = topRightVertexX;
    float bottomRightVertexY = (yCoordiante - yCenterCoordinate - 1) / crabSize;
    float bottomLeftVertexX = ((float)col - XCenter) / crabSize;
    float bottomLeftVertexY = bottomRightVertexY;
    float topLeftVertexX = bottomLeftVertexX;
    float topLeftVertexY = topRightVertexY;

    float vertices[] = {
        topRightVertexX, topRightVertexY, 0,
        bottomRightVertexX, bottomRightVertexY, 0,
        bottomLeftVertexX, bottomLeftVertexY, 0,
        topLeftVertexX, topLeftVertexY, 0
    };

    float transformation[]{
        xTransform, yTransform, 0,
        xTransform, yTransform, 0,
        xTransform, yTransform, 0,
        xTransform, yTransform, 0
    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    scaleArr(scale, sizeof(vertices) / sizeof(vertices[0]), vertices);
    // Apply transformation
    for (int i = 0; i < sizeof(vertices) / sizeof(vertices[0]); ++i) {
        vertices[i] += transformation[i];
    }
    generatePixelBuffers(EBO, VBO, VAO, vertices, indices, sizeof(vertices) / sizeof(vertices[0]), sizeof(indices) / sizeof(indices[0]));
}

void PixelCrabRenderer::generatePixelObject(float scale, float xTransform, float yTransform)
{
    vector<vector<int>>& iMap = CrabImap;

    EBOs.resize(PixelCount);
    VBOs.resize(PixelCount);
    VAOs.resize(PixelCount);

    int rows = (int)iMap.size();
    int cols = (int)iMap[0].size();
    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (iMap[i][j] == 0) continue;
            if (index == PixelCount) break;

            if (iMap[i][j] == 1) CrabBodyIndices.push_back(index);
            if (iMap[i][j] == 2) CrabEyesIndices.push_back(index);
            if (iMap[i][j] == 3) {
                CrabLegsIndices.push_back(index);
                if (i == rows - 1) {
                    CrabMovingLegsIndices.push_back(index);
                }
            }


            initializePixel(i, j, xTransform, yTransform, scale, EBOs[index], VBOs[index], VAOs[index]);
            index++;
        }
    }
}

void PixelCrabRenderer::scaleArr(float scale, int numVertices, float verticesArr[])
{
    for (int i = 0; i < numVertices; i++) {
        verticesArr[i] *= scale;
    }
}

void PixelCrabRenderer::generatePixelBuffers(unsigned int& EBO, unsigned int& VBO, unsigned int& VAO, float vertices[], unsigned int indices[], size_t vertexCount, size_t indexCount)
{
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a vertex buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);
    // 3. copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    // 4. then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void PixelCrabRenderer::printVertices(float vertices[], int array_size)
{
    int n = array_size / sizeof(vertices[0]);
    for (int i = 0; i < n; i++)
        std::cout << vertices[i] << " ";
    std::cout << std::endl;
}
