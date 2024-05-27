#include "Shader.hpp"
#include<glad/glad.h>
#include "Utils/Archivo.hpp"
#include<assert.h>
namespace GL
{
    Shader::Shader(const char* vertexShader, const char* fragmentShader)
    {
        m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
        m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        m_Program = glCreateProgram();

        glShaderSource(m_VertexShader, 1, &vertexShader, nullptr);
        glShaderSource(m_FragmentShader, 1, &fragmentShader, nullptr);

        glCompileShader(m_VertexShader);
        glCompileShader(m_FragmentShader);

        glAttachShader(m_Program, m_VertexShader);
        glAttachShader(m_Program, m_FragmentShader);

        glLinkProgram(m_Program);
    }
    Shader::~Shader()
    {
        glDeleteProgram(m_Program);
        glDeleteShader(m_FragmentShader);
        glDeleteProgram(m_VertexShader);
    }
    std::shared_ptr<Shader> Shader::Desdearchivo(const char* archivoVertexShader, const char* archivoFragmentShader)
    {
        char* vertexShader = nullptr;
        char* fragmentShader = nullptr;
        assert(Archivo::Leer(archivoVertexShader, &vertexShader) && "No se pudo abrir el archivo del vertex shader");
        assert(Archivo::Leer(archivoFragmentShader, &fragmentShader) && "No se pudo abrir el archivo del fragment shader");

        std::shared_ptr<Shader> retorno = std::make_shared<Shader>(vertexShader, fragmentShader);
        Archivo::Liberar(vertexShader);
        Archivo::Liberar(fragmentShader);

        return retorno;
    }
    void Shader::Bind()
    {
        glUseProgram(m_Program);
    }
}
