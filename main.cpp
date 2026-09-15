#include <Arduino.h>
#include <WiFi.h>

#include "config.h"
#include "display.h"
#include "dns_service.h"
#include "portal.h"

static void setupAccessPoint() {
    IPAddress localIP(AP_IP_0, AP_IP_1, AP_IP_2, AP_IP_3);
    IPAddress gateway(AP_IP_0, AP_IP_1, AP_IP_2, AP_IP_3);
    IPAddress subnet(255, 255, 255, 0);

    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(localIP, gateway, subnet);
    WiFi.softAP(LAB_SSID, LAB_PASSWORD);

    Serial.print("[WIFI] SSID: "); Serial.println(LAB_SSID);
    Serial.print("[WIFI] IP: ");   Serial.println(WiFi.softAPIP());
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    setupAccessPoint();
    displayInit();
    displayShowStartup();
    dnsInit();
    portalInit();

    Serial.println("[SYSTEM] Wi-Fi laboratory ready");
}

void loop() {
    dnsProcess();
    portalHandleClient();

    static int previousClients = -1;
    int clients = WiFi.softAPgetStationNum();
    if (clients != previousClients) {
        previousClients = clients;
        displayShowClientConnected();
    }

    delay(10);
}