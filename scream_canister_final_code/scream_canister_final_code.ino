//shout out to MertArduino for the sound sensor + LED instructable, it was very helpful :-)
//https://www.instructables.com/Arduino-Sound-Sensor-with-LED/

#include <Adafruit_NeoPixel.h>

//declare my vars
//sound sensor vars
int soundSensor = A1;
int screamDuration = 0;
int screamReading;

//timer vars
int startTime;
int interval = 3000;

//neopixel vars
int numLights = 5;
int stripPin = 7;
int currentPixel = 0;

// make an array
const int arrayLen = 100;
int screamArray[arrayLen];

int index = 0;
unsigned long sum = 0;

unsigned long avgScream;

Adafruit_NeoPixel strip(numLights, stripPin);

void setup() {
  Serial.begin(9600);
  //initilize my neopixel strip
  strip.begin();
  strip.clear();

  //set the brightness
  strip.setBrightness(255);

  //set pin modes
  pinMode (soundSensor, INPUT);

  //for loop to go through values in my array
  for (int i = 0; i < arrayLen; i++) {
    screamReading = analogRead(soundSensor);
    screamArray[i] = screamReading;
    sum += screamArray[i];
    Serial.println (screamArray[0]);
  }
}

void loop() {
  //read sound sensor
  screamReading = analogRead (soundSensor);

  // subtract old value from sum
  sum -= screamArray[index];

  // add new value to array
  screamArray[index] = screamReading;

  // add new value to sum
  sum += screamArray[index];

  // update the index
  index++;

  // reset index when it reaches the end
  if (index >= arrayLen) {
    index = 0;
  }

  // print out the average
  avgScream = sum / arrayLen;
  //  Serial.print ("avg: ");
  //  Serial.println(avgScream);

  //if scream is loud, have neopixels light up
  if (screamReading < 1000) {
    startTime = millis();
    screamDuration += 2;
    //    Serial.println (screamReading);
    if (screamDuration > 25 ) {
      strip.setPixelColor (0, 255, 0, 0);
    }
    if (screamDuration > 50 ) {
      strip.setPixelColor (1, 255, 0, 0);
    }
    if (screamDuration > 75) {
      strip.setPixelColor (2, 255, 0, 0);
    }
    if (screamDuration > 100) {
      strip.setPixelColor (3, 255, 0, 0);
    }
    if (screamDuration > 125) {
      strip.setPixelColor (4, 255, 0, 0);
    }
  }
  //if scream is not loud, have neopixels turn off slowly
  else {
    if (millis() - startTime > interval) {
      if (screamDuration > 0) {
        screamDuration --;
      }
      if (screamDuration < 25) {
        strip.setPixelColor (0, 0, 0, 0);
      }
      if (screamDuration < 50 ) {
        strip.setPixelColor (1, 0, 0, 0);
      }
      if (screamDuration < 75) {
        strip.setPixelColor (2, 0, 0, 0);
      }
      if (screamDuration < 100) {
        strip.setPixelColor (3, 0, 0, 0);
      }
      if (screamDuration < 125) {
        strip.setPixelColor (4, 0, 0, 0);
      }
    }
    strip.show();
  }

  Serial.println (screamDuration);
  strip.show();
}
