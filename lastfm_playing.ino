/*
  Example file that uses a webhook to last.fm to get the currently playing
  song (which can be a scrobbled Spotify song).

  More info can be found on https://steviethecat.tumblr.com/

  First make sure you've got an API account on last.fm and have your API
  key around. Then create the webhook either directly by running:
  ./lastfm_hook.sh

  or editing lastfm_hook.json and running:
  particle webhook create lastfm_hook.json

*/

#include "Adafruit_SSD1306.h"

unsigned int nextTime = 0;    // Next time to start the webhook

#define OLED_RESET D4
Adafruit_SSD1306 oled(OLED_RESET);

unsigned long previousMillis;
// Update every 10 seconds
unsigned long interval = 100000;

void setup() {
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)

  // Subscribe to the webhook response event
  Particle.subscribe("hook-response/lastfm_currenttrack", songHandler , MY_DEVICES);
}

void songHandler(const char *event, const char *data) {
  // Handle the webhook response
  oled.clearDisplay();

  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.setCursor(0,0);
  oled.print(data);
  oled.setTextColor(BLACK, WHITE); // 'inverted' text
  oled.display();
}

void loop() {
  if (nextTime > millis()) {
        return;
  }

  // Trigger the webhook
  Particle.publish("lastfm_currenttrack", "", PRIVATE);

  nextTime = millis() + 10000;
}
