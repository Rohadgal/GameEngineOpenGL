#include "Game.hpp"


#include <glm/glm.hpp>

#include <glad/glad.h>

#include"Utils/Archivo.hpp"

	/*"vec2 vertices[3] = {\n"
		"   {0.0f, 0.5f},\n"
		"   {-0.5f, -0.5f},\n"
		"   {0.5f, -0.5f}\n"
		"};*/
Game::Game()
{
	m_Window = std::make_unique<GL::Window>(Nombre, Ancho, Alto);
	m_Renderizador = m_Window->CrearRenderizador();
	m_Shader = GL::Shader::Desdearchivo("./Assets/shaders/Basic.vert", "./Assets/shaders/Basic.frag");

	//vertex Buffer o memoria de vertices
	//Datos
	float vertices[] =
	{
	   -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
	   -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f,

	   /*-0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f,*/
	    0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
	};//Esto es mucho codigo como podemos reutilizarlo con un index buffer asi que usaremos indices explcarles ahora los indices luego de hacer el cuadro con vertices

	uint8_t indices[] = {
		0,1,2,
		0,2,3
	};

	GL::VertexArray::Atributo atributos[] =
	{
		{0, GL::VertexArray::TipoAtributo::Float2},
		{1, GL::VertexArray::TipoAtributo::Float3},
	};

	std::shared_ptr<GL::VertexBuffer> vertexBuffer = std::make_shared<GL::VertexBuffer>(sizeof(vertices) / sizeof(vertices[0]), vertices);
	std::shared_ptr<GL::IndexBuffer> indexBuffer = std::make_shared<GL::IndexBuffer>(sizeof(indices) / sizeof(indices[0]), indices);

	m_VertexArray = std::make_unique<GL::VertexArray>(atributos, sizeof(atributos) / sizeof(atributos[0]));
	m_VertexArray->SetDataBuffer(vertexBuffer, indexBuffer);

}

Game::~Game()
{
}

void Game::Run()
{
	
	m_Renderizador->Viewport(0, 0, Ancho, Alto);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//esto es para dibujar las lineas nadamas
	//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);//Esto es para dibujar los puntos de los vertices
	while (m_Window->Corriendo())
	{
		m_Window->RecibirEventos();

		Actualizar();

		Renderizar();
	}

}

void Game::Actualizar()
{

}

void Game::Renderizar()
{
	m_Renderizador->LimpiarPantalla(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
	/*static int32_t p;

	m_Renderizador->Viewport(p, p, Ancho, Alto);//hacer la prueba de los modulos cambiando ancho y alto a 100*/

	/*static float an = 0.0f;

	float r = glm::sin(glm::radians(an)) * 0.5f +0.5f;
	float g = glm::sin(2 * glm::radians(an)) * 0.5f + 0.5f;
	float b = glm::cos(glm::radians(an)) * 0.5f + 0.5f;
	*/
	//////////////////////////////////////////////////////////
	m_Shader->Bind();
	m_VertexArray->Bind();
	glDrawElements(GL_TRIANGLES, m_VertexArray->GetDrawCount(), GL_UNSIGNED_BYTE, nullptr);
	/////////////////////////////////////////////////////////
	m_Window->Cambiar();

	//an += 180.0f / 360.0f;
	
	//p = ++p % Alto;
	/* %6
	1	1
	2	2
	3	3
	4	4
	5	5
	6	1

	1
	2
	3
	*/
}