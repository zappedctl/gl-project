#ifndef SHADER_H
#define SHADER_H

#include "../Headers.h"

class Shader
{
  public:
    GLuint ID;

    // Constructor and Destructor
    Shader(const char* vertexFile, const char* fragmentFile);
    virtual ~Shader();

    // Functions
    void Activate();
    void Delete();
};

#endif // SHADER_H
