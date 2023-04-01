//
// Created by Andrew Graser on 3/31/2023.
//

#include <stdexcept>
#include <string>

#include "Renderer.h"

void GLClearError() {
    while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char *function, const char *file, int line) {
    while(GLenum error = glGetError()){
        throw std::runtime_error("[OpenGL Error] (" + std::to_string(error) + "): " +
                                function + " " + file + ":" + std::to_string(line));
    }
    return true;
}