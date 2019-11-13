#include <stdint.h>

#define PUSH_THE_BUTTON_SIZE 10

struct push_the_button_game {
  uint8_t leds[PUSH_THE_BUTTON_SIZE];
  uint8_t mappings[PUSH_THE_BUTTON_SIZE];
  long (*random)(long);
};

struct push_the_button_game push_the_button_new(long (*random)(long));

void push_the_button(struct push_the_button_game *game, uint8_t button);

void push_the_button_reset(struct push_the_button_game *game);

int push_the_button_win(struct push_the_button_game *game);
