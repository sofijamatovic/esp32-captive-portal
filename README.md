# ESP32 Captive Portal Security Lab

An embedded cybersecurity laboratory project built around an ESP32, demonstrating Wi-Fi SoftAP operation, wildcard DNS interception, captive portal behavior, HTTP request handling, phishing awareness, and OLED-based system monitoring.

## Overview

The project creates an isolated Wi-Fi laboratory environment using the ESP32 as a wireless access point.

Connected clients are directed to a locally hosted captive portal through a wildcard DNS server. The portal simulates a phishing login page and demonstrates how credential harvesting attacks can occur.

This implementation is intentionally designed as a safe security-awareness exercise.

No real passwords are transmitted or stored.

## Architecture

```text
Client Device
     |
     | Wi-Fi
     v
ESP32 SoftAP
     |
     +---- DNS Server
     |       |
     |       +---- Wildcard DNS
     |
     +---- HTTP Server
     |       |
     |       +---- Captive Portal
     |       +---- Phishing Simulation
     |
     +---- SSD1306 OLED
             |
             +---- System Status