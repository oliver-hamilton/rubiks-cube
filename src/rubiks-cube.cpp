// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.hpp>
using namespace glm;

int main() {
	// Initialise GLFW
	glewExperimental = true;	// Needed for core profile
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialise GLFW\n");
		return -1;
	}

	// Create window
	glfwWindowHint(GLFW_SAMPLES, 4);	// 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	// We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// We don't want the old OpenGL

	// Open a window and create its OpenGL context
	GLFWwindow* window;
	window = glfwCreateWindow(1024, 768, "Rubik's Cube Simulator", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);	// Initialise GLEW
	glewExperimental = true;	// Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialise GLEW\n");
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// White background
	glClearColor(0.9f, 0.9f, 0.9f, 0.0f);

	// Cube data
	static const GLfloat g_vertex_buffer_data[] = {
		// FACE DATA
		// triangle 1
		-0.95f, -0.95f, 1.0f,
		-0.95f, 0.95f, 1.0f,
		 0.95f, 0.95f, 1.0f,
		// triangle 2
		-0.95f, -0.95f, 1.0f,
		0.95f, -0.95f, 1.0f,
		0.95f, 0.95f, 1.0f,
		// triangle 3
		-1.0f, -0.95f, 0.95f,
		-1.0f, -0.95f, -0.95f,
		-1.0f, 0.95f, -0.95f,
		// triangle 4
		-1.0f, -0.95f, 0.95f,
		-1.0f, 0.95f, 0.95f,
		-1.0f, 0.95f, -0.95f,
		// triangle 5
		-0.95f, -1.0f, 0.95f,
		-0.95f, -1.0f, -0.95f,
		0.95f, -1.0f, 0.95f,
		// triangle 6
		0.95f, -1.0f, 0.95f,
		0.95f, -1.0f, -0.95f,
		-0.95f, -1.0f, -0.95f,
		// triangle 7
		1.0f, -0.95f, 0.95f,
		1.0f, -0.95f, -0.95f,
		1.0f, 0.95f, -0.95f,
		// triangle 8
		1.0f, -0.95f, 0.95f,
		1.0f, 0.95f, 0.95f,
		1.0f, 0.95f, -0.95f,
		// triangle 9
		0.95f, 0.95f, -1.0f,
		0.95f, -0.95f, -1.0f,
		-0.95f, -0.95f, -1.0f,
		// triangle 10
		0.95f, 0.95f, -1.0f,
		-0.95f, 0.95f, -1.0f,
		-0.95f, -0.95f, -1.0f,
		// triangle 11
		-0.95f, 1.0f, -0.95f,
		0.95f, 1.0f, -0.95f,
		0.95f, 1.0f, 0.95f,
		//triangle 12
		0.95f, 1.0f, 0.95f,
		-0.95f, 1.0f, 0.95f,
		-0.95f, 1.0f, -0.95f,

		// BORDER DATA
		// triangle 1
		-1.0f, -1.0f, 0.999f,
		-1.0f, 1.0f, 0.999f,
		 1.0f, 1.0f, 0.999f,
		// triangle 2
		-1.0f, -1.0f, 0.999f,
		1.0f, -1.0f, 0.999f,
		1.0f, 1.0f, 0.999f,
		// triangle 3
		-0.999f, -1.0f, 1.0f,
		-0.999f, -1.0f, -1.0f,
		-0.999f, 1.0f, -1.0f,
		// triangle 4
		-0.999f, -1.0f, 1.0f,
		-0.999f, 1.0f, 1.0f,
		-0.999f, 1.0f, -1.0f,
		// triangle 5
		-1.0f, -0.999f, 1.0f,
		-1.0f, -0.999f, -1.0f,
		1.0f, -0.999f, 1.0f,
		// triangle 6
		1.0f, -0.999f, 1.0f,
		1.0f, -0.999f, -1.0f,
		-1.0f, -0.999f, -1.0f,
		// triangle 7
		0.999f, -1.0f, 1.0f,
		0.999f, -1.0f, -1.0f,
		0.999f, 1.0f, -1.0f,
		// triangle 8
		0.999f, -1.0f, 1.0f,
		0.999f, 1.0f, 1.0f,
		0.999f, 1.0f, -1.0f,
		// triangle 9
		1.0f, 1.0f, -0.999f,
		1.0f, -1.0f, -0.999f,
		-1.0f, -1.0f, -0.999f,
		// triangle 10
		1.0f, 1.0f, -0.999f,
		-1.0f, 1.0f, -0.999f,
		-1.0f, -1.0f, -0.999f,
		// triangle 11
		-1.0f, 0.999f, -1.0f,
		1.0f, 0.999f, -1.0f,
		1.0f, 0.999f, 1.0f,
		//triangle 12
		1.0f, 0.999f, 1.0f,
		-1.0f, 0.999f, 1.0f,
		-1.0f, 0.999f, -1.0f,
	};

	static const GLfloat g_colour_buffer_data[] = {
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.65f, 0.0f,
		1.0f, 0.65f, 0.0f,
		1.0f, 0.65f, 0.0f,
		1.0f, 0.65f, 0.0f,
		1.0f, 0.65f, 0.0f,
		1.0f, 0.65f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
	};

	int width = 2;
	int height = 2;

	// Create a Vertex Array Object and set it as the current one
	GLuint VertexArrayId;
	glGenVertexArrays(1, &VertexArrayId);
	glBindVertexArray(VertexArrayId);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// Identifies our vertex buffer
	GLuint vertexbuffer;
	// Generate one, put the resulting id in vertex buffer
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glVertexAttribPointer(
			0,
			3,			// size
			GL_FLOAT,	// type
			GL_FALSE,	// normalized?
			0,			// stride
			(void*)0	// array buffer offset
		);

	// Identifies our colour buffer
	GLuint colourbuffer;
	// Generate one, put the resulting id in colour buffer
	glGenBuffers(1, &colourbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colourbuffer);
	// Give our colours to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_colour_buffer_data), g_colour_buffer_data, GL_STATIC_DRAW);
	glVertexAttribPointer(
			1,
			3,			// size
			GL_FLOAT,	// type
			GL_FALSE, 	// normalized
			0,			// stride
			(void*)0	// array buffer offset
		);

	glBindVertexArray(0);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	// Get a handle for our uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	float mouseSpeed = 0.002f;
	float horizontalAngle = 3.14f;
	float verticalAngle = 0.0f;
	float lastTime;
	float currentTime = glfwGetTime();
	float deltaTime = 0.05f;
	float radius = 6.0f;
	float speed = 3.0f;

	glm::mat4 rotateMatrix[3][3][3] = {
								{{glm::mat4(1.0f), glm::mat4(1.0f), glm::mat4(1.0f)},
								 {glm::mat4(1.0f), glm::mat4(1.0f), glm::mat4(1.0f)},
								 {glm::mat4(1.0f), glm::mat4(1.0f), glm::mat4(1.0f)}},
								{{glm::mat4(1.0f), glm::mat4(1.0f), glm::mat4(1.0f)},
								 {glm::mat4(1.0f), glm::mat4(1.0f), glm::mat4(1.0f)},
								 {glm::mat4(1.0f), glm::mat4(1.0f), glm::mat4(1.0f)}},
								{{glm::mat4(1.0f), glm::mat4(1.0f), glm::mat4(1.0f)},
								 {glm::mat4(1.0f), glm::mat4(1.0f), glm::mat4(1.0f)},
								 {glm::mat4(1.0f), glm::mat4(1.0f), glm::mat4(1.0f)}}
	};

	float leftToRotateX[3][3][3] = {
								{{0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f}},
								{{0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f}},
								{{0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f}}
	};
	float leftToRotateY[3][3][3] = {
								{{0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f}},
								{{0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f}},
								{{0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f}}
	};
	float leftToRotateZ[3][3][3] = {
								{{0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f}},
								{{0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f}},
								{{0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f}}
	};

	float rotationAngleX[3][3][3] = {
								{{0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f}},
								{{0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f}},
								{{0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f}}
	};
	float rotationAngleY[3][3][3] = {
								{{0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f}},
								{{0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f}},
								{{0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f}}
	};
	float rotationAngleZ[3][3][3] = {
								{{0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f}},
								{{0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f}},
								{{0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f},
								 {0.0f, 0.0f, 0.0f}}
	};

	float x_t = 0.0f;
	float y_t = 0.0f;

	bool rotating;
	
	glm::vec3 position = glm::vec3(0, 0, 0);

	// Ensure we can capture the escape key being pressed
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	do {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::vec3 position(
			radius * cos(y_t) * sin(x_t),
			radius * sin(y_t),
			radius * cos(y_t) * cos(x_t)
		);
		
		// Move right
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			x_t -= deltaTime * speed;
		}
		// Move left
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
			x_t += deltaTime * speed;
		}

		// Move up
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			y_t += deltaTime * speed;
		}
		// Move down
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			y_t -= deltaTime * speed;
		}
		
		// Generate our MVP (model view projection) matrix
		glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.01f, 100.0f);

		// Camera matrix
		glm::mat4 View = glm::lookAt(
			position,
			glm::vec3(0.0f, 0.0f, 0.0f), // and looks at the origin
			glm::vec3(0.0f, cos(y_t), 0.0f) // Head is up
		);

		// Use the shader
		glUseProgram(programID);
		glBindVertexArray(VertexArrayId);

		rotating = false;
		for (int x = -1; x <= 1; x++) {
			for (int y = -1; y <= 1; y++) {
				for (int z = -1; z <= 1; z++) {
					if (leftToRotateY[x+1][y+1][z+1] != 0.0f) {
						if (leftToRotateY[x+1][y+1][z+1] < deltaTime * 0.5f && leftToRotateY[x+1][y+1][z+1] > -deltaTime * 0.5f) {
							rotateMatrix[x+1][y+1][z+1] = glm::rotate(glm::mat4(1.0f), leftToRotateY[x+1][y+1][z+1], glm::vec3(0.0f, 1.0f, 0.0f)) * rotateMatrix[x+1][y+1][z+1];
							leftToRotateY[x+1][y+1][z+1] = 0;
						}
						else if (leftToRotateY[x+1][y+1][z+1] > 0.0f) {
							leftToRotateY[x+1][y+1][z+1] -= deltaTime * 0.5f;
							rotateMatrix[x+1][y+1][z+1] = glm::rotate(glm::mat4(1.0f), deltaTime * 0.5f, glm::vec3(0.0f, 1.0f, 0.0f)) * rotateMatrix[x+1][y+1][z+1];
						}
						else if (leftToRotateY[x+1][y+1][z+1] < 0.0f) {
							leftToRotateY[x+1][y+1][z+1] += deltaTime * 0.5f;
							rotateMatrix[x+1][y+1][z+1] = glm::rotate(glm::mat4(1.0f), -deltaTime * 0.5f, glm::vec3(0.0f, 1.0f, 0.0f)) * rotateMatrix[x+1][y+1][z+1];
						}
						rotating = true;
					}

					else if (leftToRotateZ[x+1][y+1][z+1] != 0.0f) {
						if (leftToRotateZ[x+1][y+1][z+1] < deltaTime * 0.5f && leftToRotateZ[x+1][y+1][z+1] > -deltaTime * 0.5f) {
							rotateMatrix[x+1][y+1][z+1] = glm::rotate(glm::mat4(1.0f), leftToRotateZ[x+1][y+1][z+1], glm::vec3(0.0f, 0.0f, 1.0f)) * rotateMatrix[x+1][y+1][z+1];
							leftToRotateZ[x+1][y+1][z+1] = 0;
						}
						else if (leftToRotateZ[x+1][y+1][z+1] > 0.0f) {
							leftToRotateZ[x+1][y+1][z+1] -= deltaTime * 0.5f;
							rotateMatrix[x+1][y+1][z+1] = glm::rotate(glm::mat4(1.0f), deltaTime * 0.5f, glm::vec3(0.0f, 0.0f, 1.0f)) * rotateMatrix[x+1][y+1][z+1];
						}
						else if (leftToRotateZ[x+1][y+1][z+1] < 0.0f) {
							leftToRotateZ[x+1][y+1][z+1] += deltaTime * 0.5f;
							rotateMatrix[x+1][y+1][z+1] = glm::rotate(glm::mat4(1.0f), -deltaTime * 0.5f, glm::vec3(0.0f, 0.0f, 1.0f)) * rotateMatrix[x+1][y+1][z+1];
						}
						rotating = true;
					}

					else if (leftToRotateX[x+1][y+1][z+1] != 0.0f) {
						if (leftToRotateX[x+1][y+1][z+1] < deltaTime * 0.5f && leftToRotateX[x+1][y+1][z+1] > -deltaTime * 0.5f) {
							rotateMatrix[x+1][y+1][z+1] = glm::rotate(glm::mat4(1.0f), leftToRotateX[x+1][y+1][z+1], glm::vec3(1.0f, 0.0f, 0.0f)) * rotateMatrix[x+1][y+1][z+1];
							leftToRotateX[x+1][y+1][z+1] = 0;
						}
						else if (leftToRotateX[x+1][y+1][z+1] > 0.0f) {
							leftToRotateX[x+1][y+1][z+1] -= deltaTime * 0.5f;
							rotateMatrix[x+1][y+1][z+1] = glm::rotate(glm::mat4(1.0f), deltaTime * 0.5f, glm::vec3(1.0f, 0.0f, 0.0f)) * rotateMatrix[x+1][y+1][z+1];
						}
						else if (leftToRotateX[x+1][y+1][z+1] < 0.0f) {
							leftToRotateX[x+1][y+1][z+1] += deltaTime * 0.5f;
							rotateMatrix[x+1][y+1][z+1] = glm::rotate(glm::mat4(1.0f), -deltaTime * 0.5f, glm::vec3(1.0f, 0.0f, 0.0f)) * rotateMatrix[x+1][y+1][z+1];
						}
						rotating = true;
					}

					glm::mat4 transMatrix = glm::translate(rotateMatrix[x+1][y+1][z+1], glm::vec3(x * 0.6f, y * 0.6f, z * 0.6f));
					glm::mat4 scaleMatrix = glm::scale(transMatrix, glm::vec3(0.3f, 0.3f, 0.3f));

					glm::mat4 Model = scaleMatrix;
					// Our ModelViewProjection: multiplication of these three matrices
					glm::mat4 mvp = Projection * View * Model;
					// Send our transformation to the currently bound shader, in the "MVP" uniform
					glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);


					glDrawArrays(GL_TRIANGLES, 0, 24*3);
				}
			}
		}

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		// Update deltaTime just before input loop
		lastTime = currentTime;
		currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		// Get rotation input
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {
					for (int z = -1; z <= 1; z++) {
						glm::vec4 newCoords = rotateMatrix[x+1][y+1][z+1] * glm::vec4(x, y, z, 1);
						if ((float) round(newCoords.y) == 1.0f && leftToRotateY[x+1][y+1][z+1] == 0.0f && !rotating) {
							leftToRotateY[x+1][y+1][z+1] -= glm::radians(90.0f);
						}
					}
				}
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {
					for (int z = -1; z <= 1; z++) {
						glm::vec4 newCoords = rotateMatrix[x+1][y+1][z+1] * glm::vec4(x, y, z, 1);
						if ((float) round(newCoords.x) == -1.0f && leftToRotateX[x+1][y+1][z+1] == 0.0f && !rotating) {
							leftToRotateX[x+1][y+1][z+1] += glm::radians(90.0f);
						}
					}
				}
			}
		}

		else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {
					for (int z = -1; z <= 1; z++) {
						glm::vec4 newCoords = rotateMatrix[x+1][y+1][z+1] * glm::vec4(x, y, z, 1);
						if ((float) round(newCoords.x) == 1.0f && leftToRotateX[x+1][y+1][z+1] == 0.0f && !rotating) {
							leftToRotateX[x+1][y+1][z+1] -= glm::radians(90.0f);
						}
					}
				}
			}
		}

		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {
					for (int z = -1; z <= 1; z++) {
						glm::vec4 newCoords = rotateMatrix[x+1][y+1][z+1] * glm::vec4(x, y, z, 1);
						if ((float) round(newCoords.y) == -1.0f && leftToRotateY[x+1][y+1][z+1] == 0.0f && !rotating) {
							leftToRotateY[x+1][y+1][z+1] += glm::radians(90.0f);
						}
					}
				}
			}
		}

		else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {
					for (int z = -1; z <= 1; z++) {
						glm::vec4 newCoords = rotateMatrix[x+1][y+1][z+1] * glm::vec4(x, y, z, 1);
						if ((float) round(newCoords.z) == 1.0f && leftToRotateZ[x+1][y+1][z+1] == 0.0f && !rotating) {
							leftToRotateZ[x+1][y+1][z+1] -= glm::radians(90.0f);
						}
					}
				}
			}
		}

		else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {
					for (int z = -1; z <= 1; z++) {
						glm::vec4 newCoords = rotateMatrix[x+1][y+1][z+1] * glm::vec4(x, y, z, 1);
						if ((float) round(newCoords.z) == -1.0f && leftToRotateZ[x+1][y+1][z+1] == 0.0f && !rotating) {
							leftToRotateZ[x+1][y+1][z+1] += glm::radians(90.0f);
						}
					}
				}
			}
		}
		
		// Wait for input loop to finish
		currentTime = glfwGetTime();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && 
		   glfwWindowShouldClose(window) == 0);

	return 0;
}