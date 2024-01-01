#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <stdio.h>

const char *ssid = "Md.Maif";
const char *password = "md.maif2022@gmail.com";

WebServer server(80);

void handleRoot() {
  char msg[1500];
  float x = random(0, 100); // Generate a random value between 0 and 100 for x

  snprintf(msg, 1500,
            "<html>\
  <head>\
  <meta http-equiv='refresh' content='2'/>\
    <title>Receiving Data</title>\
    <style>\
      html { font-family: Arial; display: inline-block; margin: 0px auto; text-align: center;}\
    </style>\
  </head>\
  <body>\
    <h2>Receiving Data</h2>\
    <p>Data X: %.2f</p>\
  </body>\
</html>",
           x
  );
  server.send(200, "text/html", msg);
}

void setup(void) {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Connecting....\n\n");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
}

void loop(void) {
  server.handleClient();
  // You can add additional code here if needed
}
