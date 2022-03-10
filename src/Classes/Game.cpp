#include "../Headers/Game.h"
#include "../Constants.h"

float playerX = 0.f;
float playerY = 0.f;

// Callback Declarations

void windowSizeCallback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);

// Functions

const GLuint LoadTexture2D(const char* path);

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
    // Positions        // Texture Coords
    -0.5f,  0.5f, 0.f,  0.f, 0.f, // Top Left
     0.5f,  0.5f, 0.f,  1.f, 0.f, // Top Right
    -0.5f, -0.5f, 0.f,  0.f, 1.f, // Bottom Left
     0.5f, -0.5f, 0.f,  1.f, 1.f  // Bottom Right
  };

  unsigned int indices[] = {
    0, 1, 2,
    1, 2, 3
  };

  this->VAO1 = new VAO();
  VAO1->Bind();

  this->VBO1 = new VBO(vertices, sizeof(vertices));
  this->EBO1 = new EBO(indices, sizeof(indices));

  this->VAO1->LinkAttrib(*this->VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
  this->VAO1->LinkAttrib(*this->VBO1, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

  this->VAO1->Unbind();
  this->VBO1->Unbind();
  this->EBO1->Unbind();

  // Binding Texture
  this->textureID = LoadTexture2D("src/Assets/Textures/sus.png");
  this->mainShader->Activate();
  glUniform1i(glGetUniformLocation(this->mainShader->ID, "sampTexture"), 0);
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
  // Clearing the Window
  glClearColor(0.2f, 0.3f, 0.4f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT);

  // Binding Texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, this->textureID);

  // Binding VAO
  this->mainShader->Activate();
  VAO1->Bind();

  // Handling Movement
  glm::mat4 modelMatrix(1.f);
  glm::mat4 viewMat(1.f);

  viewMat = glm::translate(viewMat, glm::vec3(playerX, playerY, 0));  

  glUniformMatrix4fv(glGetUniformLocation(this->mainShader->ID, "mTransform"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
  glUniformMatrix4fv(glGetUniformLocation(this->mainShader->ID, "vTransform"), 1, GL_FALSE, glm::value_ptr(viewMat));

  // Drawing Triangles
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  // Unbinding
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindVertexArray(0);

  // Swapping Buffers
  glfwSwapBuffers(this->window);
}

void Game::run()
{
  while (!glfwWindowShouldClose(this->window))
  {
    glfwPollEvents();
    this->render();
  }
}

// Callback Definitions

void windowSizeCallback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_W) playerY -= 0.1f;
  else if (key == GLFW_KEY_S) playerY += 0.1f;
  else if (key == GLFW_KEY_A) playerX += 0.1f;
  else if (key == GLFW_KEY_D) playerX -= 0.1f;
}

void cursorPosCallback(GLFWwindow* window, double xPos, double yPos)
{

}

// Functions

const GLuint LoadTexture2D(const char* path)
{
  // Creating Texture
  GLuint textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  
  // Texture Parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

  // Texture Filtering
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Loading Texture from a File
  int width, height, channels;
  unsigned char* data = stbi_load(path, &width, &height, &channels, 0);

  // Error Checking
  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else {
    std::cout << "ERROR::GAME::CANT_LOAD_TEXTURE" << std::endl;
  }

  // Unbinding
  glBindTexture(GL_TEXTURE_2D, 0);
  stbi_image_free(data);

  return textureID;
}
