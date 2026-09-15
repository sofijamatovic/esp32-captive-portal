# ESP32 Wi-Fi Security Lab — Evil Twin / Captive Portal Demo

An embedded cybersecurity project that turns an ESP32 into a self-contained Wi-Fi
"evil twin" lab: it stands up its own access point, hijacks DNS for every connected
client, and serves a captive portal that demonstrates how phishing-style credential
harvesting works — safely, on hardware you own, with **no real credentials ever
captured, logged, or transmitted.**

Built for hands-on learning around Wi-Fi/BLE security concepts, and as an entry for
[hackathon name].

## Why this project

Deauth attacks, rogue APs, and captive-portal phishing are usually explained in
slides. This makes them physical: you connect a phone to the lab AP and watch, in
real time, on a small OLED screen, exactly what an attacker's infrastructure is doing
at each stage — access point spoofing, DNS interception, HTTP redirection, and a
simulated credential-harvesting form.

## How it works

```text
Client Device
     |
     | Wi-Fi
     v
ESP32 SoftAP  (impersonates a trusted network name)
     |
     +---- DNS Server -------- wildcard resolver: every domain -> ESP32's own IP
     |
     +---- HTTP Server ------- served from LittleFS
     |       +---- Captive portal page (index.html / style.css / app.js)
     |       +---- Phishing-awareness simulation (POST /api/login-event)
     |
     +---- SSD1306 OLED ------ live status: AP state, connected clients,
                                portal hits, login attempts
```

1. The ESP32 broadcasts its own Wi-Fi network (SoftAP).
2. A wildcard DNS server answers every DNS query with the ESP32's own IP address —
   the same trick captive portals (hotel Wi-Fi, airport Wi-Fi) use legitimately.
3. Any HTTP request gets redirected to a locally hosted page, served from the
   board's onboard flash (LittleFS) rather than baked into the firmware.
4. That page is clearly labeled as a phishing simulation *before* any input is
   requested, and the client-side JS never transmits the actual password value —
   only whether the fields were filled in.
5. The SSD1306 display shows what's happening at each stage: idle, client
   connected, portal opened, "login" attempted, simulation complete.

## Hardware

| Component | Used here |
|---|---|
| Microcontroller | ESP32-WROOM DevKit V1 (USB-C, CP2102/CH340 USB-serial) |
| Display | SSD1306 128x64 OLED, I2C |
| Wiring | 3.3V, GND, SDA → GPIO21, SCL → GPIO22 |

## Software

- **Framework:** Arduino core via PlatformIO
- **Libraries:** Adafruit SSD1306, Adafruit GFX
- **Filesystem:** LittleFS (portal HTML/CSS/JS live on flash, not in firmware)

```
src/          main.cpp, display.cpp, dns_service.cpp, portal.cpp
include/      matching headers + config.h (SSID, password, pins, IPs)
data/         index.html, style.css, app.js — flashed separately to LittleFS
```

## Building and flashing

```bash
pio run                # build
pio run -t upload      # flash firmware
pio run -t uploadfs    # flash the portal's HTML/CSS/JS to LittleFS
pio device monitor      # watch [WIFI] / [DNS] / [FS] / [HTTP] boot log, 115200 baud
```

Network name and password are set in `include/config.h`.

## Running the demo

1. Connect a phone to the SSID/password from `config.h`.
2. The OLED switches to "CLIENT CONNECTED".
3. The device's captive-portal detection should pop the login page automatically;
   if not, open `http://192.168.4.1` manually.
4. Submit the form with any values (never a real password) and watch the OLED walk
   through "LOGIN ATTEMPT" → "SIMULATION COMPLETE", while the serial log confirms
   the password value was never transmitted.

## Ethics and scope

This project is built and tested exclusively against hardware and networks I own.
It is intentionally designed so that the credential-harvesting simulation cannot
capture anything real:

- The password field's value is never sent over the network — only a boolean
  "was it filled in" flag.
- The backend never stores or logs any submitted value.
- The portal page identifies itself as a security-lab simulation before any input
  is requested.

Running this kind of tool against networks or devices you don't own and don't have
explicit permission to test is illegal in most jurisdictions, including Serbia.

## Author

Sofija Matović — [github.com/sofijamatovic](https://github.com/sofijamatovic)
