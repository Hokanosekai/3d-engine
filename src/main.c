#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "timer.h"
#include "window.h"
#include "config.h"
#include "log.h"

Log* LOGGER = NULL;

int main(int argc, char *argv[])
{
  srand(time(NULL));
  
  int delta_time;
  
  // Initialize log
  if (log_init(LOGGER, LOG_LEVEL_DEBUG) == -1) {
    printf("[FATAL] >> log_init() failed");
    return EXIT_FAILURE;
  };

  Timer* timer = timer_init();
  if (timer == NULL) {
    LOG(LOG_LEVEL_FATAL, "timer_init() failed");
    return EXIT_FAILURE;
  }

  Window* window = window_init(WINDOW_X_POS, WINDOW_Y_POS, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false);  
  if (window == NULL) {
    LOG(LOG_LEVEL_FATAL, "window_init() failed");
    return EXIT_FAILURE;
  }  

  timer_start(timer);

  while (true) {
    timer_start(timer);
    delta_time = timer_compute_delta_time(timer);
    
    LOG(LOG_LEVEL_INFO, "Starting main loop");
    
    window_update_fps(window, delta_time);
    window_clear(window);

    window_swap_buffers(window);

    timer_delay(timer);
  }

  timer_destroy(timer);
  window_destroy(window);

  return EXIT_SUCCESS;
}
