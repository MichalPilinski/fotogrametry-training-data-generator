#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <Windows.h>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "ViewBuilder.h"
#include "Background.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "FreeImage.h"

using namespace glm;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
double deltaTime = 0.0f;
double lastFrame = 0.0f;

float ambientStrength = 0.5;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "DataGenerator", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	Shader ourShader("BasicShader.vs", "BasicShader.fs");

	Model ourModel("Models/TableSimplified/Table/Table.obj");
	ViewBuilder viewBuilder(ourModel.GetBoundingBox(), 1.5, 3, vec3(2,10,60), camera.Zoom);

	Background background(ourModel.GetMaxDimentionXY());
	background.AddTexture("wall.jpg", "Textures", Wall);
	background.AddTexture("moth.jpg", "Textures", Wall);
	
	Background floor(ourModel.GetMaxDimentionXY());
	floor.AddTexture("floor.jpg", "Textures", Floor);

	while (!glfwWindowShouldClose(window))
	{

		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.1f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Set(viewBuilder.GetCameraPosition(), viewBuilder.GetCameraTarget());
		//camera.Describe();
		ourShader.use();

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();

		ourShader.setMat4("projection", projection);
		ourShader.setMat4("view", view);

		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0, 0, 0));
		ourShader.setMat4("model", model);
		ourModel.Draw(ourShader);

		background.SetPosition(10, SCR_WIDTH/SCR_HEIGHT, camera, 30, 0);
		background.SetTexture(0, Wall);
		background.Draw(ourShader);

		floor.SetPosition(10, SCR_WIDTH / SCR_HEIGHT, camera, 30, 0);
		floor.SetTexture(0, Floor);
		floor.Draw(ourShader);

		glfwSwapBuffers(window);
		glfwPollEvents();

		Sleep(6);
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}