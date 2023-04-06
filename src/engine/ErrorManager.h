//
// Created by Andrew Graser on 3/31/2023.
//

#ifndef OPENGL_BASE_ERRORMANAGER_H
#define OPENGL_BASE_ERRORMANAGER_H

#include "glad/glad.h"


#define ASSERT(x) if(!(x)) __debugbreak();
#define GLErrorManager(x) GLClearError(); \
    x;                            \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))


void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

#endif //OPENGL_BASE_ERRORMANAGER_H
