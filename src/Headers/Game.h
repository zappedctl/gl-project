#ifndef GAME_H
#define GAME_H

#include "../Headers.h"

class Game
{
  private:
    GLFWwindow* window;

  public:
    // Constructor and Destructor
    Game();
    virtual ~Game();
};

#endif // GAME_H
