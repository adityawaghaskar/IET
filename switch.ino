#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "SwitchNetwork";
const char* password = "SwitchPassword";

WebServer server(80);

const unsigned int MAX_CONNECTIONS = 10; // Maximum allowed connections before intrusion detection
const unsigned long DETECTION_INTERVAL = 5000; // Interval for checking intrusion (in milliseconds)

bool intrusionDetected = false;

void handleRoot() {
  server.send(200, "text/html", "<h1>Intrusion Detection System</h1><p>Status: " + String(intrusionDetected ? "Intrusion Detected" : "No Intrusion Detected") + "</p>");
}

void setup() {
  Serial.begin(115200);

  // Configure ESP32 as Access Point
  WiFi.softAP(ssid, password);
  Serial.println("Access Point created");

  // Initialize web server
  server.on("/", HTTP_GET, handleRoot);
  server.begin();
  Serial.println("Web server started");

  // Print initial memory usage
  Serial.print("Initial free memory: ");
  Serial.println(ESP.getFreeHeap());
}

void loop() {
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();

  // Check for intrusion periodically
  if (currentMillis - previousMillis >= DETECTION_INTERVAL) {
    checkIntrusion();
    previousMillis = currentMillis;
  }

  // Handle web server client requests
  server.handleClient();
}

void checkIntrusion() {
  int packetCount = WiFi.softAPgetStationNum(); // Get the number of connected stations (clients)

  // Print packet count for debugging
  Serial.print("Current number of requests: ");
  Serial.println(packetCount);

  // Adjust threshold dynamically based on network activity
  unsigned int threshold = MAX_CONNECTIONS;

  // Perform intrusion detection
  if (packetCount > threshold) {
    intrusionDetected = true;
    Serial.println("Intrusion Detected!");
  } else {
    intrusionDetected = false;
    Serial.println("No Intrusion Detected");
  }

  // Print free memory for monitoring resource usage
  Serial.print("Free memory: ");
  Serial.println(ESP.getFreeHeap());
}
