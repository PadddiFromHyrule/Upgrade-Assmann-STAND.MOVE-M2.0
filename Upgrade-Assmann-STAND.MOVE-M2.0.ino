/*
  Ping))) Sensor

  This sketch reads a PING))) ultrasonic rangefinder and returns the distance
  to the closest object in range. To do this, it sends a pulse to the sensor to
  initiate a reading, then listens for a pulse to return. The length of the
  returning pulse is proportional to the distance of the object from the sensor.

  The circuit:
	- +V connection of the PING))) attached to +5V
	- GND connection of the PING))) attached to ground
	- SIG connection of the PING))) attached to digital pin 7

  created 3 Nov 2008
  by David A. Mellis
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/sensors/Ping/
*/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// this constant won't change. It's the pin number of the sensor's output:
const int trigPin = 7;
const int echoPin = 8;
const int relaisRunter = 12;
const int relaisHoch = 11;
const int buttonDown = 3;
const int buttonUp = 2;
bool runter = false;
bool hoch = false;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 Fehler"));
    for(;;);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relaisRunter, OUTPUT);
  pinMode(relaisHoch, OUTPUT);
  pinMode(buttonDown, INPUT_PULLUP);
  pinMode(buttonUp, INPUT_PULLUP);
}

void loop() {
  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  long duration, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);

  if (digitalRead(buttonDown) == LOW) {
    runter = true;
    delay(50);
  }
    if (digitalRead(buttonUp) == LOW) {
    hoch = true;
    delay(50);
  }
    if (runter) {
      if (cm > 20) {
        digitalWrite(relaisRunter, HIGH);
      } else {
        digitalWrite(relaisRunter, LOW);
        runter = false;
      }
    }
    if (hoch) {
      if (cm < 30) {
        digitalWrite(relaisHoch, HIGH);
      } else {
        digitalWrite(relaisHoch, LOW);
        hoch = false;
      }
    }
  
  Serial.print(cm);
  Serial.print(" cm");
  Serial.println();

  display.clearDisplay();      // Wichtig: Vorher den alten Wert löschen!


  display.setTextSize(3);      // Große Schrift für den Wert
  display.setCursor(0, 0);
  display.print(cm);
  display.print(" cm");

  display.display();

  delay(1000);
}


long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
