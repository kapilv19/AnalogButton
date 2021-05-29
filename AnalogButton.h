#ifndef AnalogMultipleButton_h
#define AnalogMultipleButton_h

#include "Arduino.h"

#define DEFAULT_PIN_BUZZER -1
#define DEFAULT_ERROR_MARGIN 25
#define DEFAULT_WAIT_TIMEOUT 0
#define DEFAULT_KEYPRESS_DELAY 250
#define DEFAULT_ROUTINE_DELAY 500

class AnalogButton
{
  public:
    AnalogButton(int pin, int n, int* thresholds, 
                        int pin_buzzer = DEFAULT_PIN_BUZZER,
                        int error_margin = DEFAULT_ERROR_MARGIN);
    int getPressedButton();
    int waitForKey(bool required_keys[], long timeout = DEFAULT_WAIT_TIMEOUT,
                        int key_press_delay = DEFAULT_KEYPRESS_DELAY);
    int waitForKey(bool required_keys[], void (*routine_function)(), 
                        long routine_delay = DEFAULT_ROUTINE_DELAY,
                        long timeout = DEFAULT_WAIT_TIMEOUT,
                        int key_press_delay = DEFAULT_KEYPRESS_DELAY);
  private:
    void beep();
    int _pin;
    int _n;
    int* _thresholds;
    int _error_margin;
    bool _buzzer;
    int _pin_buzzer;
};

#endif
