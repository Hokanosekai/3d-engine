#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <SDL2/SDL_opengl.h>

typedef enum {
  SHADER_PROGRAM_VERTEX,
  SHADER_PROGRAM_FRAGMENT
} ShaderType;

typedef struct {
  GLuint mprogram_id;
  GLuint attached_shaders[2];
} ShaderProgram;

/**
 * @brief Initializes the shader program.
 * @param vertex_shader_path The path to the vertex shader.
 * @param fragment_shader_path The path to the fragment shader.
 * @return 0 if success, -1 otherwise.
 */
ShaderProgram* shader_program_init(const char* vertex_shader_path, const char* fragment_shader_path);

/**
 * @brief Destroys the shader program.
 * @param shader_program The shader program.
 */
void shader_program_destroy(ShaderProgram* shader_program);

void shader_program_set_uniform_buffer_slot(const char* name, GLuint slot);

void shader_program_attach(const char* file_path, const ShaderType type);

void shader_program_link();

/**
 * @brief Get the shader program.
 * @param shader_program The shader program.
 * @return The shader program.
 */
GLuint shader_program_get_program(ShaderProgram* shader_program);

#endif // SHADER_PROGRAM_H
