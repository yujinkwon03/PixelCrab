#include "RectCrabRenderer.h"
const float null = -100.0f;


RectCrabRenderer::RectCrabRenderer(float scale, float xTransform, float yTransform)
{
    std::random_device rd;  // Seed
    std::mt19937 gen(rd()); // Mersenne Twister engine

    if (scale == NULL) {
        // Create a random number
        std::uniform_real_distribution<> dis(0.15f, 0.25f); // Range [0, 1)
        scale = float(dis(gen));
    }
    if (xTransform == NULL) {
        // Create a random number
        std::uniform_real_distribution<> dis(-1.0f + scale, 1.0f - scale); // Range [0, 1)
        xTransform = float(dis(gen));
    }
    if (yTransform == NULL) {
        // Create a random number
        std::uniform_real_distribution<> dis(-1.0f + scale, 1.0f - scale); // Range [0, 1)
        yTransform = float(dis(gen));
    }

    XDim = scale;
    YDim = scale * (12.f/18.f);
    CrabScale = scale;
    generateRectangle(scale, xTransform, yTransform);

    PixelSize = scale / 18.0f;
    CrabOriginalPos =  vec3( xTransform, yTransform, 0 );
    CrabCurrentPos = vec3(xTransform, yTransform, 0);
    std::uniform_real_distribution<> dis(0, 1);
    MoveRight = std::round(dis(gen));
}

void RectCrabRenderer::drawCrab() {
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glBindVertexArray(VAO);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


int RectCrabRenderer::getCrabFrame() 
{ 
    if (WalkingPhase) {
        CrabFrame = 1;
    }
    else CrabFrame = 0;
    return CrabFrame; 
}

void RectCrabRenderer::deallocResources() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
}

int RectCrabRenderer::getPixelCount() const { return PixelCount; }

bool RectCrabRenderer::getWalkingPhase() const { return WalkingPhase; }

bool RectCrabRenderer::getIsMoving() const { return IsMoving; }

float RectCrabRenderer::getPixelSize() const { return PixelSize; }

float RectCrabRenderer::getXDim() const { return XDim; }

float RectCrabRenderer::getYDim() const { return YDim; }

glm::mat4 RectCrabRenderer::getTransformation() const { return Trans; }

const unsigned int& RectCrabRenderer::getEBO() const { return EBO; }

const unsigned int& RectCrabRenderer::getVBO() const { return VBO; }

const unsigned int& RectCrabRenderer::getVAO() const { return VAO; }


void RectCrabRenderer::generateRectangle(float scale, float xTransform, float yTransform)
{
    // Generate rectangle (using scale) 
    float topRightVertexX = (xTransform + XDim);
    float topRightVertexY = (yTransform + YDim);
    float bottomRightVertexX = topRightVertexX;
    float bottomRightVertexY = (yTransform - YDim);
    float bottomLeftVertexX = (xTransform - XDim);
    float bottomLeftVertexY = bottomRightVertexY;
    float topLeftVertexX = bottomLeftVertexX;
    float topLeftVertexY = topRightVertexY;

    vector<float> vertices = {
        // positions                                    // colors           // texture coords
       topRightVertexX,  topRightVertexY, 0.0f,         1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
       bottomRightVertexX, bottomRightVertexY, 0.0f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
       bottomLeftVertexX,  bottomLeftVertexY, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
       topLeftVertexX,  topLeftVertexY, 0.0f,           1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };

    size_t verticesSize = vertices.size();

    for (size_t i = 0; i < verticesSize; ++i) {
        Vertices[i] = vertices[i];  // Copy each element
        std::cout << Vertices[i] << endl;
    }


    unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
    };

    generatePixelBuffers(EBO, VBO, VAO, Vertices, indices, sizeof(Vertices) / sizeof(Vertices[0]), sizeof(indices) / sizeof(indices[0]));
}

void RectCrabRenderer::scaleArr(float scale, int numVertices, float verticesArr[])
{
    for (int i = 0; i < numVertices; i++) {
        verticesArr[i] *= scale;
    }
}

void RectCrabRenderer::generatePixelBuffers(unsigned int& EBO, unsigned int& VBO, unsigned int& VAO, float vertices[], unsigned int indices[], size_t vertexCount, size_t indexCount)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    

    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a vertex buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_DYNAMIC_DRAW);
    // 3. copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    // 4. then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenTextures(1, &Texture);
    glBindTexture(GL_TEXTURE_2D, Texture);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    float borderColor[] = { 1.0f, 0.0f, 0.0f, 0.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load("C:\\Users\\kwony\\OneDrive\\Desktop\\crab.png", &width, &height, &nrChannels, 0);
    if (data){
    
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void RectCrabRenderer::printVertices(float vertices[], int array_size)
{
    int n = array_size / sizeof(vertices[0]);
    for (int i = 0; i < n; i++)
        std::cout << vertices[i] << " ";
    std::cout << std::endl;
}
