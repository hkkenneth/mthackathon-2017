#include "SoftwareSerial.h"
#include "WiFiEsp.h"

#define TIMEOUT 15000 // mS

WiFiEspClient client;

SoftwareSerial Serial1(7, 6); // RX, TX

char server[] = "arduino.cc";

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.setTimeout(1500);

  Serial1.begin(115200);
  while (!Serial1) {
    ; // wait for serial port to connect. Needed for native USB port only
  }  
  Serial1.setTimeout(1500);

  Serial.println("Serial Initialized");

  wrapCommand("Init", "AT");

  wrapCommand("Set CWMODE", "AT+CWMODE=1");

  wrapCommand("Check CWMODE", "AT+CWMODE?");

  wrapCommand("Check IP", "AT+CIFSR");

  wrapCommand("Connect Wifi","AT+CWJAP=\"patcklui\",\"patck27159039\"");

  wrapCommand("Use single connection mode", "AT+CIPMUX=0");

  wrapCommand("Connect", "AT+CIPSTART=\"TCP\",\"192.168.0.102\",12345", 3000);

  String httpPayload = "GET / HTTP/1.0";
  wrapCommand("Start sending", "AT+CIPSEND=" + String(httpPayload.length()));

  wrapCommand("Send", httpPayload);

  wrapCommand("Closing", "AT+CIPCLOSE");
}

void wrapCommand(String message, String cmd) {
  wrapCommand(message, cmd, 1000);
}

void wrapCommand(String message, String cmd, int waitTime) {
  Serial.println(message);
  Serial1.println(cmd);
  delay(waitTime);
  while (Serial1.available() > 0) {
    Serial.print(Serial1.readString());
  }
}

void loop() {
  if (Serial.available() > 0) {
    if (Serial.readString().equals("END\r\n")) {
      Serial.println("Disconnect Wifi");
      Serial1.println("AT+CWQAP");
      delay(1000);
      while (Serial1.available() > 0) {
        Serial.print(Serial1.readString());
      }
    } else if (Serial.readString().equals("RST\r\n")) {
      setup();
    }
  }
}

