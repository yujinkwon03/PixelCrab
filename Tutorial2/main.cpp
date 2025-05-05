#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 1200;
vec3 MousePos = vec3(NULL);

#include "input_manager.cpp"
#include "GeneratePixelCrabs.cpp"

int main() {
	glfwInit();

	// specifies contect and version (specifically for tutorial)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creating Window Object
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "learnOpenGl", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Pass GLAD (handles fundtion pointers for OPENGL) function to load adress of OPENGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to intialize GLAD" << std::endl;
		return -1;
	}

	// Registering callback function to resizes Viewport when window is resized
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);

	const char* VertexShaderPath = "rectCrabVertexShader.vert";
	const char* FragShaderPath = "rectCrabFragShader.frag";
	generateRectCrabs(window, VertexShaderPath, FragShaderPath);

	glfwTerminate();
	return 0;

}