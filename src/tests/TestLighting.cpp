//
// Created by apgra on 4/9/2023.
//

#include "TestLighting.h"
#include "GLFW/glfw3.h"
#include "renderer/VertexBufferLayout.h"
#include <imgui.h>


test::TestLighting::TestLighting() {

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

    float planeVertices[48] = {
            // positions           // normals               // texcoords
            0.5, -0.5f,  0.5,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
            -0.5, -0.5f,  0.5,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
            -0.5, -0.5f, -0.5,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f,

            0.5, -0.5f,  0.5,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
            -0.5, -0.5f, -0.5,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
            0.5, -0.5f, -0.5,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f
    };


    {
        cubeVA = std::make_unique<VertexArray>();
        cubeVB = std::make_unique<VertexBuffer>(cubeVertices, sizeof(cubeVertices));

        VertexBufferLayout layout;
        layout.Push<float>(3);
        cubeVA->AddBuffer(*cubeVB, layout);

        cubeIB = std::make_unique<IndexBuffer>(cubeIndices, 36);
    }

    {
        planeVA = std::make_unique<VertexArray>();
        planeVB = std::make_unique<VertexBuffer>(planeVertices, sizeof(planeVertices));

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);
        layout.Push<float>(2);
        planeVA->AddBuffer(*planeVB, layout);
    }


    shader = std::make_unique<Shader>("../../src/shaders/TexturedLit.vert", "../../src/shaders/TexturedLit.frag");
    lightShader = std::make_unique<Shader>("../../src/shaders/SolidLit.vert", "../../src/shaders/SolidLit.frag");
    tex = std::make_unique<Texture2D>("../../resources/textures/wood.png");

    camera = std::make_unique<Camera>(glm::vec3(0.0f), 1280, 720);
}

test::TestLighting::~TestLighting() {

}

void test::TestLighting::OnUpdate(float deltaTime, void *window) {
    GLFWwindow* w = (GLFWwindow*)window;

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
    if(!cursorEnabled) {
        double mouseX, mouseY;
        glfwGetCursorPos(w, &mouseX, &mouseY);
        camera->Rotate((float) mouseX, (float) mouseY);
    }


    if(glfwGetKey(w, GLFW_KEY_SPACE) == GLFW_PRESS){
        GLint toggle = cursorEnabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL;
        glfwSetInputMode(w, GLFW_CURSOR, toggle);
        cursorEnabled = !cursorEnabled;
    }

    Test::OnUpdate(deltaTime, window);
}

void test::TestLighting::OnRender() {
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

    glm::mat4 proj = camera->projection();
    glm::mat4 view = camera->view();

    shader->Bind();
    shader->SetMat4("proj", proj);
    shader->SetMat4("view", view);

    tex->Bind();

    shader->SetVec3("viewPos", camera->position());
    shader->SetInt("gamma", false);

    shader->SetInt("numLights", lightPositions.size());

    shader->SetInt("texture_diffuse0", 0);

    for(int i = 0; i < lightPositions.size(); ++i){
        std::string index = std::to_string(i);
        shader->SetVec3(("lightPositions[" + index + "]"), lightPositions[i]);
        shader->SetVec3(("lightColors[" + index + "]"), lightColors[i]);
    }

    //Light Cubes
    for(int i = 0; i < lightPositions.size(); i++) {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), lightPositions[i]);

        lightShader->Bind();
        lightShader->SetMat4("model", transform);
        lightShader->SetVec3("color", lightColors[i]);

        renderer.Draw(*lightShader, *cubeVA, *cubeIB);
    }

    //Plane
    {

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 0.0f));
        transform = glm::scale(transform, glm::vec3(20.0f, 1.0f, 20.0f));

        shader->Bind();
        shader->SetMat4("model", transform);

        renderer.Draw(*shader, *planeVA, 6);
    }
    tex->Unbind();

    Test::OnRender();
}

void test::TestLighting::OnImGuiRender() {
    if(ImGui::Button("Create Light")){
        lightPositions.emplace_back(0.0f, 1.0f, 0.0f);
        lightColors.emplace_back(0.1f, 0.1f, 0.1f);
    }

    for(int i = 0; i < lightPositions.size(); i++){
        if(ImGui::CollapsingHeader(("Light #" + std::to_string(i)).c_str())){
            ImGui::SliderFloat3("Position", &lightPositions[i].x, -10.0f, 10.0f);
            ImGui::SliderFloat3("Color", &lightColors[i].x, 0.0f, 1.0f);
        }
    }

    Test::OnImGuiRender();
}
