//
// Created by Andrew Graser on 4/18/2023.
//

#include "TestInstancedRender.h"
#include "renderer/VertexBufferLayout.h"
#include "GLFW/glfw3.h"

#define NUM_INSTANCES 10000
#define PI 3.141592653589793238

test::TestInstancedRender::TestInstancedRender() {
    float cubeVertices[24] = {
            -0.5, -0.5,  0.5, //0
            0.5, -0.5,  0.5, //1
            -0.5,  0.5,  0.5, //2
            0.5,  0.5,  0.5, //3
            -0.5, -0.5, -0.5, //4
            0.5, -0.5, -0.5, //5
            -0.5,  0.5, -0.5, //6
            0.5,  0.5, -0.5  //7
    };

    unsigned int cubeIndices[36] = {
            //Top
            2, 6, 7,
            2, 3, 7,

            //Bottom
            0, 4, 5,
            0, 1, 5,

            //Left
            0, 2, 6,
            0, 4, 6,

            //Right
            1, 3, 7,
            1, 5, 7,

            //Front
            0, 2, 3,
            0, 1, 3,

            //Back
            4, 6, 7,
            4, 5, 7
    };

    positions.resize(NUM_INSTANCES);

    for (unsigned int i = 0; i < NUM_INSTANCES; ++i) {
        positions[i] = glm::vec3(
                0.2f * i * cos(40 * PI * i / NUM_INSTANCES),
                0.2f * i * sin(40 * PI * i / NUM_INSTANCES),
                0.0f
        );
    }

    {
        cubeVA = std::make_unique<VertexArray>();
        cubeVB = std::make_unique<VertexBuffer>(cubeVertices, sizeof(cubeVertices));

        instanceVB = std::make_unique<VertexBuffer>(&positions[0], NUM_INSTANCES * sizeof(glm::vec3));

        cubeVA->Bind();

        cubeVB->Bind();
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), nullptr);

        instanceVB->Bind();
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, 3 * sizeof(float), nullptr);
        glVertexAttribDivisor(1, 1);


        cubeIB = std::make_unique<IndexBuffer>(cubeIndices, 36);
    }

    solidShader = std::make_unique<Shader>("../../src/shaders/SolidLit.vert", "../../src/shaders/SolidLit.frag");

    camera = std::make_unique<Camera>(glm::vec3(0.0f), 1280, 720);
}

test::TestInstancedRender::~TestInstancedRender() {

}

void test::TestInstancedRender::OnUpdate(float deltaTime, void *window) {
    GLFWwindow *w = (GLFWwindow *) window;

    //Camera Input
    if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS) {
        camera->Move(Forward, deltaTime);
    }
    if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS) {
        camera->Move(Backward, deltaTime);
    }
    if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS) {
        camera->Move(Left, deltaTime);
    }
    if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS) {
        camera->Move(Right, deltaTime);
    }

    //Mouse Input
    if (glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_MIDDLE)) {
        double mouseX, mouseY;
        glfwGetCursorPos(w, &mouseX, &mouseY);
        camera->Rotate((float) mouseX, (float) mouseY);
    }

    Test::OnUpdate(deltaTime, window);
}

void test::TestInstancedRender::OnRender(glm::vec2 windowSize) {

    {
        solidShader->Bind();
        solidShader->SetMat4("proj", camera->projection());
        solidShader->SetMat4("view", camera->view());

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.25f));

        solidShader->SetVec3("color", 1.0f, 0.0f, 0.0f);
        solidShader->SetMat4("model", model);

        Renderer::Draw(*solidShader, *cubeVA, *cubeIB, NUM_INSTANCES);
    }

    Test::OnRender(windowSize);
}

void test::TestInstancedRender::OnImGuiRender() {
    Test::OnImGuiRender();
}
