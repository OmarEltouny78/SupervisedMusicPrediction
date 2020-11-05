#include <stdio.h>
#include <iostream>
#include <ctime>

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

GLuint VAO, VBO, IBO, shader, v_uniform, f_uniform, m_uniform;
GLuint VAO1, VBO1, IBO1;
float random;
const float dtr = 3.14 / 180.0;
float Off_T = 0.0f, Off_R = 0.0f, Off_S = 0.0f;


static const char* vshader = "\n\
#version 330 \n\
in vec3 pos;\n\
out vec4 vC; \n\
uniform float s; \n\
uniform mat4 model; \n\
void main() {\n\
	gl_Position =model*vec4(pos.x,pos.y,pos.z,1.0);\n\
	vC=vec4(clamp(pos, 0.6,1.0),1.0); \n\
}\n\
";

static const char* fshader = "\n\
#version 330\n\
uniform vec3 c; \n\
out vec4 colour;\n\
in vec4 vC; \n\
void main(){\n\
	colour=vC;\n\
}\n\
";
void createShape()
{
	GLuint ind[] = {
		1,2,3,
		1,4,2,
		1,4,3,
		2,3,4,
		2,3,5
	};
	GLfloat vertices[] = {
		-1.0f, 0.0f,-0.0f,
		1.0f, 0.0f, -0.0f,
		0.0f, 1.0f, -0.0f,
		0.0f, 0.0f, -0.5f,
		0.0f,-0.5f,0.0f
	};

	//VAO--VBO-->data-->pointer)
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void compileShader()
{
	shader = glCreateProgram();
	if (!shader)
	{
		printf("shader error");
	}

	//create shader
	GLuint verShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	//assgin shader source
	glShaderSource(verShader, 1, &vshader, NULL);
	glShaderSource(fragShader, 1, &fshader, NULL);
	//compile shader
	glCompileShader(verShader);
	glCompileShader(fragShader);

	//attach shaders (v, f) to shader program 
	glAttachShader(shader, verShader);
	glAttachShader(shader, fragShader);
	//attach shader to the program
	glLinkProgram(shader);
	v_uniform = glGetUniformLocation(shader, "s");
	f_uniform = glGetUniformLocation(shader, "c");
	m_uniform = glGetUniformLocation(shader, "model");

}
void createShape1()
{
	GLuint ind[] = {
		1,2,3,
		1,4,2,
		1,4,3,
		2,3,4,
		2,3,5
	};
	GLfloat vertices[] = {
		0.5f, 0.0f,-0.0f,
		-0.5f, 0.0f, -0.0f,
		0.0f, 0.5f, -0.0f,
		0.0f, 0.0f, -0.25f,
		0.0f,-0.f,0.0f
	};

	//VAO--VBO-->data-->pointer)
	glGenVertexArrays(1, &VAO1);
	glBindVertexArray(VAO1);
	glGenBuffers(1, &IBO1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW);
	glGenBuffers(1, &VBO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
int main()
{

	//init glfw
	if (!glfwInit())
	{
		printf("error: glfw");
		glfwTerminate();
		return 1;
	}
	//init & setup window
	GLFWwindow* mainwindow = glfwCreateWindow(800, 600, "shader", NULL, NULL);
	//assign window
	if (!mainwindow)

	{
		printf("error:mainWindow");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(mainwindow);

	if (glewInit() != GLEW_OK)
	{
		printf("error:glew");
		glfwDestroyWindow(mainwindow);
		glfwTerminate();
		return 1;
	}
	//while loop 
	srand(time(NULL));
	createShape();
	createShape1();
	compileShader();
	while (!glfwWindowShouldClose(mainwindow))
	{
		random = rand() % 10 / 10.0;
		//handle event 
		glfwPollEvents();
		//bg
		glClearColor(0.4f, 0.4f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//draw
		glUseProgram(shader);
		glm::mat4 model(1.0);
		//model = glm::translate(model, glm::vec3(Off_T, 0.0, 0.0));
		model = glm::translate(model, glm::vec3(-0.4, -0.65, 0.0));
		model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
		model = glm::rotate(model, 90*dtr,glm::vec3(0.0, 0.0, 1.0));



		if (Off_T <= 1.0f) {

			Off_T += 0.005f;
		}

		else {
			Off_T = -1.5f;
		}


		glUniformMatrix4fv(m_uniform, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(v_uniform, random);
		glUniform3f(f_uniform, 0.2, random, random * random);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glUniformMatrix4fv(m_uniform, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(v_uniform, random);
		glUniform3f(f_uniform, 0.2, random, random * random);
		glBindVertexArray(VAO1);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO1);
		glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glUseProgram(0);
		//buffer setup
		glfwSwapBuffers(mainwindow);

	}
	return 0;
}