#ifndef GAME_H
#define GAME_H

#include "../Headers.h"

class Game
{
  private:
    GLFWwindow* window;

    // Shaders
    unsigned int shaderProgram;
    unsigned int vertexShader;
    unsigned int fragmentShader;

    // OpenGL Objects
    unsigned int VBO;
    unsigned int EBO;
    unsigned int VAO;

    // Initializers
    void initWindow();
    void initCallbacks();
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
