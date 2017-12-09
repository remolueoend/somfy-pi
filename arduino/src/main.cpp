#include <Arduino.h>
#include <Receiver.h>

// #define TX
#define RX

const int transmit_pin = 2;
const int receive_pin = 2;

void setup_tx () {
  vw_set_tx_pin(transmit_pin);
  vw_setup(2000);
  pinMode(LED_BUILTIN, OUTPUT);
}

void setup_rx () {
  Serial.begin(9600);
  Serial.println("setup");
  vw_set_rx_pin(receive_pin);
  vw_setup(2000);
  vw_rx_start();
  pinMode(LED_BUILTIN, OUTPUT);
}

void setup_rx_simple() {
  Serial.begin(9600);
  pinMode(receive_pin, INPUT);
}

void rx_simple() {
  int data = digitalRead(receive_pin);
  Serial.println(data);
  delay(10);
}

byte count = 1;

void tx() {
  char msg[7] = {'h','e','l','l','o',' ','#'};
  msg[6] = count;
  digitalWrite(LED_BUILTIN, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)msg, 7);
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(LED_BUILTIN, LOW);
  count = count + 1;
  delay(1000);
}

void rx () {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  /*
     int msg_rec = vw_wait_rx_max(5000);
     if(!msg_rec) {
     Serial.println("No message received in 5000ms");
     return;
     } else {
     Serial.print("Message received");
     Serial.println(msg_rec);
     }
   */

  if (vw_get_message(buf, &buflen)) {
    int i;
    digitalWrite(LED_BUILTIN, HIGH); // Flash a light to show received good message
    for (i = 0; i < buflen; i++) {
      Serial.print(buf[i], HEX);
    }
    Serial.println();
    digitalWrite(LED_BUILTIN, LOW);
  }
}

#ifdef TX
void setup() {
  setup_tx();
}
void loop() {
  tx();
}
#else
void setup() {
  setup_rx();
}
void loop() {
  rx();
}
#endif
