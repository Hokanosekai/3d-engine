#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "engine/utils/log.h"
#include "engine/input/input_manager.h"
#include "engine/utils/timer.h"
#include "engine/window.h"
#include "engine/config.h"

int main(int argc, char *argv[])
{
  srand(time(NULL));
  
  int delta_time;
  
  // Initialize log
  if (log_init(LOG_LEVEL_DEBUG) == -1) {
    printf("[FATAL] >> log_init() failed");
    return EXIT_FAILURE;
  };

  Timer* timer = timer_init();
  if (timer == NULL) {
    LOG_FATAL("timer_init() failed");
    return EXIT_FAILURE;
  }

  Window* window = window_init(WINDOW_X_POS, WINDOW_Y_POS, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false);  
  if (window == NULL) {
    LOG_FATAL("window_init() failed");
    return EXIT_FAILURE;
  }  

  InputManager* input_manager = input_manager_init();
  if (input_manager == NULL) {
    LOG_FATAL("input_manager_init() failed");
    return EXIT_FAILURE;
  }

  LOG_INFO("Starting main loop");
  timer_start(timer);

  // Define the vertex data of the cube
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f
};

  // Create a vertex buffer object (VBO)
GLuint VBO;
glGenBuffers(1, &VBO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Create a vertex array object (VAO)
GLuint VAO;
glGenVertexArrays(1, &VAO);
glBindVertexArray(VAO);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
glEnableVertexAttribArray(0);

  // Create a vertex shader
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
    "}\0";
GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);

// Create a fragment shader
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";
GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
glCompileShader(fragmentShader);

  // Link the shaders to a program
GLuint shaderProgram = glCreateProgram();
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);
glLinkProgram(shaderProgram);

  bool is_running = true;

  while (is_running) {
    timer_start(timer);
    delta_time = timer_compute_delta_time(timer);
    
    window_update_fps(window, delta_time);
    
    input_manager_prepare_update(input_manager);
    is_running = input_manager_poll_inputs(input_manager);
    KeyboardState* keyboard_state = input_manager_get_keyboard_state(input_manager);

    if (keyboard_state_get_key_status(keyboard_state, SDL_SCANCODE_ESCAPE) == KEY_JUST_PRESSED) {
      LOG_INFO("Escape key pressed");
      is_running = false;
    }

    if (keyboard_state_is_just_pressed(keyboard_state, SDL_SCANCODE_F)) {
      LOG_INFO("F key pressed");
    }

    window_clear(window);

    // Use the program
    glUseProgram(shaderProgram);

    // Render the cube
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    window_swap_buffers(window);

    timer_delay(timer);
  }

  timer_destroy(timer);
  window_destroy(window);
  log_destroy();

  return EXIT_SUCCESS;
}
