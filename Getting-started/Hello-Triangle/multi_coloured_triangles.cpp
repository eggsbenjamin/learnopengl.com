/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  27/06/19 18:48:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ben Davies (eggsbenjamin), eggs.benjamin@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream> 
#include <glad/glad.h>
#include <GLFW/glfw3.h>

std::string readFile(const char* path) {
  std::ifstream t(path);
  std::stringstream buffer;
  buffer << t.rdbuf();
  t.close();

  return buffer.str();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
      (void)window; // unused var 
      glViewport(0, 0, width, height);
} 

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return -1;
    }

    glfwMakeContextCurrent(window);
  
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "Failed to initialize GLAD" << std::endl;
      return -1;
    } 

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertexShaderSource = readFile("./glsl/vertex.glsl");
    const char* t = vertexShaderSource.c_str();
    
    glShaderSource(vertexShader, 1, &t, NULL);
    glCompileShader(vertexShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success) {
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
      return 1;
    }

    unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentShaderOrangeSource = readFile("./glsl/fragment_orange.glsl");
    t = fragmentShaderOrangeSource.c_str();

    glShaderSource(fragmentShaderOrange, 1, &t, NULL);
    glCompileShader(fragmentShaderOrange);

    glGetShaderiv(fragmentShaderOrange, GL_COMPILE_STATUS, &success);

    if(!success) {
      glGetShaderInfoLog(fragmentShaderOrange, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
      return 1;
    }

    unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentShaderYellowSource = readFile("./glsl/fragment_yellow.glsl");
    t = fragmentShaderYellowSource.c_str();

    glShaderSource(fragmentShaderYellow, 1, &t, NULL);
    glCompileShader(fragmentShaderYellow);

    glGetShaderiv(fragmentShaderYellow, GL_COMPILE_STATUS, &success);

    if(!success) {
      glGetShaderInfoLog(fragmentShaderYellow, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
      return 1;
    }

    unsigned int shaderProgramOrange = glCreateProgram();
    glAttachShader(shaderProgramOrange, vertexShader);
    glAttachShader(shaderProgramOrange, fragmentShaderOrange);
    glLinkProgram(shaderProgramOrange);

    glGetProgramiv(shaderProgramOrange, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgramOrange, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return 1;
    }

    unsigned int shaderProgramYellow = glCreateProgram();
    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);

    glGetProgramiv(shaderProgramYellow, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgramYellow, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return 1;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderOrange); 
    glDeleteShader(fragmentShaderYellow); 

    // set up VBO/VAO

    float verticesLeft[] = {
      -1.0f, -0.5f, 0.0f, // bottom left
       0.0f, -0.5f, 0.0f, // bottom right
      -0.5f,  0.5f, 0.0f, // top
    };

    float verticesRight[] = {
       0.0f, -0.5f, 0.0f, // bottom left
       1.0f, -0.5f, 0.0f, // bottom right
       0.5f,  0.5f, 0.0f, // top
    };

    GLuint VBOs[2], VAOs[2];

    glGenBuffers(2, VBOs);
    glGenVertexArrays(2, VAOs);

    // set up left triangle 
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLeft), verticesLeft, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // set up right triangle 
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLeft), verticesRight, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while(!glfwWindowShouldClose(window)) {
      processInput(window);

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // draw left triangle
      glUseProgram(shaderProgramOrange);
      glBindVertexArray(VAOs[0]);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      // draw right triangle
      glUseProgram(shaderProgramYellow);
      glBindVertexArray(VAOs[1]);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      glfwSwapBuffers(window);
      glfwPollEvents();     
    }

    glDeleteVertexArrays(1, VAOs);
    glDeleteBuffers(1, VBOs);
    glfwTerminate();

    return 0;
}
