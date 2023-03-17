#include "application.h"

#include <iostream>

int main(){
    Application app(1280, 720, "OpenGL Base");

    try{
        app.Run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
