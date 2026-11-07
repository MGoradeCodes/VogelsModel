#include <iostream>
#include <glad/gl.h>
#include <vector>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
#include <VAO.h>
#include <VBO.h>
#include <ShaderProgram.h>
#include <glad/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using std::vector;

float zoomScale = 1.0f; 
float centerX = 360.0f; 
float centerY = 360.0f;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    int displayWidth = 720;
    int displayHeight = 720;

    vector<float> x;
    vector<float> y;

    GLFWwindow* window = glfwCreateWindow(displayWidth, displayHeight, "Hello World", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    glfwSetScrollCallback(window, scroll_callback);

    float goldenAngle = 360 * (1 - 1/1.61803398875); 

    for(int i = 0; i < 600; ++i) {
        float theta = glm::radians(goldenAngle * i);

        float r = sqrt(i) * 8;
        x.push_back(static_cast<float>(centerX + r * cos(theta)));
        y.push_back(static_cast<float>(centerY + r * sin(theta)));
    }

    vector<float> vertices;

    for(int i = 0; i < x.size(); ++i) {
        vertices.push_back(x[i]);
        
        vertices.push_back(y[i]);

        vertices.push_back(1.0f);
        vertices.push_back(1.0f);
        vertices.push_back(0.0f);
    }

    VAO VAO1;
    VAO1.Bind();
    VBO VBO1 (vertices.data(), vertices.size() * sizeof(float));

    ShaderProgram shaderProgram ("../shaders/default.vert", "../shaders/default.frag");

    VAO1.LinkAttribs(VBO1, 0, 2, GL_FLOAT, 5 * sizeof(float), nullptr);
    VAO1.LinkAttribs(VBO1, 1, 3, GL_FLOAT,5 * sizeof(float), (void*)(2 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();

    GLsizeiptr vertexCount = static_cast<GLsizeiptr>(vertices.size() / 5);

    glfwMakeContextCurrent(window);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        shaderProgram.Activate();
        glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
        glm::mat4 viewTransform = glm::mat4(1.0f);
        viewTransform = glm::translate(viewTransform, glm::vec3(centerX, centerY, 0.0f));
        viewTransform = glm::scale(viewTransform, glm::vec3(zoomScale, zoomScale, 1.0f));
        viewTransform = glm::translate(viewTransform, glm::vec3(-centerX, -centerY, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "viewTransform"), 1, GL_FALSE, glm::value_ptr(viewTransform));
        VAO1.Bind();
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_POINTS, 0, vertexCount);
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    VAO1.Delete();
    VBO1.Delete();
    shaderProgram.Delete();
    glfwTerminate();
    return 0;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (yoffset > 0) {
        zoomScale *= 1.1f; 
    } else if (yoffset < 0) {
        zoomScale /= 1.1f; 
    }

    if (zoomScale < 0.1f)  zoomScale = 0.1f;
    if (zoomScale > 10.0f) zoomScale = 10.0f;
}