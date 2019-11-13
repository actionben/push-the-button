#include "game.h"

struct push_the_button_game push_the_button_new(long (*random)(long)) {
  struct push_the_button_game game;
  game.random = random;
  for (int i = 0; i < PUSH_THE_BUTTON_SIZE; i++) {
    game.leds[i] = 0;
    game.mappings[i] = i;
  }
  push_the_button_reset(&game);
  return game;
}

static void toggle_by_distance(struct push_the_button_game *game,
                               uint8_t button, uint8_t distance) {
  uint8_t up = (button + distance) % PUSH_THE_BUTTON_SIZE;
  uint8_t down =
      (button + PUSH_THE_BUTTON_SIZE - distance) % PUSH_THE_BUTTON_SIZE;
  game->leds[up] = !game->leds[up];
  if (up != down) {
    game->leds[down] = !game->leds[down];
  }
}

void push_the_button(struct push_the_button_game *game, uint8_t button) {
  switch (game->mappings[button]) {
  case 0:
    for (int i = 0; i < PUSH_THE_BUTTON_SIZE; i++) {
      game->leds[i] = 0;
    };
    break;
  case 1:
    for (int i = 0; i < PUSH_THE_BUTTON_SIZE; i++) {
      if (button != i) {
        game->leds[i] = !game->leds[i];
      }
    };
    break;
  case 2:
    toggle_by_distance(game, button, 0);
    break;
  case 3:
    for (int i = 1; i < PUSH_THE_BUTTON_SIZE; i += 2) {
      game->leds[i] = 1;
    };
    break;
  case 4:
    for (int i = 1; i < PUSH_THE_BUTTON_SIZE; i += 2) {
      game->leds[i] = 0;
    };
    break;
  case 5:
    for (int i = 0; i < PUSH_THE_BUTTON_SIZE; i += 2) {
      game->leds[i] = 1;
    };
    break;
  case 6:
    for (int i = 0; i < PUSH_THE_BUTTON_SIZE; i += 2) {
      game->leds[i] = 0;
    };
    break;
  case 7:
    toggle_by_distance(game, button, 1);
    break;
  case 8:
    toggle_by_distance(game, button, 2);
    break;
  case 9:
    toggle_by_distance(game, button, 3);
    break;
  }
}

void push_the_button_reset(struct push_the_button_game *game) {
  for (int i = 0; i < PUSH_THE_BUTTON_SIZE; i++) {
    game->leds[i] = 0;
  };

  for (int i = 0; i < PUSH_THE_BUTTON_SIZE; i++) {
    int currentMapping = game->mappings[i];
    int randomSwap = game->random(PUSH_THE_BUTTON_SIZE - i) + i;
    game->mappings[i] = game->mappings[randomSwap];
    game->mappings[randomSwap] = currentMapping;
  }
}

int push_the_button_win(struct push_the_button_game *game) {
  for (int i = 0; i < PUSH_THE_BUTTON_SIZE; i++) {
    if (game->leds[i] == 0) {
      return 0;
    }
  };
  return 1;
}
