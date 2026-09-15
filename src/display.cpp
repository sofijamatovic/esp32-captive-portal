#include "display.h"
#include "config.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

static Adafruit_SSD1306 display(
    OLED_WIDTH,
    OLED_HEIGHT,
    &Wire,
    -1
);

void displayInit() {
    Wire.begin();

    if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        OLED_ADDR
    )) {
        Serial.println("[OLED] Initialization failed");
        return;
    }

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.display();
}

static void drawLines(
    const char* line1,
    const char* line2 = "",
    const char* line3 = "",
    const char* line4 = "",
    const char* line5 = "",
    const char* line6 = ""
) {
    display.clearDisplay();

    display.setCursor(0, 0);
    display.println(line1);

    display.setCursor(0, 11);
    display.println(line2);

    display.setCursor(0, 22);
    display.println(line3);

    display.setCursor(0, 33);
    display.println(line4);

    display.setCursor(0, 44);
    display.println(line5);

    display.setCursor(0, 55);
    display.println(line6);

    display.display();
}

void displayShowStartup() {
    drawLines(
        "SECURITY LAB",
        "---------------",
        "AP: F1-Security",
        "IP: 192.168.4.1",
        "DNS: ACTIVE",
        "PORTAL: ACTIVE"
    );
}

void displayShowClientConnected() {
    drawLines(
        "SECURITY LAB",
        "---------------",
        "NEW CLIENT",
        "CLIENT CONNECTED",
        "",
        "PORTAL READY"
    );
}

void displayShowPortalHit() {
    drawLines(
        "SECURITY LAB",
        "---------------",
        "PORTAL HIT",
        "HTTP REQUEST",
        "",
        "SIMULATION ACTIVE"
    );
}

void displayShowLoginAttempt() {
    drawLines(
        "SECURITY LAB",
        "---------------",
        "LOGIN ATTEMPT",
        "USER: DETECTED",
        "PASSWORD: ***",
        "NOT STORED"
    );
}

void displayShowSimulationComplete() {
    drawLines(
        "SECURITY LAB",
        "---------------",
        "PHISHING DEMO",
        "COMPLETE",
        "",
        "NO PASSWORD STORED"
    );
}