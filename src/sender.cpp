#include <Arduino.h>

#include <SPI.h>
#include <LoRa.h>

#define LORA_SS_PIN 5
#define LORA_RESET_PIN 15
#define LORA_DIO0_PIN -1 // DIO0 pin is optional, it is only needed for receive callback mode.
#define LORA_SCK_PIN 18
#define LORA_MISO_PIN 19
#define LORA_MOSI_PIN 23
#define signalBandwidth 250E3
#define spreadingFactor 10

long count = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Start LoRa sender");

  LoRa.setPins(LORA_SS_PIN, LORA_RESET_PIN, LORA_DIO0_PIN);
  // LoRa.setSignalBandwidth(signalBandwidth);

  delay(500);

  while (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
  }

  LoRa.setSpreadingFactor(spreadingFactor);
  LoRa.setSignalBandwidth(signalBandwidth);

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