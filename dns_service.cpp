#include "dns_service.h"
#include "config.h"

#include <WiFi.h>
#include <DNSServer.h>

static DNSServer dnsServer;

void dnsInit() {
    IPAddress apIP(
        AP_IP_0,
        AP_IP_1,
        AP_IP_2,
        AP_IP_3
    );

    dnsServer.start(
        DNS_PORT,
        "*",
        apIP
    );

    Serial.println("[DNS] Wildcard DNS server started");
    Serial.println("[DNS] All queries resolve to ESP32");
}

void dnsProcess() {
    dnsServer.processNextRequest();
}