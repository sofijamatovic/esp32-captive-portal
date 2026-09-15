#include "portal.h"
#include "display.h"

#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>

static WebServer server(80);

static void sendFile(
    const char* path,
    const char* contentType
) {
    if (!LittleFS.exists(path)) {
        server.send(
            404,
            "text/plain",
            "File not found"
        );
        return;
    }

    File file = LittleFS.open(path, "r");

    server.streamFile(
        file,
        contentType
    );

    file.close();
}

static void handleRoot() {
    Serial.println("[PORTAL] Client opened portal");

    displayShowPortalHit();

    sendFile(
        "/index.html",
        "text/html"
    );
}

static void handleCSS() {
    sendFile(
        "/style.css",
        "text/css"
    );
}

static void handleJS() {
    sendFile(
        "/app.js",
        "application/javascript"
    );
}

static void handleLoginEvent() {
    Serial.println("[PHISH] Login attempt detected");

    bool passwordEntered =
        server.hasArg("password_entered") &&
        server.arg("password_entered") == "true";

    String username = "";

    if (server.hasArg("username")) {
        username = server.arg("username");
    }

    Serial.print("[PHISH] Username field: ");

    if (username.length() > 0) {
        Serial.println("FILLED");
    } else {
        Serial.println("EMPTY");
    }

    Serial.print("[PHISH] Password field: ");

    if (passwordEntered) {
        Serial.println("FILLED");
    } else {
        Serial.println("EMPTY");
    }

    Serial.println(
        "[PHISH] Password value was NOT transmitted"
    );

    displayShowLoginAttempt();

    server.send(
        200,
        "application/json",
        "{\"status\":\"simulation_complete\",\"password_stored\":false}"
    );

    delay(1000);

    displayShowSimulationComplete();
}

static void handleCaptivePortalDetection() {
    server.send(
        200,
        "text/html",
        "<html><body>"
        "<meta http-equiv='refresh' content='0;url=/'>"
        "</body></html>"
    );
}

static void handleNotFound() {
    Serial.print("[HTTP] Redirecting: ");
    Serial.println(server.uri());

    server.sendHeader(
        "Location",
        "http://192.168.4.1/",
        true
    );

    server.send(
        302,
        "text/plain",
        ""
    );
}

void portalInit() {
    if (!LittleFS.begin(true)) {
        Serial.println(
            "[FS] LittleFS initialization failed"
        );

        return;
    }

    Serial.println(
        "[FS] LittleFS mounted successfully"
    );

    server.on(
        "/",
        HTTP_GET,
        handleRoot
    );

    server.on(
        "/style.css",
        HTTP_GET,
        handleCSS
    );

    server.on(
        "/app.js",
        HTTP_GET,
        handleJS
    );

    server.on(
        "/generate_204",
        HTTP_GET,
        handleCaptivePortalDetection
    );

    server.on(
        "/hotspot-detect.html",
        HTTP_GET,
        handleCaptivePortalDetection
    );

    server.on(
        "/connecttest.txt",
        HTTP_GET,
        handleCaptivePortalDetection
    );

    server.on(
        "/ncsi.txt",
        HTTP_GET,
        handleCaptivePortalDetection
    );

    server.on(
        "/api/login-event",
        HTTP_POST,
        handleLoginEvent
    );

    server.onNotFound(
        handleNotFound
    );

    server.begin();

    Serial.println(
        "[HTTP] Captive portal server started"
    );
}

void portalHandleClient() {
    server.handleClient();
}