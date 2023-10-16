
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

int main(void)
{
	//------Setting GLFW/GLEW------//
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow* window = glfwCreateWindow(960, 720, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glewInit();

	//------------------------------------Write after this line only------------------------------------//
	
	//------Setting Vertex Buffer Object------//
	unsigned int VBO;
	float vertexPositions[] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f
	};

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

	//------Setting Vertex Attibute------//
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	//------Setting Vertex Shader------//
	unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	std::string vertexShaderSource =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec3 position;\n"
		"\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(position.x,position.y,position.z,1.0f);\n"
		"}\n";

	const char* vertexSrc = vertexShaderSource.c_str();
	glShaderSource(vertexShaderID, 1, &vertexSrc, NULL);
	glCompileShader(vertexShaderID);

	//------Setting Fragment Shader------//
	unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragmentShaderSource =
		"#version 330 core\n"
		"\n"
		"out vec4 color;\n"
		"\n"
		"void main()\n"
		"{\n"
		"   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"}\n";

	const char* fragmentSrc = fragmentShaderSource.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentSrc, NULL);
	glCompileShader(fragmentShaderID);

	//------Setting Program------//
	unsigned int program = glCreateProgram();
	glAttachShader(program, vertexShaderID);
	glAttachShader(program, fragmentShaderID);
	glLinkProgram(program);
	glValidateProgram(program);
	glUseProgram(program);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	//------Setting Vertex Array Object------//
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//------Render Loop------//
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
	

		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}