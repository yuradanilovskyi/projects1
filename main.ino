#include <TimerOne.h>
#include <OLED_I2C.h>


OLED  myOLED(SDA, SCL);

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

  if(!myOLED.begin(SSD1306_128X64))
    while(1);   // In case the library failed to allocate enough RAM for the display buffer...
    
  myOLED.setFont(BigNumbers);

}

void loop() {
    myOLED.clrScr();
    myOLED.printNumI(speed_bike, 16, 26, 0, '1');
    myOLED.printNumF((float)range_bike/1000,  2, 64, 26);

    if(speed_bike>9){
      myOLED.drawRect(8, 18, 52, 58);
      myOLED.drawRect(10, 20, 50, 56);
    } else {
      myOLED.drawRect(8, 18, 37, 58);
      myOLED.drawRect(10, 20, 35, 56);
    }
    //myOLED.print("m/s", CENTER, 16);
    myOLED.update();
    delay(100);
 
}

void blink() {
  size_clik++;
}
