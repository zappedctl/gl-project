#ifndef GAME_H
#define GAME_H

#include "../Headers.h"
#include "Shader.h"

class Game
{
  private:
    GLFWwindow* window;

    Shader* mainShader;

    // OpenGL Objects
    unsigned int VBO;
    unsigned int EBO;
    unsigned int VAO;

    // Initializers
    void initWindow();
    void initCallbacks();
    void initShaders();
    void initObjects();

  public:
    // Constructor and Destructor
    Game();
    virtual ~Game();

    // Functions
    void render();
    void run();
};

#endif // GAME_H
