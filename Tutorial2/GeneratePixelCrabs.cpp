#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <random>
#include <cmath>

//#include "PixelCrabRenderer.h"
#include "RectCrabRenderer.h"
#include "Shader.h"

void moveCrab(RectCrabRenderer& crab, float currentTime, int crabIndex);
void sideWalkCrab(RectCrabRenderer& crab);
vec3 repelObject(vec3 obj1Position, vec3 obj2Position, float defaultStepSize);

vector<RectCrabRenderer> pixelCrabList;

//// Generate	crabs where each pixel is a VAO (the vertices of the crab are defined)
//int generatePixelCrabs(GLFWwindow* window, const char* VertexShaderPath, const char* FragShaderPath)
//{
//
//	Shader basicCrabBodyShader(VertexShaderPath, FragShaderPath);
//
//	vector<float> lastToggleTime;
//	vector<float> crabSpeed;
//
//	float colorToggleTime = 0;
//	float redValue = 0;
//	int numCrabs = 40;
//
//	vector<PixelCrabRenderer> pixelCrabList;
//	for (int i = 0; i < numCrabs; i++) {
//		pixelCrabList.push_back(PixelCrabRenderer());
//		lastToggleTime.push_back(0.0);
//		std::random_device rd;  // Seed
//		std::mt19937 gen(rd()); // Mersenne Twister engine
//		std::uniform_real_distribution<> dis(0.02, 0.6); // Range [0, 1)
//		crabSpeed.push_back(dis(gen));
//	}
//
//	// Create a random number generator
//	std::random_device rd;  // Seed
//	std::mt19937 gen(rd()); // Mersenne Twister engine
//
//	while (!glfwWindowShouldClose(window))
//	{
//		// Input handling 
//		processInput(window);
//
//		// Entire color buffer filled with color configured in glClearColor
//		glClearColor(.2f, 0.5f, 0.5f, 1.0f); // specify color to clear screen with 
//		//glClearColor(0.1f, 0.3f, 0.3f, 1.0f); // specify color to clear screen with 
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// update uniform color 
//		float timeValue = glfwGetTime();
//		float greenValue = sin(timeValue) / 2.0 + 0.5f;
//
//		// Assigning uniforms 
//		int vertexColorLocation = glGetUniformLocation(basicCrabBodyShader.ID, "ourColor");
//
//
//
//
//		for (int i = 0; i < pixelCrabList.size(); i++) {
//
//
//			int shaderNum = i % 7;
//			//int shaderNum = 0;
//			PixelCrabRenderer& pixelcrab = pixelCrabList[i];
//
//			lastToggleTime[i] = pixelcrab.moveCrab(timeValue, lastToggleTime[i], crabSpeed[i], 4.0);
//			basicCrabBodyShader.setFloat("crabPixelSize", pixelcrab.getPixelSize());
//			basicCrabBodyShader.setInt("crabType", shaderNum);
//			basicCrabBodyShader.setBool("walkingPhase", pixelcrab.getWalkingPhase());
//			int crabCenterPosLocation = glGetUniformLocation(basicCrabBodyShader.ID, "centerPos");
//			glUniform2f(crabCenterPosLocation, pixelcrab.CrabOriginalPos[0], pixelcrab.CrabOriginalPos[1]);
//
//			glm::mat4 trans = pixelcrab.getTransformation();
//			unsigned int transformLoc = glGetUniformLocation(basicCrabBodyShader.ID, "transform");
//			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
//
//			// update uniform color 
//			timeValue = glfwGetTime();
//			if (shaderNum == 3) {
//				if (timeValue - colorToggleTime >= 0.6)
//				{
//					std::uniform_real_distribution<> dis(0.0, 1.0); // Range [0, 1)
//					float random_number = dis(gen);
//					colorToggleTime = timeValue;
//					redValue = random_number;
//					std::cout << redValue << endl;
//				}
//				glUniform4f(vertexColorLocation, redValue, 0.0f, 0.0f, 1.0f);
//			}
//			else
//			{
//				greenValue = sin(timeValue * i) / 2.0 + 0.5f;
//				glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
//			}
//
//			basicCrabBodyShader.setBool("isMoving", pixelcrab.getIsMoving());
//		}
//
//		// Check and call events + swap buffers
//		glfwSwapBuffers(window);
//		glfwPollEvents(); //checks if any events are triggered + calls
//	}
//
//	//deallocate all resources
//	for (int i = 0; i < pixelCrabList.size(); i++) {
//		PixelCrabRenderer pixelcrab = pixelCrabList[i];
//		pixelcrab.deallocResources();
//	}
//
//	return 0;
//}

