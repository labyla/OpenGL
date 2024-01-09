#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>

#include "VertexArrayClass/VertexArrayClass.h"
#include "ElementBufferClass/ElementBufferClass.h"
#include "ShaderClass/ShaderClass.h"
#include "Tools.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

int main()
{
    if (!glfwInit()) {
        std::cout << "Failed to init GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //////////////////////////////////////////////////////////////////////////////////////////
    float vertices[] = {
        -0.5f,  0.5f, 0.0f, // Top Left
         1.0f, 0.0f, 0.0f,  // Color

         0.5f,  0.5f, 0.0f, // Top Right
         0.0f, 1.0f, 0.0f,  // Color

        -0.5f, -0.5f, 0.0f, // Bottom Left
         0.0f, 0.0f, 1.0f,  // Color

         0.5f, -0.5f, 0.0f, // Bottom Right
         1.0f, 0.0f, 0.0f,  // Color
    };

    unsigned int indices[] = {
        2, 0, 1,
        2, 3, 1
    };

    VertexArray VAO;
    VAO.Bind();
    VertexBuffer VBO = VertexBuffer(sizeof(vertices), &vertices);

    VertexBufferLayout Layout;
    Layout.PushElement<float>(3, false);
    Layout.PushElement<float>(3, false);

    VAO.AddVertexBuffer(VBO, Layout);

    ElementBuffer EBO = ElementBuffer(sizeof(indices), &indices);

    VBO.Unbind();
    EBO.Unbind();
    VAO.Unbind();

    Shader ShaderClass("./Source/Shaders/Basic.shader");
    ShaderClass.CreateShaderProgram();
    ShaderClass.UseProgram();

    /*int UnfiformLocation = glGetUniformLocation(ShaderProgram, "u_Color");
    ASSERT(UnfiformLocation != -1);
    glUniform4f(UnfiformLocation, 1.0f, 1.0f, 0.0f, 1.0f);*/
    //////////////////////////////////////////////////////////////////////////////////////////

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        VAO.Bind();
        EBO.Bind();
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        //glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //const unsigned int buffers[10] = { Buffer };
    //glDeleteBuffers(1, buffers);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}