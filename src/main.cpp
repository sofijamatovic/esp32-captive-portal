#include <Arduino.h>
#include "display.h"

void setup() {
    Serial.begin(115200);
    delay(1000);

    displayInit();
    displayShowStartup();

    Serial.println("[SYSTEM] OLED-only checkpoint");
}

void loop() {
    delay(1000);
}