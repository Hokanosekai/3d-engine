#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "timer.h"
#include "window.h"
#include "config.h"
#include "log.h"

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


  LOG_INFO("Starting main loop");
  timer_start(timer);

  while (true) {
    timer_start(timer);
    delta_time = timer_compute_delta_time(timer);
    
    window_update_fps(window, delta_time);
    window_clear(window);

    window_swap_buffers(window);

    timer_delay(timer);
  }

  timer_destroy(timer);
  window_destroy(window);
  log_destroy();

  return EXIT_SUCCESS;
}
