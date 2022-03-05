#include "../Headers/Shader.h"

// Non-Member Functions

std::string getFileContents(const char* fileName)
{
  std::ifstream in(fileName, std::ios::binary);
  if (in) {
    std::string contents;

    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();

    return contents;
  }

  throw errno;
}

// Constructor and Destructor

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
  std::string vertexCode = getFileContents(vertexFile);
  std::string fragmentCode = getFileContents(fragmentFile);

  const char* vertexSource = vertexCode.c_str();
  const char* fragmentSource = fragmentCode.c_str();

  // Creating Vertex Shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);

  // Creating Fragment Shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);

  // Linking Shaders
  this->ID = glCreateProgram();
  glAttachShader(this->ID, vertexShader);
  glAttachShader(this->ID, fragmentShader);
  glLinkProgram(this->ID);

  // Deleting Shaders
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

Shader::~Shader()
{

}

// Functions

void Shader::Activate()
{
  glUseProgram(this->ID);
}

void Shader::Delete()
{
  glDeleteProgram(this->ID);
}
