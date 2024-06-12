//MAIN CODE FOR CREATING A ROTATING CUBE

#include<filesystem>
namespace fs = std::filesystem;
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"


const unsigned int width = 800;
const unsigned int height = 800;

// Vertices coordinates for a cube
GLfloat vertices[] = {
	// Front face
	-0.25f, -0.25f,  0.25f,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f, // 0
	-0.25f,  0.25f,  0.25f,  0.83f, 0.70f, 0.44f,  0.0f, 1.0f, // 1
	 0.25f,  0.25f,  0.25f,  0.83f, 0.70f, 0.44f,  1.0f, 1.0f, // 2
	 0.25f, -0.25f,  0.25f,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f, // 3

	 // Back face
	 -0.25f, -0.25f, -0.25f,  0.92f, 0.86f, 0.76f,  0.0f, 0.0f, // 4
	 -0.25f,  0.25f, -0.25f,  0.92f, 0.86f, 0.76f,  0.0f, 1.0f, // 5
	  0.25f,  0.25f, -0.25f,  0.92f, 0.86f, 0.76f,  1.0f, 1.0f, // 6
	  0.25f, -0.25f, -0.25f,  0.92f, 0.86f, 0.76f,  1.0f, 0.0f, // 7

	  // Left face
	  -0.25f, -0.25f, -0.25f,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f, // 8
	  -0.25f,  0.25f, -0.25f,  0.83f, 0.70f, 0.44f,  0.0f, 1.0f, // 9
	  -0.25f,  0.25f,  0.25f,  0.83f, 0.70f, 0.44f,  1.0f, 1.0f, // 10
	  -0.25f, -0.25f,  0.25f,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f, // 11

	  // Right face
	   0.25f, -0.25f, -0.25f,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f, // 12
	   0.25f,  0.25f, -0.25f,  0.83f, 0.70f, 0.44f,  0.0f, 1.0f, // 13
	   0.25f,  0.25f,  0.25f,  0.83f, 0.70f, 0.44f,  1.0f, 1.0f, // 14
	   0.25f, -0.25f,  0.25f,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f, // 15

	   // Top face
	   -0.25f,  0.25f, -0.25f,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f, // 16
	   -0.25f,  0.25f,  0.25f,  0.83f, 0.70f, 0.44f,  0.0f, 1.0f, // 17
		0.25f,  0.25f,  0.25f,  0.83f, 0.70f, 0.44f,  1.0f, 1.0f, // 18
		0.25f,  0.25f, -0.25f,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f, // 19

		// Bottom face
		-0.25f, -0.25f, -0.25f,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f, // 20
		-0.25f, -0.25f,  0.25f,  0.83f, 0.70f, 0.44f,  0.0f, 1.0f, // 21
		 0.25f, -0.25f,  0.25f,  0.83f, 0.70f, 0.44f,  1.0f, 1.0f, // 22
		 0.25f, -0.25f, -0.25f,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f  // 23
};

// Indices for a cube
GLuint indices[] = {
	0, 1, 2, 0, 2, 3,       // Front face
	4, 5, 6, 4, 6, 7,       // Back face
	8, 9, 10, 8, 10, 11,    // Left face
	12, 13, 14, 12, 14, 15, // Right face
	16, 17, 18, 16, 18, 19, // Top face
	20, 21, 22, 20, 22, 23  // Bottom face
};


int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "Solving a Rubik's Cube"
	GLFWwindow* window = glfwCreateWindow(width, height, "Solving a Rubik's Cube", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);



	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");



	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string texPath = "/Resource Files/";

	// Texture
	Texture brickTex("./brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);

	// Bind the texture and set the texture wrapping and filtering options
	brickTex.Bind();

	// Set the texture wrapping parameters (GL_REPEAT is the default)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // Set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);    // Set texture wrapping to GL_REPEAT

	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Set texture filtering for minification
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Set texture filtering for magnification

	// Variables that help the rotation of the cube
	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.53f, 0.81f, 0.98f, 1.0f); // Light blue background
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		// Simple timer
		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.5f;
			prevTime = crntTime;
		}

		// Initializes matrices so they are not the null matrix
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		// Assigns different transformations to each matrix
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.3f, -2.0f)); // Adjust the y-coordinate for finer control
		proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

		// Outputs the matrices into the Vertex Shader
		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		glUniform1f(uniID, 0.5f);
		// Binds texture so that it appears in rendering
		brickTex.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}




	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	brickTex.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}