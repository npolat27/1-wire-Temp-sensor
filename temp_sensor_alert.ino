#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define ONE_WIRE_BUS    4
#define buzzer          8
#define temp_alert      31

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT  32
#define OLED_RESET     -1

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  pinMode(buzzer, OUTPUT);
  sensors.begin();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  Serial.print("Temperature: ");
  Serial.print(tempC, 3);
  Serial.println(" C");

  // Buzzer
  if (tempC > temp_alert) {
    tone(buzzer, 100);
  } else {
    noTone(buzzer);
  }

  // Display
  display.clearDisplay();

  if (tempC > temp_alert) {

    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("! ALERT !");

    display.setTextSize(2);
    display.setCursor(0, 16);
    display.print(tempC, 1);
    display.println(" C");
  } else {

    display.setTextSize(1);
    display.setCursor(0, 3);
    display.println("Temperature:");

    display.setTextSize(2);
    display.setCursor(0, 18);
    display.print(tempC, 3);
    display.println(" C");
  }

  display.display();
  delay(2000);
}