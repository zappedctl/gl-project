#include "../Headers/Game.h"
#include "../Constants.h"

// Callback Declarations

void windowSizeCallback(GLFWwindow* window, int width, int height);
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

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Game::initCallbacks()
{
  glfwSetWindowSizeCallback(this->window, windowSizeCallback);
  glfwSetKeyCallback(this->window, keyCallback);
  glfwSetCursorPosCallback(this->window, cursorPosCallback);
}

void Game::initShaders()
{
  this->mainShader = new Shader("src/Shaders/default.vert", "src/Shaders/default.frag");
}

void Game::initObjects()
{
  float vertices[] = {
    -0.5f, 0.5f, 0.f,  // Top Left
    0.5f, 0.5f, 0.f,   // Top Right
    -0.5f, -0.5f, 0.f, // Bottom Left
    0.5f, -0.5f, 0.f   // Bottom Right
  };

  unsigned int indices[] = {
    0, 1, 2,
    1, 2, 3
  };


  glGenVertexArrays(1, &this->VAO);
  glGenBuffers(1, &this->VBO);
  glGenBuffers(1, &this->EBO);

  glBindVertexArray(this->VAO);
  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // Unbinding
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

// Construtor and Destructor

Game::Game()
{
  this->initWindow();
  this->initCallbacks();
  this->initShaders();
  this->initObjects();
}

Game::~Game()
{
  this->mainShader->Delete();
  
  delete this->mainShader;
}

// Functions

void Game::render()
{
  glClearColor(0.2f, 0.3f, 0.4f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT);

  this->mainShader->Activate();
  glBindVertexArray(this->VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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


void windowSizeCallback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}

void cursorPosCallback(GLFWwindow* window, double xPos, double yPos)
{

}
