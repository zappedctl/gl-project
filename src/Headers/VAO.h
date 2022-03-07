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

    void LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    void Bind();
    void Unbind();
    void Delete();
};

#endif // VAO_H
