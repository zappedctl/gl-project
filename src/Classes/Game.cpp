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

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
    -0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f,  // Top Left
    0.5f, 0.5f, 0.f, 0.f, 1.f, 0.f,   // Top Right
    -0.5f, -0.5f, 0.f, 0.f, 0.f, 1.f, // Bottom Left
    0.5f, -0.5f, 0.f, 1.f, 1.f, 0.f   // Bottom Right
  };

  unsigned int indices[] = {
    0, 1, 2,
    1, 2, 3
  };

  this->VAO1 = new VAO();
  VAO1->Bind();

  this->VBO1 = new VBO(vertices, sizeof(vertices));
  this->EBO1 = new EBO(indices, sizeof(indices));

  this->VAO1->LinkAttrib(*this->VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
  this->VAO1->LinkAttrib(*this->VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

  this->VAO1->Unbind();
  this->VBO1->Unbind();
  this->EBO1->Unbind();
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
  VAO1->Delete();
  VBO1->Delete();
  EBO1->Delete();
  this->mainShader->Delete();
  
  delete this->VAO1;
  delete this->VBO1;
  delete this->EBO1;
  delete this->mainShader;
}

// Functions

void Game::render()
{
  glClearColor(0.2f, 0.3f, 0.4f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT);

  this->mainShader->Activate();
  VAO1->Bind();
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
