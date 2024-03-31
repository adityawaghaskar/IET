#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "SwitchNetwork";
const char* password = "SwitchPassword";
const int LED_BUILTIN_PIN = 2; // Define the pin connected to the built-in LED

WebServer server(80);

const unsigned int MAX_CONNECTIONS = 2; // Maximum allowed connections before intrusion detection
const unsigned long DETECTION_INTERVAL = 500; // Interval for checking intrusion (in milliseconds)

bool intrusionDetected = false;

void handleRoot() {
  String statusMessage = "<h1>Intrusion Detection System</h1>";

  // Add CSS for responsive design
  statusMessage += "<style>body {font-family: Arial, sans-serif; text-align: center;}"
                   "@media only screen and (max-width: 600px) {h1 {font-size: 1.5em;}}</style>";

  // Determine font color based on intrusion detection status
  String status;
  String fontColor;
  if (intrusionDetected) {
    status = "Intrusion Detected";
    fontColor = "red";
  } else {
    status = "No Intruders!!";
    fontColor = "green";
  }

  // Display status message with appropriate font color
  statusMessage += "<p>Status: <span style='color: " + fontColor + ";'>" + status + "</span></p>";

  // Send the response
  server.send(200, "text/html", statusMessage);
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

  // Set LED pin as output
  pinMode(LED_BUILTIN_PIN, OUTPUT);

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
    Serial.println("Intrusion Detected");
    activateSafeMode();
  } else {
    intrusionDetected = false;
    Serial.println("No Intrusion Detected");
  }

  // Print free memory for monitoring resource usage
  Serial.print("Free memory: ");
  Serial.println(ESP.getFreeHeap());
}

void activateSafeMode() {
  // Code to activate safe mode (e.g., turn on specific operations, deactivate critical functions)
  // Blink the LED rapidly
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_BUILTIN_PIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN_PIN, LOW);
    delay(100);
  }
}
