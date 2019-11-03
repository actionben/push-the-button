#include "game.h"

uint8_t BUTTON_PINS[] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4};
int last_button_states[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};

uint8_t RESET_PIN = 3;
int last_reset_state = LOW;
struct push_the_button_game game;

void setup() {
  pinMode(RESET_PIN, INPUT);
  game = push_the_button_new(&random);
}

void loop() {
  for (int i = 0; i < sizeof(BUTTON_PINS); i++) {
    pinMode(BUTTON_PINS[i], INPUT);
    int buttonState = digitalRead(BUTTON_PINS[i]);
    if (buttonState == HIGH && last_button_states[i] == LOW) {
      push_the_button(&game, i);
    }
    last_button_states[i] = buttonState;
    pinMode(BUTTON_PINS[i], OUTPUT);
    digitalWrite(BUTTON_PINS[i], game.leds[i] == 0 ? LOW : HIGH);
  }

  int resetState = digitalRead(RESET_PIN);
  if (resetState == HIGH && last_reset_state == LOW) {
    push_the_button_reset(&game);
  }
  last_reset_state = resetState;

  delay(50);
}
