#include <glad/glad.h>
#include <iostream>

#include "./Log.h"


#define ASSERT(Expression) if (!(Expression)) __debugbreak();
#define GLCall(Function) GLClearErrors();\
    Function;\
    ASSERT(GLIsError())

void GLClearErrors() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLIsError() {
    while (unsigned int errorCode = glGetError()) {
        LOG("[OpenGL Error]: " << errorCode)
            return false;
    }

    return true;
}