#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
void setup()
{
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
}
char target[] = "GET TAGS";
void loop()
{
  delay(1000);
  if (Serial.available() > 0) {
    if ( Serial.find(target)) {
      if ( ! mfrc522.PICC_IsNewCardPresent())
      {
        return;
      }
      if ( ! mfrc522.PICC_ReadCardSerial())
      {
        return;
      }
      String content = "";
      byte letter;
      for (byte i = 0; i < mfrc522.uid.size; i++)
      {
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
      content.toUpperCase();
      if (content.substring(1) == "9C 21 2F 02")
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
               (content.substring(1) == "0C 17 2F 02")) {
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
               (content.substring(1) == "0C FA 2E 02") or \
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
      else if (content.substring(1) == "FC 16 2F 02")
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
               (content.substring(1) == "0C 23 2F 02")) {
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
               (content.substring(1) == "0C 14 2F 02")) {
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
      else if (content.substring(1) == "EC EC 2E 02")
      {
        Serial.println("num:25");
        delay(1000);
      }
      else if (content.substring(1) == "4C FF 2E 02") {
        Serial.println("num:26");
        delay(1000);
      }
      else if ((content.substring(1) == "4C 0D 2F 02" ) or \
               (content.substring(1) == "EC F7 2E 02")) {
        Serial.println("num:27");
        delay(1000);
      }
      else if ((content.substring(1) == "8C 04 2F 02" ) or \
               (content.substring(1) == "0C 26 2F 02")) {
        Serial.println("num:28");
        delay(1000);
      }
      else if ((content.substring(1) == "5C 1D 2F 02" ) or \
               (content.substring(1) == "1C 26 2F 02")) {
        Serial.println("num:29");
        delay(1000);
      }
      else if ((content.substring(1) == "EC BD 2E 02" ) or \
               (content.substring(1) == "FC E7 2E 02")) {
        Serial.println("num:30");
        delay(1000);
      }
      else if ((content.substring(1) == "FC EE 2E 02" ) or \
               (content.substring(1) == "6C 2C 2F 02") or \
               (content.substring(1) == "7C 04 2F 02")) {
        Serial.println("num:31");
        delay(1000);
      }
      else if ((content.substring(1) == "5C 0D 2F 02" ) or \
               (content.substring(1) == "8C 14 2F 02") or \
               (content.substring(1) == "0C EE 2E 02")) {
        Serial.println("num:32");
        delay(1000);
      }
      else if ((content.substring(1) == "2C 08 2F 02" ) or \
               (content.substring(1) == "EC C4 2E 02") or \
               (content.substring(1) == "DC F7 2E 02")) {
        Serial.println("num:33");
        delay(1000);
      }
      else if ((content.substring(1) == "2C FD 2E 02" ) or \
               (content.substring(1) == "4C A6 2E 02") or \
               (content.substring(1) == "4C 1A 2F 02")) {
        Serial.println("num:34");
        delay(1000);
      }
      else if ((content.substring(1) == "0C EF 2E 02" ) or \
               (content.substring(1) == "9C AC 2E 02")) {
        Serial.println("num:35");
        delay(1000);
      }
      else if (content.substring(1) == "0C E8 2E 02") {
        Serial.println("num:36");
        delay(1000);
      }
      else if (content.substring(1) == "1C DA 2E 02")
      {
        Serial.println("num:37");
        delay(1000);
      }
      else if (content.substring(1) == "DC D0 2E 02") {
        Serial.println("num:38");
        delay(1000);
      }
      else if ((content.substring(1) == "2C E2 2E 02" ) or \
               (content.substring(1) == "BC B9 2E 02")) {
        Serial.println("num:39");
        delay(1000);
      }
      else if ((content.substring(1) == "8C C9 2E 02" ) or \
               (content.substring(1) == "EC D0 2E 02")) {
        Serial.println("num:40");
        delay(1000);
      }
      else if ((content.substring(1) == "2C C1 2E 02" ) or \
               (content.substring(1) == "5C DB 2E 02")) {
        Serial.println("num:41");
        delay(1000);
      }
      else if ((content.substring(1) == "EC BB 2E 02" ) or \
               (content.substring(1) == "2C B4 2E 02")) {
        Serial.println("num:42");
        delay(1000);
      }
      else if ((content.substring(1) == "AC CB 2E 02" ) or \
               (content.substring(1) == "7C C9 2E 02") or \
               (content.substring(1) == "4C C8 2E 02")) {
        Serial.println("num:43");
        delay(1000);
      }
      else if ((content.substring(1) == "1C B2 2E 02" ) or \
               (content.substring(1) == "2C D9 2E 02") or \
               (content.substring(1) == "0C DA 2E 02")) {
        Serial.println("num:44");
        delay(1000);
      }
      else if ((content.substring(1) == "0C D8 2E 02" ) or \
               (content.substring(1) == "1C E2 2E 02") or \
               (content.substring(1) == "FC D1 2E 02")) {
        Serial.println("num:45");
        delay(1000);
      }
      else if ((content.substring(1) == "6C CA 2E 02" ) or \
               (content.substring(1) == "9C CB 2E 02") or \
               (content.substring(1) == "CC D7 2E 02")) {
        Serial.println("num:46");
        delay(1000);
      }
      else if ((content.substring(1) == "BC D2 2E 02" ) or \
               (content.substring(1) == "CC B9 2E 02")) {
        Serial.println("num:47");
        delay(1000);
      }
      else if (content.substring(1) == "3C D9 2E 02") {
        Serial.println("num:48");
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
