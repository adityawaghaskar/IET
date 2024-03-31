#include <WiFi.h>

const char* ssid = "SwitchNetwork";
const char* password = "SwitchPassword";
const char* switchIP = "192.168.4.1"; // IP address of the switch

void setup() {
  Serial.begin(115200);

  // Connect to Switch's Wi-Fi network
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Switch's Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");

  Serial.print("Switch IP address: ");
  Serial.println(switchIP);
}

void loop() {
  // Request status from switch and handle safe mode activation
  WiFiClient client;
  if (client.connect(switchIP, 80)) {
    client.print("GET / HTTP/1.1\r\n");
    client.print("Host: ");
    client.print(switchIP);
    client.print("\r\n\r\n");
    while (client.connected() && !client.available()) delay(1);
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
      // Parse the response and activate safe mode if intrusion detected
      if (line.indexOf("Intrusion Detected") != -1) {
        // Optionally, you can perform some action here when intrusion is detected
      }
    }
    client.stop();
  }
  delay(5000); // Adjust polling interval as needed
}

