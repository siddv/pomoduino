#include <ButtonDebounce.h>
#include <Adafruit_NeoPixel.h>
#define BUTTON_PIN 5
#define LED_PIN    6
#define LED_COUNT  24
#define SECOND     1000
#define MINUTE     SECOND * 60

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
ButtonDebounce button(BUTTON_PIN, 250);

bool pomodoring = false;

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(255);

  button.setCallback(onButtonChange);
}

void onButtonChange(const int state) {
  pomodoring = !pomodoring;
}

void setPomoColour(uint32_t colour) {
  for(int i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, colour);
  }
  strip.show();
}

void loop() {
  button.update();
  while (pomodoring == false) {
    setPomoColour(strip.Color(50, 25, 0));
    strip.show();
    button.update();
  }
  
  while(pomodoring == true) {
    setPomoColour(strip.Color(255, 0, 0));
    strip.show();
    pomodoring = true;
    for(int i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(15, 0, 0));
      strip.show();
      button.update();
      delay(SECOND);
    }
    setPomoColour(strip.Color(0, 100, 0));
    delay(SECOND * 5);
    pomodoring = false;
  }
}
