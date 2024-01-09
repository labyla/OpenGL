#include "ShaderClass.h"
#include <glad/glad.h>
#include <iostream>
#include <memory>

#include "../Log.h"

Shader::Shader(const std::string& a_FilePath) {
    enum class ShaderType {
        NONE = -1,
        VERTEX,
        FRAGMENT
    };

    std::ifstream FileStream = std::ifstream(a_FilePath);
    ShaderType CurrentShaderType = ShaderType::NONE;
    std::stringstream StringStream[2];

    std::string Line;
    while (std::getline(FileStream, Line)) {
        if (Line.find("#shader") != std::string::npos) {
            if (Line.find("vertex") != std::string::npos) {
                CurrentShaderType = ShaderType::VERTEX;
            }
            else if (Line.find("fragment") != std::string::npos) {
                CurrentShaderType = ShaderType::FRAGMENT;
            }

            continue;
        }

        StringStream[(int)CurrentShaderType] << Line << '\n';
    }

    m_ShaderSources.VertexShader = StringStream[0].str();
    m_ShaderSources.FragmentShader = StringStream[1].str();
}

unsigned int Shader::CreateShader(unsigned int a_Type, const std::string& a_ShaderSource) {
    unsigned int shader = glCreateShader(a_Type);
    const char* shaderSource = a_ShaderSource.c_str();
    glShaderSource(shader, 1, &shaderSource, nullptr);

    return shader;
}

bool Shader::CompileShader(unsigned int a_Shader) {
    glCompileShader(a_Shader);

    int compileStatus;
    glGetShaderiv(a_Shader, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus == GL_FALSE) {
        int errorInfoLength;
        glGetShaderiv(a_Shader, GL_INFO_LOG_LENGTH, &errorInfoLength);

        char* errorInfo = new char[errorInfoLength];
        glGetShaderInfoLog(a_Shader, errorInfoLength, nullptr, errorInfo);
        LOG("[Shader Compile Error]: " << errorInfo);
        delete[] errorInfo;

        return false;
    }

    return true;
}

unsigned int Shader::CreateShaderProgram() {
    m_ShaderProgram = glCreateProgram();

    unsigned int vertexShader = CreateShader(GL_VERTEX_SHADER, m_ShaderSources.VertexShader);
    if (!CompileShader(vertexShader))
        return 0;
    glAttachShader(m_ShaderProgram, vertexShader);

    unsigned int fragmentShader = CreateShader(GL_FRAGMENT_SHADER, m_ShaderSources.FragmentShader);
    if (!CompileShader(fragmentShader))
        return 0;
    glAttachShader(m_ShaderProgram, fragmentShader);
    

    glLinkProgram(m_ShaderProgram);
    int linkStatus;
    glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &linkStatus);
    if (linkStatus == GL_FALSE) {
        int errorInfoLength;
        glGetProgramiv(m_ShaderProgram, GL_INFO_LOG_LENGTH, &errorInfoLength);

        char* errorInfo = new char[errorInfoLength];
        glGetProgramInfoLog(m_ShaderProgram, errorInfoLength, nullptr, errorInfo);
        LOG("[Program Link Error]: " << errorInfo);
        delete[] errorInfo;

        return 0;
    }

    glValidateProgram(m_ShaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return m_ShaderProgram;
}

void Shader::UseProgram() {
    glUseProgram(m_ShaderProgram);
}

Shader::~Shader() {
    glDeleteProgram(m_ShaderProgram);
}