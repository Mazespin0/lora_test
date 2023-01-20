#include <Arduino.h>

#include <SPI.h>
#include <LoRa.h>

#define LORA_SS_PIN 5
#define LORA_RESET_PIN 15
#define LORA_DIO0_PIN -1 // DIO0 pin is optional, it is only needed for receive callback mode.
#define LORA_SCK_PIN 18
#define LORA_MISO_PIN 19
#define LORA_MOSI_PIN 23

void setup(){
  Serial.begin(115200);
  Serial.println("Start LoRa receiver");

  LoRa.setPins(LORA_SS_PIN, LORA_RESET_PIN, LORA_DIO0_PIN);
  
  delay(500);

  while (!LoRa.begin(868E6)){
    Serial.println("Starting LoRa failed!");
  }

  Serial.println("LoRa initializing ok");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize){
    Serial.print("Received packet ");

    while (LoRa.available()){
      String LoRaData = LoRa.readString();
      Serial.print(LoRaData);
    }

    int rrsi = LoRa.packetRssi();
    Serial.print(" with RSSI ");
    Serial.println(rrsi);
  }
}