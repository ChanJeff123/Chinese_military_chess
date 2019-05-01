#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

void setup()
{
  Serial.begin(115200);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
}

char target[] = "GET TAGS";

void loop()
{
  delay(1000);
  if (Serial.available() > 0) {
    if ( Serial.find(target)) {
      // Look for new cards
      if ( ! mfrc522.PICC_IsNewCardPresent())
      {
        return;
      }
      // Select one of the cards
      if ( ! mfrc522.PICC_ReadCardSerial())
      {
        return;
      }
      //Show UID on serial monitor
      String content = "";
      byte letter;
      for (byte i = 0; i < mfrc522.uid.size; i++)
      {
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
      content.toUpperCase();
      if (content.substring(1) == "9C 21 2F 02") //change here the UID of the card/cards that you want to give access
      {
        Serial.println("num:1");
        delay(1000);
      }
      else if (content.substring(1) == "5C 0E 2F 02") {
        Serial.println("num:2");
        delay(1000);
      }
      else if ((content.substring(1) == "3C F1 2E 02" ) or \
               (content.substring(1) == "AC F6 2E 02")) {
        Serial.println("num:3");
        delay(1000);
      }
      else if ((content.substring(1) == "9C 20 2F 02" ) or \
               (content.substring(1) == "8C 20 2F 02")) {
        Serial.println("num:4");
        delay(1000);
      }
      else if ((content.substring(1) == "9C F2 2E 02" ) or \
               (content.substring(1) == "CC F8 2E 02")) {
        Serial.println("num:5");
        delay(1000);
      }
      else if ((content.substring(1) == "FC 08 2F 02" ) or \
               (content.substring(1) == "C1 07 2F 02")) {
        Serial.println("num:6");
        delay(1000);
      }
      else if ((content.substring(1) == "EC 08 2F 02" ) or \
               (content.substring(1) == "9C 11 2F 02") or \
               (content.substring(1) == "1C 2E 2F 02")) {
        Serial.println("num:7");
        delay(1000);
      }
      else if ((content.substring(1) == "2C F1 2E 02" ) or \
               (content.substring(1) == "FC 18 2F 02") or \
               (content.substring(1) == "6C 1E 2F 02")) {
        Serial.println("num:8");
        delay(1000);
      }
      else if ((content.substring(1) == "4C 29 2F 02" ) or \
               (content.substring(1) == "CF 0A 2E 02") or \
               (content.substring(1) == "7C 10 2F 02")) {
        Serial.println("num:9");
        delay(1000);
      }
      else if ((content.substring(1) == "3C 27 2F 02" ) or \
               (content.substring(1) == "EC 06 2F 02") or \
               (content.substring(1) == "4C 01 2F 02")) {
        Serial.println("num:10");
        delay(1000);
      }
      else if ((content.substring(1) == "5C 01 2F 02" ) or \
               (content.substring(1) == "AC 21 2F 02")) {
        Serial.println("num:11");
        delay(1000);
      }
      else if (content.substring(1) == "4C F4 2E 02") {
        Serial.println("num:12");
        delay(1000);
      }
      else if (content.substring(1) == "FC 16 2F 02") //change here the UID of the card/cards that you want to give access
      {
        Serial.println("num:13");
        delay(1000);
      }
      else if (content.substring(1) == "8C 2A 2F 02") {
        Serial.println("num:14");
        delay(1000);
      }
      else if ((content.substring(1) == "7C 2E 2F 02" ) or \
               (content.substring(1) == "AC 1B 2F 02")) {
        Serial.println("num:15");
        delay(1000);
      }
      else if ((content.substring(1) == "9C 2A 2F 02" ) or \
               (content.substring(1) == "3C FF 2E 02")) {
        Serial.println("num:16");
        delay(1000);
      }
      else if ((content.substring(1) == "BC 03 2F 02" ) or \
               (content.substring(1) == "CC 03 2F 02")) {
        Serial.println("num:17");
        delay(1000);
      }
      else if ((content.substring(1) == "4C 0A 2F 02" ) or \
               (content.substring(1) == "AC 02 2F 02")) {
        Serial.println("num:18");
        delay(1000);
      }
      else if ((content.substring(1) == "6C 0F 2F 02" ) or \
               (content.substring(1) == "AC 0B 2F 02") or \
               (content.substring(1) == "BC 02 2F 02")) {
        Serial.println("num:19");
        delay(1000);
      }
      else if ((content.substring(1) == "FC 22 2F 02" ) or \
               (content.substring(1) == "1C 08 2F 02") or \
               (content.substring(1) == "C2 03 2F 02")) {
        Serial.println("num:20");
        delay(1000);
      }
      else if ((content.substring(1) == "9C 0B 2F 02") or \
               (content.substring(1) == "EC 12 2F 02") or \
               (content.substring(1) == "8C 2E 2F 02")) {
        Serial.println("num:21");
        delay(1000);
      }
      else if ((content.substring(1) == "4C FB 2E 02" ) or \
               (content.substring(1) == "BC 05 2F 02") or \
               (content.substring(1) == "C1 04 2F 02")) {
        Serial.println("num:22");
        delay(1000);
      }
      else if ((content.substring(1) == "8C F2 2E 02" ) or \
               (content.substring(1) == "9C F3 2E 02")) {
        Serial.println("num:23");
        delay(1000);
      }
      else if (content.substring(1) == "3C 1A 2F 02") {
        Serial.println("num:24");
        delay(1000);
      }
      else   {
        Serial.println(" Access denied");
        ;
        delay(1000);
      }
    }
  }
}
