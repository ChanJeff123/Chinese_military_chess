#include <SoftwareSerial.h>
#include "FastLED.h"
#include <SPI.h>
#include <MFRC522.h>

SoftwareSerial mySerial(3, 1);//CONNECT WITH OTHER BOARD

unsigned char order[4] = {0xAA, 0x06, 0x00, 0xB0};

#define LED_DT 8
#define COLOR_ORDER GRB
#define LED_TYPE WS2812
#define NUM_LEDS 5
uint8_t max_bright = 60;
struct CRGB leds[NUM_LEDS];

#define SS_PIN 4  //D2
#define RST_PIN 5 //D1

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int a;
int b1 = 0;
int b2 = 0;
int b3 = 0;
int b4 = 0;
MFRC522::MIFARE_Key key;
// Init array that will store new NUID
byte nuidPICC[3];

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
  volume(0x1E);//音量设置0x00-0x1E
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  //  rfid.PCD_Init(); // Init MFRC522
  LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(max_bright);
  set_max_power_in_volts_and_milliamps(5, 500);
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
}

void loop() {
  RFID();
  if (0 < a && a < 13) {
    b1 = a;
    //Serial.print("b1=");
    ////Serial.println(b1);
    led(10);
  }
  else if (12 < a && a < 25) {
    b2 = a - 12;
    //Serial.print("b2=");
    ////Serial.println(b2);
    led(10);
  }
  else if (24 < a && a < 37) {
    b3 = a - 24;
    //Serial.print("b3=");
    ////Serial.println(b3);
    led(10);
  }
  else if (36 < a && a < 49) {
    b4 = a - 36;
    //Serial.print("b4=");
    ////Serial.println(b4);
    led(10);
  }
  suanfa();
}

