#include "../Headers/Game.h"

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

void Game::initCallbacks()
{
  glfwSetKeyCallback(this->window, keyCallback);
  glfwSetCursorPosCallback(this->window, cursorPosCallback);
}

// Constructor and Destructor

Game::Game()
{
  this->initWindow();
  this->initCallbacks();
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

// Callback Definitions

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_A)
  {
    std::cout << "You've pressed key A!" << std::endl;
  }
}

void cursorPosCallback(GLFWwindow* window, double xPos, double yPos)
{
  std::cout << xPos << ", " << yPos << std::endl;
}
