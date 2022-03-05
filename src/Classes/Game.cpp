#include "../Headers/Game.h"
#include "../Constants.h"

// Shaders

const char* vertexShaderSource =
  "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main()\n"
  "{\n"
  " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
  "}\0";

const char* fragmentShaderSource =
  "#version 330 core\n"
  "out vec4 fColor;\n"
  "void main()\n"
  "{\n"
  " fColor = vec4(1.f, 0.f, 0.f, 1.0f);\n"
  "}\0";

// Callback Declarations

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);

// Initializers

void Game::initWindow()
{
  if (!glfwInit())
  {
    std::cout << "Failed to initialize GLFW." << std::endl;
  }

  // Window Hints
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a GLFW Window
  this->window = glfwCreateWindow(
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    WINDOW_TITLE,
    WINDOW_FULLSCREEN ? glfwGetPrimaryMonitor() : NULL,
    NULL
  );

  // Error checking for GLFW Window
  if (this->window == NULL)
  {
    std::cout << "Failed to initialize GLFW Window" << std::endl;
    glfwTerminate();
  }
  glfwMakeContextCurrent(this->window);

  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    std::cout << "Failed to initialize GLEW." << std::endl;
    glfwTerminate();
  }
}

void Game::initCallbacks()
{
  glfwSetKeyCallback(this->window, keyCallback);
  glfwSetCursorPosCallback(this->window, cursorPosCallback);
}

void Game::initObjects()
{
  float vertices[] = {
    -0.5f, -0.5f, 0.f,
    0.5f, -0.5f, 0.f,
    0.f, 0.5f, 0.f
  };

  this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(this->vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(this->vertexShader);

  this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(this->fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(this->fragmentShader);

  glGenBuffers(1, &this->VBO);
  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glGenVertexArrays(1, &this->VAO);
  glBindVertexArray(this->VAO);
  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  this->shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, this->vertexShader);
  glAttachShader(shaderProgram, this->fragmentShader);
  glLinkProgram(this->shaderProgram);

  glUseProgram(this->shaderProgram);
  glDeleteShader(this->vertexShader);
  glDeleteShader(this->fragmentShader);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
}

// Construtor and Destructor

Game::Game()
{
  this->initWindow();
  this->initCallbacks();
  this->initObjects();
}

Game::~Game()
{

}

// Functions

void Game::render()
{
  glClearColor(0.2f, 0.3f, 0.4f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(this->shaderProgram);
  glBindVertexArray(this->VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  glfwSwapBuffers(this->window);
}

void Game::run()
{
  while (!glfwWindowShouldClose(this->window))
  {
    this->render();
    glfwPollEvents();
  }
}

// Callback Definitions

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}

void cursorPosCallback(GLFWwindow* window, double xPos, double yPos)
{

}

