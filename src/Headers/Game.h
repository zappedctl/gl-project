#ifndef GAME_H
#define GAME_H

#include "../Headers.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Game
{
  private:
    GLFWwindow* window;

    Shader* mainShader;
    GLuint textureID;

    // OpenGL Objects
    VAO* VAO1;
    VBO* VBO1;
    EBO* EBO1;

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
