#ifndef EBO_H
#define EBO_H

#include "../Headers.h"

class EBO
{
  private:
    GLuint ID;

  public:
    // Constructor and Destructor
    EBO(GLuint* vertices, GLsizeiptr size);
    virtual ~EBO();

    // Functions
    void Bind();
    void Unbind();
    void Delete();
};

#endif // EBO_H
