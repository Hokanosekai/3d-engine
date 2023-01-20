#include "shader_program.h"
#include <SDL2/SDL_opengl.h>
#include <stdlib.h>

ShaderProgram* shader_program_init(const char* vertex_shader_path, const char* fragment_shader_path)
{
  ShaderProgram* tmp = malloc(sizeof(ShaderProgram));
  if (tmp == NULL) return NULL;

  tmp->mprogram_id = glCreateProgram();
  shader_program_attach(vertex_shader_path, SHADER_PROGRAM_VERTEX);
  shader_program_attach(fragment_shader_path, SHADER_PROGRAM_FRAGMENT);

  shader_program_link(tmp);

  return tmp;
}

void shader_program_destroy(ShaderProgram *shader_program)
{
  for (GLuint i = 0; i < 2; i++)
  {
    glDetachShader(shader_program->mprogram_id, shader_program->attached_shaders[i]);
    glDeleteShader(shader_program->attached_shaders[i]);
  }
  glDeleteProgram(shader_program->mprogram_id);
}

void shader_program_set_uniform_buffer_slot(const char *name, GLuint slot)
{

}

void shader_program_attach(const char *file_path, const ShaderType type)
{
  
}