int generateRectCrabs(GLFWwindow* window, const char* VertexShaderPath, const char* FragShaderPath)
{

	Shader basicCrabBodyShader(VertexShaderPath, FragShaderPath);

	vector<float> lastToggleTime;
	vector<float> crabSpeed;

	float colorToggleTime = 0;
	float redValue = 0;
	int numCrabs = 30;

	for (int i = 0; i < numCrabs; i++) {
		pixelCrabList.push_back(RectCrabRenderer(0.1f));
		lastToggleTime.push_back(0.0f);
		std::random_device rd;  // Seed
		std::mt19937 gen(rd()); // Mersenne Twister engine
		std::uniform_real_distribution<> dis(0.08f, 0.6f); // Range [0, 1)
		pixelCrabList[i].CrabSpeed = float(dis(gen));
	}

	pixelCrabList[0].CrabSpeed = 0.3f;

	// Create a random number generator
	std::random_device rd;  // Seed
	std::mt19937 gen(rd()); // Mersenne Twister engine

	glUniform1i(glGetUniformLocation(basicCrabBodyShader.ID, "crabTexture"), 0);

	while (!glfwWindowShouldClose(window))
	{
		// Input handling 
		processInput(window);

		cout << MousePos.y << endl;

		// Entire color buffer filled with color configured in glClearColor
		glClearColor(.2f, 0.5f, 0.5f, 1.0f); // specify color to clear screen with 
		//glClearColor(0.1f, 0.3f, 0.3f, 1.0f); // specify color to clear screen with 
		glClear(GL_COLOR_BUFFER_BIT);

		// update uniform color 
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0 + 0.5f;

		// Assigning uniforms 
		//int vertexColorLocation = glGetUniformLocation(basicCrabBodyShader.ID, "ourColor");
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, pixelCrabList[0].Texture);


		for (int i = 0; i < pixelCrabList.size(); i++) {

			RectCrabRenderer &pixelcrab = pixelCrabList[i];

			timeValue = glfwGetTime();
			moveCrab(pixelcrab, timeValue, i);
			basicCrabBodyShader.setInt("crabFrame", pixelcrab.getCrabFrame());


			glm::mat4 trans = pixelcrab.getTransformation();
			unsigned int transformLoc = glGetUniformLocation(basicCrabBodyShader.ID, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

			basicCrabBodyShader.use();
			pixelcrab.drawCrab();
		}

		// Check and call events + swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents(); //checks if any events are triggered + calls
	}

	//deallocate all resources
	for (int i = 0; i < pixelCrabList.size(); i++) 
	{
	RectCrabRenderer pixelcrab = pixelCrabList[i];
		pixelcrab.deallocResources();
	}

	return 0;
}


//REFACTOR THIS CODE
void moveCrab(RectCrabRenderer &crab, float currentTime, int crabIndex)
{
	vector<vec3> pixelCrabTranforms;

	if (currentTime - crab.LastToggleTime >= crab.CrabSpeed) 
	{
		// cohesion; crabs are attracted to mouse, update transform accordingly 

		vec3 crabTransform = vec3(0.f, 0.f, 0.f);
		int neighborCount = 0;

		for (int i = 0; i < pixelCrabList.size(); i++) {
			if (i == crabIndex) continue;

			float crabDist = distance(crab.CrabCurrentPos, pixelCrabList[i].CrabCurrentPos);

			/*if (crabDist <= 24*crab.PixelSize)
			{
				vec3 crabDisp = repelObject(crab.CrabCurrentPos, pixelCrabList[i].CrabCurrentPos, crab.PixelSize);
				crabTransform += crabDisp;
				neighborCount++;
			}*/

		}

		if (neighborCount != 0) 
		{
			crabTransform /= neighborCount; 
			crabTransform = normalize(crabTransform);
			crabTransform *= 0.008;
			crab.CrabCurrentPos += crabTransform;
			crab.Trans = translate(crab.Trans, crabTransform);
			if (crabTransform.x < 1) crab.MoveRight = false;
			else crab.MoveRight = true;
		}

		bool nearCursor = false;
		float mouseDist = distance(MousePos, crab.CrabCurrentPos);
		if (mouseDist < crab.PixelSize * 30) nearCursor = true;

		if (nearCursor) 
		{
			vec3 crabTransformation = MousePos - crab.CrabCurrentPos;
			crabTransformation = normalize(crabTransformation);
			crabTransformation *= 50 * crab.PixelSize * pow(mouseDist, 2.0);
			crab.CrabCurrentPos += crabTransformation;
			crab.Trans = translate(crab.Trans, crabTransformation);
			crab.WalkingPhase = !crab.WalkingPhase;

			//cout << "here" << endl;
		}
		else 
		{
			float crabDisp = distance(crab.CrabOriginalPos, crab.CrabCurrentPos);
			if (crabDisp > crab.PixelSize * 4) 
			{
				vec3 crabTransformation = crab.CrabOriginalPos - crab.CrabCurrentPos;
				crabTransformation = normalize(crabTransformation);
				crabTransformation *= crab.PixelSize;
				crab.CrabCurrentPos += crabTransformation;
				crab.Trans = translate(crab.Trans, crabTransformation);
				crab.WalkingPhase = !crab.WalkingPhase;
			}
			else {
				sideWalkCrab(crab);

			}
		}

		crab.LastToggleTime = currentTime;
	}
}

vec3 repelObject(vec3 obj1Position, vec3 obj2Position, float defaultStepSize) {
	// repel obj1 from obj2 
	vec3 obj1Transform = vec3(0.f, 0.f, 0.f);
	obj1Transform -= obj1Position - obj2Position; 
	obj1Transform *= -1;
	return obj1Transform; 
}
// Make the crab walk sideways
void sideWalkCrab(RectCrabRenderer &crab)
{
	// Walking Crab 
	float crabWalkTranslation = crab.PixelSize;
	float crabLeftXCoor = crab.CrabCurrentPos[0] - crab.CrabScale;
	float crabRightXCoor = crab.CrabCurrentPos[0] + crab.CrabScale;

	// if crab is unable to move, return 
	if (crabRightXCoor >= 1.0f && crabLeftXCoor <= -1.0f) return;

	if (crabRightXCoor >= 1.0f || crabLeftXCoor <= -1.0f) crab.MoveRight = !crab.MoveRight;
	if (!crab.MoveRight) crabWalkTranslation *= -1.f;
	crab.WalkingPhase = !crab.WalkingPhase;
	crab.CrabCurrentPos[0] += crabWalkTranslation;
	crab.CrabOriginalPos = crab.CrabCurrentPos;
	crab.Trans = glm::translate(crab.Trans, glm::vec3(crabWalkTranslation, 0.0f, 0.0f));
}