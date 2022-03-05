#include "../Headers/Game.h"

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
    800,
    600,
    "GLFW",
    NULL,
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

// Constructor and Destructor

Game::Game()
{
  this->initWindow();
}

Game::~Game()
{

}

// Functions

void Game::render()
{
  glClearColor(.2f, .3f, .4f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT);
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
