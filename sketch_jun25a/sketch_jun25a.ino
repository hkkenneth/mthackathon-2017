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

  Serial1.println("AT");
  Serial.print(Serial1.readString());

  Serial.println("Set CWMODE");
  Serial1.println("AT+CWMODE=1");
  delay(1000);
  while (Serial1.available() > 0) {
    Serial.print(Serial1.readString());
  }

  Serial.println("Check CWMODE");
  Serial1.println("AT+CWMODE?");
  delay(1000);
  while (Serial1.available() > 0) {
    Serial.print(Serial1.readString());
  }

  Serial.println("Check IP");
  Serial1.println("AT+CIFSR");
  delay(1000);
  while (Serial1.available() > 0) {
    Serial.print(Serial1.readString());
  }

  Serial.println("Connect Wifi");
  Serial1.println("AT+CWJAP=\"patcklui\",\"patck27159039\"");
  delay(1000);
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

