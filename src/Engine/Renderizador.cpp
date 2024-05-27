#include "Renderizador.hpp"
#include <glad/glad.h>
#include <string>
#include <stdio.h>
static void ManejadorDeErrores(GLenum src, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* msg, void const* user_param);

static std::string FuenteComoString(GLenum fuente);
static std::string TipoComoString(GLenum tipo);
static std::string SeveridadComoString(GLenum severity);
namespace GL
{
	Renderizador::Renderizador()
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(ManejadorDeErrores, nullptr);
		//glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
	}
	void Renderizador::Viewport(uint32_t x, uint32_t y, uint32_t ancho, uint32_t alto)
	{
		glViewport(x, y, ancho, alto);
	}

	void Renderizador::LimpiarPantalla(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT);

	}
}
void ManejadorDeErrores(GLenum src, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* msg, void const* user_param)
{
	std::string fuente = FuenteComoString(src);
	std::string tipo = TipoComoString(type);
	std::string severidad = SeveridadComoString(severity);
	
	printf("Severidad : %s; Fuente: %s, Tipo: %s; Mensaje: %s", severidad.c_str(), fuente.c_str(), tipo.c_str(), msg);

	assert(severity != GL_DEBUG_SEVERITY_HIGH && "Error critico encontrado");
	assert(severity != GL_DEBUG_SEVERITY_MEDIUM && "Error alto nivel");
	assert(severity != GL_DEBUG_SEVERITY_LOW && "Error bajo nivel");
}

std::string FuenteComoString(GLenum fuente)
{
	switch (fuente)
	{
	case GL_DEBUG_SOURCE_API:
		return "API";

	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		return "Window system";

	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		return "Shader compiler";

	case GL_DEBUG_SOURCE_THIRD_PARTY:
		return "Third party";

	case GL_DEBUG_SOURCE_APPLICATION:
		return "Application";

	case GL_DEBUG_SOURCE_OTHER:
		return "Other";
	}
	assert(false);
	return "";
}

std::string TipoComoString(GLenum tipo)
{
	switch (tipo)
	{
		case GL_DEBUG_TYPE_ERROR: return "Error";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "Deprecated behavior";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "Undefined behavior";
		case GL_DEBUG_TYPE_PORTABILITY: return "Portability";
		case GL_DEBUG_TYPE_PERFORMANCE: return "Prefomance";
		case GL_DEBUG_TYPE_MARKER: return "marker";
		case GL_DEBUG_TYPE_OTHER: return "Other";
	}
	assert(false);
	return "";
}

std::string SeveridadComoString(GLenum severity)
{
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_NOTIFICATION: return "Notificacion";
	case GL_DEBUG_SEVERITY_LOW: return "Low";
	case GL_DEBUG_SEVERITY_MEDIUM:return "Medium";
	case GL_DEBUG_SEVERITY_HIGH: return "High";
	}
	assert(false);
	return "";
}

