#include <Adafruit_NeoPixel.h>

#define RING_PIN  6
#define RING_LED_COUNT  24

#define POT_PIN 0

#define BUTTON_PIN_SINGLE_COLOR  2
#define BUTTON_PIN_COLOR_WIPE 4
#define BUTTON_PIN_COLOR_CHASE  7
#define BUTTON_PIN_RAINBOW  8
#define BUTTON_PIN_RAINBOW_CHASE  12

#define BUTTON_PIN_WHITE  13
#define BUTTON_PIN_RED  11
#define BUTTON_PIN_BLUE 10
#define BUTTON_PIN_GREEN  9

int RED = 255;
int BLUE = 255;
int GREEN = 255;

int brightness = 55;

Adafruit_NeoPixel ring(RING_LED_COUNT, RING_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN_SINGLE_COLOR, INPUT_PULLUP);
  pinMode(BUTTON_PIN_COLOR_WIPE, INPUT_PULLUP);
  pinMode(BUTTON_PIN_COLOR_CHASE, INPUT_PULLUP);
  pinMode(BUTTON_PIN_RAINBOW, INPUT_PULLUP);
  pinMode(BUTTON_PIN_RAINBOW_CHASE, INPUT_PULLUP);

  pinMode(BUTTON_PIN_WHITE, INPUT_PULLUP);
  pinMode(BUTTON_PIN_RED, INPUT_PULLUP);
  pinMode(BUTTON_PIN_BLUE, INPUT_PULLUP);
  pinMode(BUTTON_PIN_GREEN, INPUT_PULLUP);

  pinMode(POT_PIN, INPUT);
  
  ring.begin();
  ring.show();
  //ring.setBrightness(75);
}

void loop() {
  int buttonValSingleColor = digitalRead(BUTTON_PIN_SINGLE_COLOR);
  int buttonValColorWipe = digitalRead(BUTTON_PIN_COLOR_WIPE);
  int buttonValColorChase = digitalRead(BUTTON_PIN_COLOR_CHASE);
  int buttonValRainbow = digitalRead(BUTTON_PIN_RAINBOW);
  int buttonValRainbowChase = digitalRead(BUTTON_PIN_RAINBOW_CHASE);

  int buttonValWhite = digitalRead(BUTTON_PIN_WHITE);
  int buttonValRed = digitalRead(BUTTON_PIN_RED);
  int buttonValBlue = digitalRead(BUTTON_PIN_BLUE);
  int buttonValGreen = digitalRead(BUTTON_PIN_GREEN);

  int potValue = analogRead(POT_PIN);

  brightness = potValue/4;

  Serial.println(potValue);

  if(buttonValWhite == LOW){
    RED = 127;
    GREEN = 127;
    BLUE = 127;
  }

  if(buttonValRed == LOW){
    RED = 255;
    GREEN = 0;
    BLUE = 0;
  }

  if(buttonValGreen == LOW){
    RED = 0;
    GREEN = 255;
    BLUE = 0;
  }

  if(buttonValBlue == LOW){
    RED = 0;
    GREEN = 0;
    BLUE = 255;
  }

  if(buttonValSingleColor == LOW){
    allOneColor(ring.Color(RED,GREEN,BLUE));
  }

  if(buttonValColorWipe == LOW){
    colorWipe(ring.Color(RED,GREEN,BLUE));
  }

  if(buttonValColorChase == LOW){
    colorChase(ring.Color(RED,GREEN,BLUE));
  }

  if(buttonValRainbow == LOW){
    rainbow();
  }

  if(buttonValRainbowChase == LOW){
    rainbowChase();
  }

  
}

void allOneColor(uint32_t color){
  ring.fill(color, 0, ring.numPixels());
  ring.show();
  ring.setBrightness(brightness);
  delay(100);
}

void colorWipe(uint32_t color){
  for(int i = 0; i < ring.numPixels(); i++){
    ring.setPixelColor(i, color);
    ring.show();
    ring.setBrightness(brightness);
    delay(50);
  }
}

void colorChase(uint32_t color){
  for(int a=0; a<10; a++){
    for(int b=0; b<3; b++){
      ring.clear();
      for(int c=b; c<ring.numPixels(); c+=3){
        ring.setPixelColor(c, color);
      }
      ring.show();
      ring.setBrightness(brightness);
      delay(50);
    }
  }
}

void rainbow(){
  for(long firstPixelHue =0; firstPixelHue < 5*65536; firstPixelHue += 256){
    for(int i = 0; i<ring.numPixels(); i++){
      int pixelHue = firstPixelHue + ( i * 65536L / ring.numPixels());
      ring.setPixelColor(i, ring.gamma32(ring.ColorHSV(pixelHue)));
    }
    ring.show();
    ring.setBrightness(brightness);
    delay(10);
  }
}

void rainbowChase(){
  int firstPixelHue = 0;
  for(int a=0; a<30;a++){
    for(int b=0; b<3;b++){
      ring.clear();
      for(int c=b;c<ring.numPixels();c+=3){
        int hue = firstPixelHue + c * 65536L / ring.numPixels();
        uint32_t color = ring.gamma32(ring.ColorHSV(hue));
        ring.setPixelColor(c, color);
      }
      ring.show();
      ring.setBrightness(brightness);
      delay(50);
      firstPixelHue += 65536 / 90;
    }
  }
}
