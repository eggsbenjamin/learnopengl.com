#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream> 
#include <math.h>
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

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentShaderSource = readFile("./glsl/fragment.glsl");
    t = fragmentShaderSource.c_str();

    glShaderSource(fragmentShader, 1, &t, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success) {
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
      return 1;
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return 1;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); 

    // set up VBO/VAO

    float vertices[] = {
      -0.5f, -0.5f, 0.0f,
       0.5f, -0.5f, 0.0f,
       0.0f,  0.5f, 0.0f
    };
    unsigned int VBO, VAO;

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    while(!glfwWindowShouldClose(window)) {
      processInput(window);

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      glUseProgram(shaderProgram);

      float timeValue = glfwGetTime();
      float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
      int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColour");
      glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

      glBindVertexArray(VAO);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      glfwSwapBuffers(window);
      glfwPollEvents();     
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();

    return 0;
}
