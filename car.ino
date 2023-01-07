/*

transistor usato 2n2222a
hfe = 270


*/

#include <SoftwareSerial.h>

#define RX 2
#define TX 3
#define PIN_RELE 4
#define PIN_TRANSISTOR 5
#define LED13 13

#define CMD_LENGTH 4

#define __BAUD 9600

#define UINT_CMD "UINT"
#define STOP_CMD "STOP"
#define GO_ON_CMD "GOON"
#define GO_BACK_CMD "BACK"

SoftwareSerial BTserial(RX, TX);
// Connect the HC-05 TX to Arduino pin 2 RX.
// Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.

uint16_t res;
char receivedFromHC05[CMD_LENGTH + 1] = { 0 };

void setup() {
  Serial.begin(__BAUD);
  BTserial.begin(__BAUD);

  pinMode(LED13, OUTPUT);
  pinMode(PIN_RELE, OUTPUT);
  pinMode(PIN_TRANSISTOR, OUTPUT);

  digitalWrite(LED13, LOW);
  digitalWrite(PIN_RELE, HIGH);               // spengo i rele(polarità standard motore)
  digitalWrite(PIN_TRANSISTOR, LOW);          // spengo il transistor(motore spento)

}

void loop() {

  if (res = (BTserial.available() >= CMD_LENGTH)) {

    BTserial.readBytes(receivedFromHC05, CMD_LENGTH);
    receivedFromHC05[CMD_LENGTH] = '\0';

    if (strcmp(receivedFromHC05, STOP_CMD) == 0) {
      digitalWrite(PIN_RELE, HIGH);  // spengo i rele(marcia avanti)
      digitalWrite(PIN_TRANSISTOR, LOW);  // spengo il transistor(motore spento)
      digitalWrite(LED13, LOW);
      //stop_flag = true;

    }
    else if (strcmp(receivedFromHC05, GO_ON_CMD) == 0) {
      digitalWrite(PIN_RELE, HIGH);   // spengo i rele(marcia avanti)
      digitalWrite(PIN_TRANSISTOR, HIGH);  // accendo il transistor
      digitalWrite(LED13, HIGH);
      //stop_flag = false;

    }
    else if (strcmp(receivedFromHC05, GO_BACK_CMD) == 0) {
      digitalWrite(PIN_RELE, LOW);  // accendo i rele(marcia indietro)
      digitalWrite(PIN_TRANSISTOR, HIGH);  // accendo il transistor
      digitalWrite(LED13, HIGH);
      //stop_flag = false;
      
    }
  
    else  /* pulisco il buffer */
      for (uint16_t i = 0; i < res; i++) BTserial.readBytes(receivedFromHC05, 1);
  }
}
