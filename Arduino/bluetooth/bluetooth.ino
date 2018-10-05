#include <SoftwareSerial.h>
#include <Time.h>

int gLedPin = 13;
int gRxPin = 3;
int gTxPin = 2;

SoftwareSerial BTSerial(gRxPin, gTxPin);

void setup() {
  BTSerial.begin(38400);
  Serial.begin(38400);
  delay(500);
}

void loop() {
  
  if (BTSerial.available()) {
    Serial.write(BTSerial.read());
  }
  if (Serial.available()) {
    BTSerial.write(Serial.read());
  }
}
  /*
   Serial.write("AT+ORGL\r\n");
   Serial.write("AT+RMAAD\r\n");
   Serial.write("AT+ROLE=0\r\n");
   Serial.write("AT+PSWD=3333\r\n");
   Serial.write("AT+NAME=NAME\r\n");
   Serial.write("AT+RESET\r\n");
   Serial.print("AT+BIND=45282,53,1666653\r\n");
   Serial.print("AT+CMODE=0\r\n");
   */
   

