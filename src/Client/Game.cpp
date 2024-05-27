#include "Game.hpp"


#include <glm/glm.hpp>

#include <glad/glad.h>

Game::Game()
{
	m_Window = std::make_unique<GL::Window>(Nombre, Ancho, Alto);
	m_Renderizador = m_Window->CrearRenderizador();

	const char* vertexShader =
		"#version 450 core\n"
		"vec2 vertices[3] = {\n"
		"   {0.0f, 0.5f},\n"
		"   {-0.5f, -0.5f},\n"
		"   {0.5f, -0.5f}\n"
		"};\n"
		"void main(){\n"
		"   gl_Position = vec4(vertices[gl_VertexID], 1.0f, 1.0f);\n"
		"}\n\0";

	const char* fragmentShader =
		"#version 450 core\n"
		"out vec4 fColor;\n"
		"void main(){\n"
		"   fColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
		"}\n\0";

	//Crear objetos shaderde OpneGl
	GLuint objetoVertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint objetoFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Subir string al objeto
	glShaderSource(objetoVertexShader, 1, &vertexShader, nullptr);
	glShaderSource(objetoFragmentShader, 1, &fragmentShader, nullptr);
	//Se puede usar docs.gl para buscar informacion de gl
	//Compilar programa
	glCompileShader(objetoVertexShader);
	glCompileShader(objetoFragmentShader);

	//Crear un objeto programa de opengl
	m_ObjetoProgramShader = glCreateProgram();

	//Enviar archivos compilados al programa
	glAttachShader(m_ObjetoProgramShader, objetoVertexShader);
	glAttachShader(m_ObjetoProgramShader, objetoFragmentShader);

	//Linker (union de archivos compilados
	glLinkProgram(m_ObjetoProgramShader);

	/*
	Como funciona el comilador
	1.cpp
	2.cpp, etc, programacion
	
	1.obj
	2.obj, crea el intermediario .obj que ya no es legible por el humano

	el compilador toma esos dos obj
	(1.obj, 2.obj) unir => linking, los une 

	y luego de unir genera el ejecutable
	*/

}

void Game::Run()
{
	m_Renderizador->Viewport(0, 0, Ancho, Alto);

	while (m_Window->Corriendo())
	{
		m_Window->RecibirEventos();

		Actualizar();

		Renderizar();
	}
	glDeleteProgram(m_ObjetoProgramShader);
}

void Game::Actualizar()
{

}

void Game::Renderizar()
{
	static float an = 0.0f;

	float r = glm::sin(glm::radians(an)) * 0.5f +0.5f;
	float g = glm::sin(2 * glm::radians(an)) * 0.5f + 0.5f;
	float b = glm::cos(glm::radians(an)) * 0.5f + 0.5f;
	m_Renderizador->LimpiarPantalla(glm::vec4( r,g,b, 1.0f ));
	//////////////////////////////////////////////////////////
	glUseProgram(m_ObjetoProgramShader);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	/////////////////////////////////////////////////////////
	m_Window->Cambiar();

	an += 180.0f / 360.0f;
}