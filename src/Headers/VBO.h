#ifndef VBO_H
#define VBO_H

#include "../Headers.h"

class VBO
{
  private:
    GLuint ID;

  public:
    // Constructor and Destructor
    VBO(GLfloat* vertices, GLsizeiptr size);
    virtual ~VBO();

    // Functions
    void Bind();
    void Unbind();
    void Delete();
};

#endif // VBO_H
