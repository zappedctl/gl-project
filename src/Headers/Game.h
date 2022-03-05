#ifndef GAME_H
#define GAME_H

#include "../Headers.h"

class Game
{
  private:
    GLFWwindow* window;

    // Initializers
    void initWindow();
    void initCallbacks();

  public:
    // Constructor and Destructor
    Game();
    virtual ~Game();

    // Functions
    void render();
    void run();
};

#endif // GAME_H
