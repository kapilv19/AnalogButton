#include "Arduino.h"
#include "AnalogButton.h"

AnalogButton::AnalogButton(int pin, int n, int* thresholds, int pin_buzzer, int error_margin) {
  pinMode(pin, INPUT);
  _pin = pin;
  _n = n;
  _thresholds =  thresholds;
  _error_margin = error_margin;
  if (pin_buzzer != DEFAULT_PIN_BUZZER) {
    _buzzer = true;
    _pin_buzzer = pin_buzzer;
  } else _buzzer = false;
}

void dummy() {}

void AnalogButton::beep() {
  if (!_buzzer) return;
  tone(_pin_buzzer, 1000);
  delay(100);
  noTone(_pin_buzzer);
}

int AnalogButton::getPressedButton() {
  int a = analogRead(_pin);
  for (int i = 0; i < _n; i++) {
    if (a <= _thresholds[i] + _error_margin && a >= _thresholds[i] - _error_margin) {
      beep();
      return _thresholds[i];
    }
  }
  return 0;
}

int AnalogButton::waitForKey(bool required_keys[],
                                     long timeout, int key_press_delay) {
  return waitForKey(required_keys, dummy, 1e9, timeout, key_press_delay);
}

int AnalogButton::waitForKey(bool required_keys[],
                                     void (*routine_function)(), long routine_delay,
                                     long timeout, int key_press_delay) {
  long strt = millis(), prev = strt, clk = strt;

  while (true)
  {
    if (millis() - clk > key_press_delay) {
      int pressed_button = getPressedButton();
      for (int i = 0; i < _n; i++) {
        if (required_keys[i] && pressed_button == _thresholds[i])  return _thresholds[i];
      }
      clk = millis();
    }

    if (millis() - prev > routine_delay)
    {
      (*routine_function)();
      prev = millis();
    }

    if (timeout != 0 && millis() - strt > timeout)
      return 0;

    delay(1);
  }

  return 0;
}
