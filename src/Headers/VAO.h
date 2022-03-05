#ifndef VAO_H
#define VAO_H

#include "VBO.h"

class VAO
{
  private:
    GLuint ID;

  public:
    // Constructor and Destructor
    VAO();
    virtual ~VAO();

    void LinkVBO(VBO VBO, GLuint layout);
    void Bind();
    void Unbind();
    void Delete();
};

#endif // VAO_H
