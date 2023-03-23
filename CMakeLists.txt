cmake_minimum_required(VERSION 3.24)
project(OpenGl_Base)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 17)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set (CMAKE_VERBOSE_MAKEFILE 0) # 1 should be used for debugging
set (CMAKE_SUPPRESS_REGENERATION TRUE) # Suppresses ZERO_CHECK
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()


option (GLFW_INSTALL OFF)
option (GLFW_BUILD_DOCS OFF)
option (GLFW_BUILD_EXAMPLES OFF)
option (GLFW_BUILD_TESTS OFF)

set(LIB_DIR ${PROJECT_SOURCE_DIR}/external)

add_subdirectory(${LIB_DIR}/glfw)

set(ASSIMP_DIR ${LIB_DIR}/assimp/)
add_subdirectory(${ASSIMP_DIR})
include_directories(${ASSIMP_DIR}/include)


include_directories (src/
        external/glad/include/
        external/glfw/include/
        external/glm/
        external/stb/
        external/assimp/include)


file(GLOB EXTERNAL_SRC ${LIB_DIR}/glad/src/glad.c)

file(GLOB_RECURSE PRJ_SRC glad.c ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*.c
        ${PROJECT_SOURCE_DIR}/src/*.cc
        ${PROJECT_SOURCE_DIR}/src/*.cxx)

file(GLOB_RECURSE PRJ_HEADERS ${PROJECT_SOURCE_DIR}/src/*.h
        ${PROJECT_SOURCE_DIR}/src/*.hpp)

file(GLOB_RECURSE PRJ_SHADERS ${PROJECT_SOURCE_DIR}/src/shaders/*.frag
        ${PROJECT_SOURCE_DIR}/src/shaders/*.vert
        ${PROJECT_SOURCE_DIR}/src/shaders/*.geom
        ${PROJECT_SOURCE_DIR}/src/shaders/*.comp)


source_group ("headers" FILES ${PROJECT_HEADERS})
source_group ("shaders" FILES ${PROJECT_SHADERS})
source_group ("sources" FILES ${PROJECT_SOURCES})
source_group ("vendors" FILES ${VENDORS_SOURCES})

add_executable(OpenGl_Base
        ${PRJ_SRC}
        ${PRJ_HEADERS}
        ${PRJ_SHADERS}
        ${EXTERNAL_SRC}
        src/model.h src/model.cpp)

target_link_libraries(OpenGl_Base
        opengl32
        glfw
        ${GLFW_LIBRARIES}
        ${GLAD_LIBRARIES}
        assimp
        )

set_target_properties (${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})