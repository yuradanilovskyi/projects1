#include <TimerOne.h>
const int led = LED_BUILTIN;
int size_clik = 0;

void fool(void) {
  static int count = 0;
  count++;
  if (count > 20) {
    Serial.println(size_clik);
    count = 0;
    size_clik = 0;
  }

}


void setup(void)
{
  Timer1.initialize(100000);
  Timer1.attachInterrupt(fool);
  Serial.begin(9600);
  const byte interruptPin = 2;
  volatile byte state = LOW;
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
}

void loop() {
}

void blink() {
  size_clik++;
}
