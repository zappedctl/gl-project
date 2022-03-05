#ifndef GAME_H
#define GAME_H

#include "../Headers.h"

class Game
{
  private:
    GLFWwindow* window;

    unsigned int VBO;

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
