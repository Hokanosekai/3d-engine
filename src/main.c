#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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

    if (keyboard_state_is_held(keyboard_state, SDL_SCANCODE_F)) {
      LOG_INFO("F key pressed");
    }

    window_clear(window);
    window_swap_buffers(window);

    timer_delay(timer);
  }

  timer_destroy(timer);
  window_destroy(window);
  log_destroy();

  return EXIT_SUCCESS;
}
