#include <Arduino.h>
#include <WiFi.h>

#include "config.h"
#include "display.h"
#include "dns_service.h"

static void setupAccessPoint() {
    WiFi.softAP(LAB_SSID, LAB_PASSWORD);

    Serial.print("[WIFI] SoftAP started: ");
    Serial.println(LAB_SSID);
    Serial.print("[WIFI] IP address: ");
    Serial.println(WiFi.softAPIP());
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    displayInit();
    displayShowStartup();

    setupAccessPoint();
    dnsInit();

    Serial.println("[SYSTEM] AP + DNS checkpoint");
}

void loop() {
    dnsProcess();
}
