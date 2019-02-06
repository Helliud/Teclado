#include "pch.h"
#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <math.h>

using namespace std;

float xTriangulo = 0.0;
float yTriangulo = 0.0;
float velocidad = 0.05;

void dibujarTriangulo() {
	glPushMatrix();
	//Transformaciones
	glTranslatef(xTriangulo, yTriangulo, 0);
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0.2, 0);
	glVertex3f(-0.2, -0.2, 0);
	glVertex3f(0.2, -0.2, 0);
	glEnd();
	glPopMatrix();
}

void dibujar() {
	dibujarTriangulo();
}


void actualizar(){
	if (xTriangulo > 0.8) {
		xTriangulo = 0.8;
	}

	if (xTriangulo < -0.8) {
		xTriangulo = -0.8;
	}

	if (yTriangulo > 0.8) {
		yTriangulo = 0.8;
	}

	if (yTriangulo < -0.8) {
		yTriangulo = -0.8;
	}

}



void teclado_callback(GLFWwindow * window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		xTriangulo += velocidad;
	}

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		xTriangulo -= velocidad;
	}

	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		yTriangulo += velocidad;
	}

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		yTriangulo -= velocidad;
	}

}

int main()
{
	//Declaramos
	GLFWwindow * window;
	// Si no se pudo iniciar GLFW terminamos la ejecucion
	if (!glfwInit()) { exit(EXIT_FAILURE); } // Si se pudo iniciar GLFW entonces inicializamos la ventana
	
	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);

	//SI no pudimos iniciar la ventana, entonces terminamos la ejecucion
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//Establecemos el contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido el contexto, activamos funciones modernas
	glewExperimental = true;
	GLenum errorGlew = glewInit();
	if (errorGlew != GLEW_OK) {
		cout << glewGetErrorString(errorGlew);
	}

	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;
	cout << "\n Hecho por Javier Eliud \n Matricula: 169171";

	//Para reconocer las teclas
	glfwSetKeyCallback(window, teclado_callback);

	//ciclo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window)) {
		//Establecer region de dibujo
		glViewport(0, 0, 1020, 768);
		//Establece el color de borrado
		glClearColor(0, 0, 0, 0);
		//Clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		actualizar();
		dibujar();
		
		//Cambiar los buffer
		glfwSwapBuffers(window);
		//Reconocer si hay entradas
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}