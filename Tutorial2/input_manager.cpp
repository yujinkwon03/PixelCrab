
// Processes inputs from user 
void processInput(GLFWwindow* window)
{
	// if user pressed esc key then close window 
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	MousePos.x = 2.f * (xpos - float(width) / 2.f) / float(width);
	MousePos.y = 2.f * (-ypos + float(height) / 2.f) / float(height);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}