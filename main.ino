#include <TimerOne.h>
#include <OLED_I2C.h>

OLED  myOLED(SDA, SCL);

#include <HCSR04.h>

HCSR04 hc(5,6);

#include "DHT.h"

DHT dht;

bool button_state_pre = false;
bool display_state = false;

bool led_state = false;
bool led_state_pre = false;
int led_count = 0;

float humidity = 0;
float temperature = 0;


extern uint8_t BigNumbers[];


const int led = LED_BUILTIN;
int size_clik = 0;
int speed_bike = 0;
int range_bike = 0;



void fool(void) {
  static int count = 0;
  count++;
  if (count > 20) {
    speed_bike = size_clik;
    range_bike += size_clik;
    count = 0;
    size_clik = 0;
  }

  if (led_state == HIGH) {

      if (digitalRead(10) == LOW)
          led_count++;
      else 
          led_count = 0;

      if (led_count > 50) led_state = false;
    
    } else {
      
      
      if (digitalRead(10) == HIGH)
          led_count++;
      else 
          led_count = 0;
      
       if (led_count > 50) led_state = true;
    }

    digitalWrite(9, led_state);

  bool button_state = digitalRead(8);
  if (button_state == LOW) {
      if (button_state_pre == HIGH) 
        display_state = !display_state;
    }

  button_state_pre = digitalRead(8);

}


void setup(void)
{
  Timer1.initialize(100000);
  Timer1.attachInterrupt(fool);
  Serial.begin(9600);
  const byte interruptPin = 2;
  volatile byte state = LOW;
  
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, OUTPUT);
  pinMode(10, INPUT);
  pinMode(11, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);

  if (!myOLED.begin(SSD1306_128X64))
    while(1);   // In case the library failed to allocate enough RAM for the display buffer...
    
  myOLED.setFont(BigNumbers);


   dht.setup(3); // data pin 3
}

void loop() {

    

    myOLED.clrScr();
    humidity = dht.getHumidity();
    temperature = dht.getTemperature();
    
    if (display_state == false) {
      myOLED.printNumI(speed_bike, 16, 26, 0, '1');
      myOLED.printNumF((float)range_bike/1000,  2, 60, 26);
    
      if(speed_bike>9){
        myOLED.drawRect(8, 18, 124, 58);
        myOLED.drawRect(10, 20, 50, 56);
        myOLED.drawRect(50, 20, 122, 56);
      } else {
        myOLED.drawRect(8, 18, 124, 58);
        myOLED.drawRect(10, 20, 35, 56);
        myOLED.drawRect(35, 20, 122, 56);
      }
    } else {
      
      myOLED.printNumF(humidity, 1, 64, 26);
      myOLED.printNumF(temperature, 1, 0, 26);
      
      }
    int distance = hc.dist();

    if (distance < 150 ) {
        analogWrite(11, 125);
          //digitalWrite(9, HIGH);
    }
    else if (distance > 100 ) {
      analogWrite(11, 0);
      }
      
    myOLED.update();
    delay(100);
}

void blink() {
  size_clik++;
}
