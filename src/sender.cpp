#include <Arduino.h>

#include <SPI.h>
#include <LoRa.h>

#define LORA_SS_PIN 4
#define LORA_RESET_PIN 7
#define LORA_DIO0_PIN -1 // DIO0 pin is optional, it is only needed for receive callback mode.
#define LORA_SCK_PIN 13
#define LORA_MISO_PIN 12
#define LORA_MOSI_PIN 11

long count = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Start LoRa sender");

  LoRa.setPins(LORA_SS_PIN, LORA_RESET_PIN, LORA_DIO0_PIN);

  delay(500);

  while (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
  }

  Serial.println("LoRa initializing ok");
}

void loop() {
  Serial.print("Sending packet: "); Serial.println(count);

  // Send packet
  LoRa.beginPacket();
    LoRa.print("packet: "); LoRa.print(count);
  LoRa.endPacket();

  count++;
  delay(500);
}