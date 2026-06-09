#include <glad.h>
#include <glfw3.h>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <cmath>

#include "vertex_array_class.h"
#include "element_buffer_class.h"
#include "shader_class.h"
#include "tools.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float deltaTime);

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

float ObjectX = 0.0f;
float ObjectY = 0.0f;
float ObjectRotation = 0.0f;

int main()
{
    if (!glfwInit()) {
        std::cout << "Failed to init GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearningOpenGL", nullptr, nullptr);
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

    Shader ShaderClass("./shaders/basic.shader");
    ShaderClass.CreateShaderProgram();
    ShaderClass.UseProgram();

    /*int UnfiformLocation = glGetUniformLocation(ShaderProgram, "u_Color");
    ASSERT(UnfiformLocation != -1);
    glUniform4f(UnfiformLocation, 1.0f, 1.0f, 0.0f, 1.0f);*/
    //////////////////////////////////////////////////////////////////////////////////////////

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    float lastFrameTime = static_cast<float>(glfwGetTime());

    while (!glfwWindowShouldClose(window))
    {
        float currentFrameTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        processInput(window, deltaTime);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float c = std::cos(ObjectRotation);
        float s = std::sin(ObjectRotation);
        float transform[] = {
             c,    s, 0.0f, 0.0f,
            -s,    c, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            ObjectX, ObjectY, 0.0f, 1.0f
        };

        int transformLocation = glGetUniformLocation(ShaderClass.m_ShaderProgram, "u_Transform");
        ASSERT(transformLocation != -1);
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, transform);

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

void processInput(GLFWwindow* window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    const float moveSpeed = 0.8f;
    const float rotationSpeed = 2.5f;

    float forwardX = -std::sin(ObjectRotation);
    float forwardY = std::cos(ObjectRotation);
    float rightX = std::cos(ObjectRotation);
    float rightY = std::sin(ObjectRotation);

    float moveX = 0.0f;
    float moveY = 0.0f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        moveX += forwardX;
        moveY += forwardY;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        moveX -= forwardX;
        moveY -= forwardY;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        moveX += rightX;
        moveY += rightY;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        moveX -= rightX;
        moveY -= rightY;
    }

    float moveLength = std::sqrt(moveX * moveX + moveY * moveY);
    if (moveLength > 0.0f)
    {
        ObjectX += (moveX / moveLength) * moveSpeed * deltaTime;
        ObjectY += (moveY / moveLength) * moveSpeed * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        ObjectRotation += rotationSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        ObjectRotation -= rotationSpeed * deltaTime;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