void play(unsigned char Track)
{
  unsigned char play[6] = {0xAA, 0x07, 0x02, 0x00, Track, Track + 0xB3}; //0xB3=0xAA+0x07+0x02+0x00,即最后一位为校验和
  mySerial.write(play, 6);
}
void volume( unsigned char vol)
{
  unsigned char volume[5] = {0xAA, 0x13, 0x01, vol, vol + 0xBE}; //0xBE=0xAA+0x13+0x01,即最后一位为校验和
  mySerial.write(volume, 5);
}
void RFID() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    //    ;
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    //    ;
    return;
  }
  //  Serial.print(F("PICC type: "));
  //  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  //  Serial.println(rfid.PICC_GetTypeName(piccType));
  //Show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
  if (content.substring(1) == "9C 21 2F 02")
  {
    Serial.println("num:1");
    a = 1;
    delay(500);
  }
  else if (content.substring(1) == "5C 0E 2F 02") {
    ////Serial.println("num:2");
    a = 2;
    delay(500);
  }
  else if ((content.substring(1) == "3C F1 2E 02" ) or \
           (content.substring(1) == "AC F6 2E 02")) {
    ////Serial.println("num:3");
    a = 3 ;
    delay(500);
  }
  else if ((content.substring(1) == "9C 20 2F 02" ) or \
           (content.substring(1) == "8C 20 2F 02")) {
    ////Serial.println("num:4");
    a = 4 ;
    delay(500);
  }
  else if ((content.substring(1) == "9C F2 2E 02" ) or \
           (content.substring(1) == "CC F8 2E 02")) {
    ////Serial.println("num:5");
    a = 5 ;
    delay(500);
  }
  else if ((content.substring(1) == "FC 08 2F 02" ) or \
           (content.substring(1) == "0C 17 2F 02")) {
    ////Serial.println("num:6");
    a = 6 ;
    delay(500);
  }
  else if ((content.substring(1) == "EC 08 2F 02" ) or \
           (content.substring(1) == "9C 11 2F 02") or \
           (content.substring(1) == "1C 2E 2F 02")) {
    ////Serial.println("num:7");
    a = 7 ;
    delay(500);
  }
  else if ((content.substring(1) == "2C F1 2E 02" ) or \
           (content.substring(1) == "FC 18 2F 02") or \
           (content.substring(1) == "6C 1E 2F 02")) {
    ////Serial.println("num:8");
    a = 8 ;
    delay(500);
  }
  else if ((content.substring(1) == "4C 29 2F 02" ) or \
           (content.substring(1) == "0C FA 2E 02") or \
           (content.substring(1) == "7C 10 2F 02")) {
    ////Serial.println("num:9");
    a = 9 ;
    delay(500);
  }
  else if ((content.substring(1) == "3C 27 2F 02" ) or \
           (content.substring(1) == "EC 06 2F 02") or \
           (content.substring(1) == "4C 01 2F 02")) {
    ////Serial.println("num:10");
    a = 10 ;
    delay(500);
  }
  else if ((content.substring(1) == "5C 01 2F 02" ) or \
           (content.substring(1) == "AC 21 2F 02")) {
    ////Serial.println("num:11");
    a = 11 ;
    delay(500);
  }
  else if (content.substring(1) == "4C F4 2E 02") {
    ////Serial.println("num:12");
    a = 12 ;
    delay(500);
  }
  else if (content.substring(1) == "FC 16 2F 02")
  {
    ////Serial.println("num:13");
    a = 13 ;
    delay(500);
  }
  else if (content.substring(1) == "8C 2A 2F 02") {
    ////Serial.println("num:14");
    a = 14 ;
    delay(500);
  }
  else if ((content.substring(1) == "7C 2E 2F 02" ) or \
           (content.substring(1) == "AC 1B 2F 02")) {
    ////Serial.println("num:15");
    a = 15 ;
    delay(500);
  }
  else if ((content.substring(1) == "9C 2A 2F 02" ) or \
           (content.substring(1) == "3C FF 2E 02")) {
    ////Serial.println("num:16");
    a = 16 ;
    delay(500);
  }
  else if ((content.substring(1) == "BC 03 2F 02" ) or \
           (content.substring(1) == "CC 03 2F 02")) {
    ////Serial.println("num:17");
    a = 17 ;
    delay(500);
  }
  else if ((content.substring(1) == "4C 0A 2F 02" ) or \
           (content.substring(1) == "AC 02 2F 02")) {
    ////Serial.println("num:18");
    a = 18 ;
    delay(500);
  }
  else if ((content.substring(1) == "6C 0F 2F 02" ) or \
           (content.substring(1) == "AC 0B 2F 02") or \
           (content.substring(1) == "0C C3 2E 02")) {
    ////Serial.println("num:19");
    a = 19 ;
    delay(500);
  }
  else if ((content.substring(1) == "FC 22 2F 02" ) or \
           (content.substring(1) == "1C 08 2F 02") or \
           (content.substring(1) == "0C 23 2F 02")) {
    ////Serial.println("num:20");
    a = 20 ;
    delay(500);
  }
  else if ((content.substring(1) == "9C 0B 2F 02") or \
           (content.substring(1) == "EC 12 2F 02") or \
           (content.substring(1) == "8C 2E 2F 02")) {
    ////Serial.println("num:21");
    a = 21 ;
    delay(500);
  }
  else if ((content.substring(1) == "4C FB 2E 02" ) or \
           (content.substring(1) == "BC 05 2F 02") or \
           (content.substring(1) == "0C 14 2F 02")) {
    ////Serial.println("num:22");
    a = 22 ;
    delay(500);
  }
  else if ((content.substring(1) == "8C F2 2E 02" ) or \
           (content.substring(1) == "9C F3 2E 02")) {
    ////Serial.println("num:23");
    a = 23 ;
    delay(500);
  }
  else if (content.substring(1) == "3C 1A 2F 02") {
    ////Serial.println("num:24");
    a = 24 ;
    delay(500);
  }
  else if (content.substring(1) == "EC EC 2E 02")
  {
    ////Serial.println("num:25");
    a = 25 ;
    delay(500);
  }
  else if (content.substring(1) == "4C FF 2E 02") {
    ////Serial.println("num:26");
    a = 26 ;
    delay(500);
  }
  else if ((content.substring(1) == "4C 0D 2F 02" ) or \
           (content.substring(1) == "EC F7 2E 02")) {
    ////Serial.println("num:27");
    a = 27 ;
    delay(500);
  }
  else if ((content.substring(1) == "8C 04 2F 02" ) or \
           (content.substring(1) == "0C 26 2F 02")) {
    ////Serial.println("num:28");
    a = 28 ;
    delay(500);
  }
  else if ((content.substring(1) == "5C 1D 2F 02" ) or \
           (content.substring(1) == "1C 26 2F 02")) {
    ////Serial.println("num:29");
    a = 29;
    delay(500);
  }
  else if ((content.substring(1) == "EC BD 2E 02" ) or \
           (content.substring(1) == "FC E7 2E 02")) {
    ////Serial.println("num:30");
    a = 30;
    delay(500);
  }
  else if ((content.substring(1) == "FC EE 2E 02" ) or \
           (content.substring(1) == "6C 2C 2F 02") or \
           (content.substring(1) == "7C 04 2F 02")) {
    ////Serial.println("num:31");
    a = 31;
    delay(500);
  }
  else if ((content.substring(1) == "5C 0D 2F 02" ) or \
           (content.substring(1) == "8C 14 2F 02") or \
           (content.substring(1) == "0C EE 2E 02")) {
    ////Serial.println("num:32");
    a = 32;
    delay(500);
  }
  else if ((content.substring(1) == "2C 08 2F 02" ) or \
           (content.substring(1) == "EC C4 2E 02") or \
           (content.substring(1) == "DC F7 2E 02")) {
    ////Serial.println("num:33");
    a = 33 ;
    delay(500);
  }
  else if ((content.substring(1) == "2C FD 2E 02" ) or \
           (content.substring(1) == "4C A6 2E 02") or \
           (content.substring(1) == "4C 1A 2F 02")) {
    ////Serial.println("num:34");
    a = 34;
    delay(500);
  }
  else if ((content.substring(1) == "0C EF 2E 02" ) or \
           (content.substring(1) == "9C AC 2E 02")) {
    ////Serial.println("num:35");
    a = 35;
    delay(500);
  }
  else if (content.substring(1) == "0C E8 2E 02") {
    ////Serial.println("num:36");
    a = 36;
    delay(500);
  }
  else if (content.substring(1) == "1C DA 2E 02")
  {
    ////Serial.println("num:37");
    a = 37;
    delay(500);
  }
  else if (content.substring(1) == "DC D0 2E 02") {
    ////Serial.println("num:38");
    a = 38;
    delay(500);
  }
  else if ((content.substring(1) == "2C E2 2E 02" ) or \
           (content.substring(1) == "BC B9 2E 02")) {
    ////Serial.println("num:39");
    a = 39;
    delay(500);
  }
  else if ((content.substring(1) == "8C C9 2E 02" ) or \
           (content.substring(1) == "EC D0 2E 02")) {
    ////Serial.println("num:40");
    a = 40;
    delay(500);
  }
  else if ((content.substring(1) == "2C C1 2E 02" ) or \
           (content.substring(1) == "5C DB 2E 02")) {
    ////Serial.println("num:41");
    a = 41 ;
    delay(500);
  }
  else if ((content.substring(1) == "EC BB 2E 02" ) or \
           (content.substring(1) == "2C B4 2E 02")) {
    ////Serial.println("num:42");
    a = 42;
    delay(500);
  }
  else if ((content.substring(1) == "AC CB 2E 02" ) or \
           (content.substring(1) == "7C C9 2E 02") or \
           (content.substring(1) == "4C C8 2E 02")) {
    ////Serial.println("num:43");
    a = 43;
    delay(500);
  }
  else if ((content.substring(1) == "1C B2 2E 02" ) or \
           (content.substring(1) == "2C D9 2E 02") or \
           (content.substring(1) == "0C DA 2E 02")) {
    ////Serial.println("num:44");
    a = 44;
    delay(500);
  }
  else if ((content.substring(1) == "0C D8 2E 02" ) or \
           (content.substring(1) == "1C E2 2E 02") or \
           (content.substring(1) == "FC D1 2E 02")) {
    //Serial.println("num:45");
    a = 45;
    delay(500);
  }
  else if ((content.substring(1) == "6C CA 2E 02" ) or \
           (content.substring(1) == "9C CB 2E 02") or \
           (content.substring(1) == "CC D7 2E 02")) {
    //Serial.println("num:46");
    a = 46;
    delay(500);
  }
  else if ((content.substring(1) == "BC D2 2E 02" ) or \
           (content.substring(1) == "CC B9 2E 02")) {
    ////Serial.println("num:47");
    a = 47;
    delay(500);
  }
  else if (content.substring(1) == "3C D9 2E 02") {
    ////Serial.println("num:48");
    a = 48;
    delay(500);
  }
  else   {
    ;
  }
}
void suanfa() {
  if (b1 != 0 && b2 != 0) {
    if (b1 < 10 && b2 < 10 && b1 < b2) {
      B1_win();
    } else if (b1 < 10 && b2 < 10 && b1 > b2) {
      B2_win();
    } else if (b1 < 10 && b2 < 10 && b1 == b2) {
      NO_win();
      //吃掉军棋的情况
    } else if (b1 == 12) {
      B2_win();
    } else if (b2 == 12) {
      B1_win();
      //炸弹的情况
    } else if (b1 == 11 || b2 == 11) {
      NO_win();
      //地雷的情况
    } else if (b1 == 10) {
      if (b2 == 9) {
        B2_win();
      } else if (b2 == 11) {
        NO_win();
      } else {
        B1_win();
      }
    } else if (b2 == 10) {
      if (b1 == 9) {
        B1_win();
      } else if (b1 == 11) {
        NO_win();
      } else {
        B2_win();
      }
    }
  }
  if (b1 != 0 && b3 != 0) {
    if (b1 < 10 && b3 < 10 && b1 < b3) {
      B1_win();
    } else if (b1 < 10 && b3 < 10 && b1 > b3) {
      B3_win();
    } else if (b1 < 10 && b3 < 10 && b1 == b3) {
      NO_win();
      //吃掉军棋的情况
    } else if (b1 == 12) {
      B3_win();
    } else if (b3 == 12) {
      B1_win();
      //炸弹的情况
    } else if (b1 == 11 || b3 == 11) {
      NO_win();
      //地雷的情况
    } else if (b1 == 10) {
      if (b3 == 9) {
        B3_win();
      } else if (b3 == 11) {
        NO_win();
      } else {
        B1_win();
      }
    } else if (b3 == 10) {
      if (b1 == 9) {
        B1_win();
      } else if (b1 == 11) {
        NO_win();
      } else {
        B3_win();
      }
    }
  }
  if (b1 != 0 && b4 != 0) {
    if (b1 < 10 && b4 < 10 && b1 < b4) {
      B1_win();
    } else if (b1 < 10 && b4 < 10 && b1 > b4) {
      B4_win();
    } else if (b1 < 10 && b4 < 10 && b1 == b4) {
      NO_win();
      //吃掉军棋的情况
    } else if (b1 == 12) {
      B4_win();
    } else if (b4 == 12) {
      B1_win();
      //炸弹的情况
    } else if (b1 == 11 || b4 == 11) {
      NO_win();
      //地雷的情况
    } else if (b1 == 10) {
      if (b4 == 9) {
        B4_win();
      } else if (b4 == 11) {
        NO_win();
      } else {
        B1_win();
      }
    } else if (b4 == 10) {
      if (b1 == 9) {
        B1_win();
      } else if (b1 == 11) {
        NO_win();
      } else {
        B4_win();
      }
    }
  }
  if (b2 != 0 && b4 != 0) {
    if (b2 < 10 && b4 < 10 && b2 < b4) {
      B2_win();
    } else if (b2 < 10 && b4 < 10 && b2 > b4) {
      B4_win();
    } else if (b2 < 10 && b4 < 10 && b2 == b4) {
      NO_win();
      //吃掉军棋的情况
    } else if (b2 == 12) {
      B4_win();
    } else if (b4 == 12) {
      B2_win();
      //炸弹的情况
    } else if (b2 == 11 || b4 == 11) {
      NO_win();
      //地雷的情况
    } else if (b2 == 10) {
      if (b4 == 9) {
        B4_win();
      } else if (b4 == 11) {
        NO_win();
      } else {
        B2_win();
      }
    } else if (b4 == 10) {
      if (b2 == 9) {
        B2_win();
      } else if (b2 == 11) {
        NO_win();
      } else {
        B4_win();
      }
    }
  }
  if (b2 != 0 && b3 != 0) {
    if (b2 < 10 && b3 < 10 && b2 < b3) {
      B2_win();
    } else if (b2 < 10 && b3 < 10 && b2 > b3) {
      B3_win();
    } else if (b2 < 10 && b3 < 10 && b2 == b3) {
      NO_win();
      //吃掉军棋的情况
    } else if (b2 == 12) {
      B3_win();
    } else if (b3 == 12) {
      B2_win();
      //炸弹的情况
    } else if (b2 == 11 || b3 == 11) {
      NO_win();
      //地雷的情况
    } else if (b2 == 10) {
      if (b3 == 9) {
        B3_win();
      } else if (b3 == 11) {
        NO_win();
      } else {
        B2_win();
      }
    } else if (b3 == 10) {
      if (b2 == 9) {
        B2_win();
      } else if (b2 == 11) {
        NO_win();
      } else {
        B3_win();
      }
    }
  }
  if (b4 != 0 && b3 != 0) {
    if (b4 < 10 && b3 < 10 && b4 < b3) {
      B4_win();
    } else if (b4 < 10 && b3 < 10 && b4 > b3) {
      B3_win();
    } else if (b4 < 10 && b3 < 10 && b4 == b3) {
      NO_win();
      //吃掉军棋的情况
    } else if (b4 == 12) {
      B3_win();
    } else if (b3 == 12) {
      B4_win();
      //炸弹的情况
    } else if (b4 == 11 || b3 == 11) {
      NO_win();
      //地雷的情况
    } else if (b4 == 10) {
      if (b3 == 9) {
        B3_win();
      } else if (b3 == 11) {
        NO_win();
      } else {
        B4_win();
      }
    } else if (b3 == 10) {
      if (b4 == 9) {
        B4_win();
      } else if (b4 == 11) {
        NO_win();
      } else {
        B3_win();
      }
    }
  }

}
void led(int C_case) {
  if (C_case == 5) {
    fill_solid(leds, NUM_LEDS, CRGB::Red);
  } else if (C_case == 6) {
    fill_solid(leds, NUM_LEDS, CRGB::Yellow);
  } else if (C_case == 7) {
    fill_solid(leds, NUM_LEDS, CRGB::Blue);
  } else if (C_case == 8) {
    fill_solid(leds, NUM_LEDS, CRGB::Green);
  } else if (C_case == 9) {
    fill_solid(leds, NUM_LEDS, CRGB::White);
  } else if (C_case == 10) {
    leds[0] = CRGB::White;
  }
  FastLED.show();
  FastLED.delay(1000);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  FastLED.clear();
}
void B1_win() {
  play(0x01);
  delay(1500);
  led(5);
  //Serial.println("RED side win!红方胜");
  ESP.restart();
}
void B2_win() {
  play(0x02);
  delay(1500);
  led(6);
  //Serial.println("YELLOW side win!黄方胜");

  ESP.restart();
}
void B3_win() {
  play(0x03);
  delay(1500);
  led(7);
  //Serial.println("BLUE side win!蓝方胜");

  ESP.restart();
}
void B4_win() {
  play(0x04);
  delay(1500);
  led(8);
  //Serial.println("GREEN side win!绿方胜");

  ESP.restart();
}

void NO_win() {
  play(0x05);
  delay(1500);
  led(9);
  //Serial.println("NO one win!双发出局");

  ESP.restart();
}
