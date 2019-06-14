#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
#include "FastLED.h"
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

//SDA  SCK MOSI MISO GND RST 3.3V
// D2  D5  D7   D6   GND D1  3.3V
String content = "";
int a;
int b1 = 0;
int b2 = 0;
int b3 = 0;
int b4 = 0;

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key;

// Init array that will store new NUID
byte nuidPICC[3];


void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  volume(0x1E);//音量设置0x00-0x1E
  SPI.begin();      // Initiate  SPI bus
  //  mfrc522.PCD_Init();   // Initiate MFRC522
  LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(max_bright);
  set_max_power_in_volts_and_milliamps(5, 500);
  rfid.PCD_Init(); // Init MFRC522
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

int RFID() {
  //----------------------------------------------------------------------RFID
  // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent()) {
    //    return;
    ;
  }
  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial()) {
    //    return;
    ;
  }

  if (rfid.uid.uidByte[0] != nuidPICC[0] ||
      rfid.uid.uidByte[1] != nuidPICC[1] ||
      rfid.uid.uidByte[2] != nuidPICC[2] ||
      rfid.uid.uidByte[3] != nuidPICC[3] ) {
    //    Serial.println(F("A new card has been detected."));
  }

  // Store NUID into nuidPICC array
  for (byte i = 0; i < 4; i++) {
    nuidPICC[i] = rfid.uid.uidByte[i];
  }
  //    Serial.println(F("The NUID tag is:"));
  //    Serial.print(F("In dec: "));
  //    Serial.println();

  printHex(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();
  content.toUpperCase();
  if (content.substring(1) == " 04 4C 7A 22 2C 5E 81") {
    ////Serial.println("num:1");
    a = 1;
    delay(500);
  }
  else if (content.substring(1) == " 04 79 7E 22 2C 5E 80") {
    //Serial.println("num: "2");
    a = 2;
    delay(500);
  }
  else if (content.substring(1) == " 04 3C 7C 22 2C 5E 80") {
    //Serial.println("num: "3");
    a = 3;
    delay(500);
  }
  else if (content.substring(1) == " 04 C2 7E 22 2C 5E 80") {
    //Serial.println("num: "3");
    a = 3;
    delay(500);
  }
  else if (content.substring(1) == " 04 E7 80 22 2C 5E 80") {
    //Serial.println("num: "4");
    a = 4;
    delay(500);
  }
  else if (content.substring(1) == " 04 99 75 22 2C 5E 80") {
    //Serial.println("num: "4");
    a = 4;
    delay(500);
  }
  else if (content.substring(1) == " 04 98 85 22 2C 5E 80") {
    //Serial.println("num: "5");
    a = 5;
    delay(500);
  }
  else if (content.substring(1) == " 04 53 7A 22 2C 5E 81") {
    //Serial.println("num: "5");
    a = 5;
    delay(500);
  }
  else if (content.substring(1) == " 04 27 7D 22 2C 5E 80") {
    //Serial.println("num: "6");
    a = 6;
    delay(500);
  }
  else if (content.substring(1) == " 04 33 77 22 2C 5E 81") {
    //Serial.println("num: "6");
    a = 6;
    delay(500);
  }
  else if (content.substring(1) == " 04 20 76 22 2C 5E 81") {
    //Serial.println("num: "7");
    a = 7;
    delay(500);
  }
  else if (content.substring(1) == " 04 E5 84 22 2C 5E 80") {
    //Serial.println("num: "7");
    a = 7;
    delay(500);
  }
  else if (content.substring(1) == " 04 6D 7E 22 2C 5E 81") {
    //Serial.println("num: "7");
    a = 7;
    delay(500);
  }
  else if (content.substring(1) == " 04 60 79 22 2C 5E 81") {
    //Serial.println("num: "8");
    a = 8;
    delay(500);
  }
  else if (content.substring(1) == " 04 49 76 22 2C 5E 81") {
    //Serial.println("num: "8");
    a = 8;
    delay(500);
  }
  else if (content.substring(1) == " 04 D0 76 22 2C 5E 80") {
    //Serial.println("num: "8");
    a = 8;
    delay(500);
  }
  else if (content.substring(1) == " 04 AE 75 22 2C 5E 80") {
    //Serial.println("num: "9");
    a = 9;
    delay(500);
  }
  else if (content.substring(1) == " 04 52 7D 22 2C 5E 81") {
    //Serial.println("num: "9");
    a = 9;
    delay(500);
  }
  else if (content.substring(1) == " 04 6B 7E 22 2C 5E 80") {
    //Serial.println("num: "9");
    a = 9;
    delay(500);
  }
  else if (content.substring(1) == " 04 74 7E 22 2C 5E 81") {
    //Serial.println("num: "10");
    a = 10;
    delay(500);
  }
  else if (content.substring(1) == " 04 C7 7D 22 2C 5E 80") {
    //Serial.println("num: "10");
    a = 10;
    delay(500);
  }
  else if (content.substring(1) == " 04 95 85 22 2C 5E 80") {
    //Serial.println("num: "10");
    a = 10;
    delay(500);
  }
  else if (content.substring(1) == " 04 71 7E 22 2C 5E 80") {
    //Serial.println("num: "11");
    a = 11;
    delay(500);
  }
  else if (content.substring(1) == " 04 04 78 22 2C 5E 81") {
    //Serial.println("num: "11");
    a = 11;
    delay(500);
  }
  else if (content.substring(1) == " 04 D7 75 22 2C 5E 80") {
    //Serial.println("num: "12");
    a = 12;
    delay(500);
  }
  else if (content.substring(1) == " 04 D7 75 22 2C 5E 80") {
    //Serial.println("num: "12");
    a = 12;
    delay(500);
  }
  else if (content.substring(1) == " 04 F9 7E 22 2C 5E 80") {
    //Serial.println("num: "14");
    a = 14;
    delay(500);
  }
  else if (content.substring(1) == " 04 61 7E 22 2C 5E 80") {
    //Serial.println("num: "15");
    a = 15;
    delay(500);
  }
  else if (content.substring(1) == " 04 55 7D 22 2C 5E 81") {
    //Serial.println("num: "15");
    a = 15;
    delay(500);
  }
  else if (content.substring(1) == " 04 6C 82 22 2C 5E 80") {
    //Serial.println("num: "16");
    a = 16;
    delay(500);
  }
  else if (content.substring(1) == " 04 9E 75 22 2C 5E 80") {
    //Serial.println("num: "16");
    a = 16;
    delay(500);
  }
  else if (content.substring(1) == " 04 3A 7C 22 2C 5E 80") {
    //Serial.println("num: "17");
    a = 17;
    delay(500);
  }
  else if (content.substring(1) == " 04 34 77 22 2C 5E 81") {
    //Serial.println("num: "17");
    a = 17;
    delay(500);
  }
  else if (content.substring(1) == " 04 15 79 22 2C 5E 81") {
    //Serial.println("num: "18");
    a = 18;
    delay(500);
  }
  else if (content.substring(1) == " 04 3C 79 22 2C 5E 81") {
    //Serial.println("num: "18");
    a = 18;
    delay(500);
  }
  else if (content.substring(1) == " 04 88 80 22 2C 5E 80") {
    //Serial.println("num: "19");
    a = 19;
    delay(500);
  }
  else if (content.substring(1) == " 04 6E 79 22 2C 5E 81") {
    //Serial.println("num: "19");
    a = 19;
    delay(500);
  }
  else if (content.substring(1) == " 04 5E 7E 22 2C 5E 80") {
    //Serial.println("num: "19");
    a = 19;
    delay(500);
  }
  else if (content.substring(1) == " 04 28 76 22 2C 5E 80") {
    //Serial.println("num: "20");
    a = 20;
    delay(500);
  }
  else if (content.substring(1) == " 04 25 75 22 2C 5E 80") {
    //Serial.println("num: "20");
    a = 20;
    delay(500);
  }
  else if (content.substring(1) == " 04 1D 75 22 2C 5E 80") {
    //Serial.println("num: "20");
    a = 20;
    delay(500);
  }
  else if (content.substring(1) == " 04 7C 7E 22 2C 5E 81") {
    //Serial.println("num: "21");
    a = 21;
    delay(500);
  }
  else if (content.substring(1) == " 04 F2 84 22 2C 5E 80") {
    //Serial.println("num: "21");
    a = 21;
    delay(500);
  }
  else if (content.substring(1) == " 04 EC 84 22 2C 5E 80") {
    //Serial.println("num: "21");
    a = 21;
    delay(500);
  }
  else if (content.substring(1) == " 04 90 7A 22 2C 5E 80") {
    //Serial.println("num: "22");
    a = 22;
    delay(500);
  }
  else if (content.substring(1) == " 04 70 7B B2 56 5D 81") {
    //Serial.println("num: "22");
    a = 22;
    delay(500);
  }
  else if (content.substring(1) == " 04 9F 85 22 2C 5E 80") {
    //Serial.println("num: "22");
    a = 22;
    delay(500);
  }
  else if (content.substring(1) == " 04 61 82 22 2C 5E 80") {
    //Serial.println("num: "23");
    a = 23;
    delay(500);
  }
  else if (content.substring(1) == " 04 6D 82 22 2C 5E 80") {
    //Serial.println("num: "23");
    a = 23;
    delay(500);
  }
  else if (content.substring(1) == " 04 6B 76 22 2C 5E 81") {
    //Serial.println("num: "24");
    a = 24;
    delay(500);
  }
  else if (content.substring(1) == " 04 42 76 22 2C 5E 81") {
    //Serial.println("num: "25");
    a = 25;
    delay(500);
  }
  else if (content.substring(1) == " 04 43 7A 22 2C 5E 80") {
    //Serial.println("num: "26");
    a = 26;
    delay(500);
  }
  else if (content.substring(1) == " 04 A6 7F 22 2C 5E 80") {
    //Serial.println("num: "27");
    a = 27;
    delay(500);
  }
  else if (content.substring(1) == " 04 90 85 22 2C 5E 80") {
    //Serial.println("num: "27");
    a = 27;
    delay(500);
  }
  else if (content.substring(1) == " 04 40 7A 22 2C 5E 80") {
    //Serial.println("num: "28");
    a = 28;
    delay(500);
  }
  else if (content.substring(1) == " 04 59 7E 22 2C 5E 80") {
    //Serial.println("num: "28");
    a = 28;
    delay(500);
  }
  else if (content.substring(1) == " 04 58 76 22 2C 5E 81") {
    //Serial.println("num: "29");
    a = 29;
    delay(500);
  }
  else if (content.substring(1) == " 04 22 77 22 2C 5E 80") {
    //Serial.println("num: "29");
    a = 29;
    delay(500);
  }
  else if (content.substring(1) == " 04 47 76 22 2C 5E 81") {
    //Serial.println("num: "30");
    a = 30;
    delay(500);
  }
  else if (content.substring(1) == " 04 1E 76 22 2C 5E 81") {
    //Serial.println("num: "30");
    a = 30;
    delay(500);
  }
  else if (content.substring(1) == " 04 69 79 22 2C 5E 81") {
    //Serial.println("num: "31");
    a = 31;
    delay(500);
  }
  else if (content.substring(1) == " 04 66 7E 22 2C 5E 80") {
    //Serial.println("num: "31");
    a = 31;
    delay(500);
  }
  else if (content.substring(1) == " 04 6B 82 22 2C 5E 80") {
    //Serial.println("num: "31");
    a = 31;
    delay(500);
  }
  else if (content.substring(1) == " 04 1E 80 22 2C 5E 80") {
    //Serial.println("num: "32");
    a = 32;
    delay(500);
  }
  else if (content.substring(1) == " 04 8A 79 22 2C 5E 80") {
    //Serial.println("num: "32");
    a = 32;
    delay(500);
  }
  else if (content.substring(1) == " 04 3A 7A 22 2C 5E 80") {
    //Serial.println("num: "32");
    a = 32;
    delay(500);
  }
  else if (content.substring(1) == " 04 62 7E 22 2C 5E 80") {
    //Serial.println("num: "33");
    a = 33;
    delay(500);
  }
  else if (content.substring(1) == " 04 2C 77 22 2C 5E 80") {
    //Serial.println("num: "33");
    a = 33;
    delay(500);
  }
  else if (content.substring(1) == " 04 73 79 22 2C 5E 81") {
    //Serial.println("num: "33");
    a = 33;
    delay(500);
  }
  else if (content.substring(1) == " 04 44 76 22 2C 5E 81") {
    //Serial.println("num: "34");
    a = 34;
    delay(500);
  }
  else if (content.substring(1) == " 04 2A 7D 22 2C 5E 80") {
    //Serial.println("num: "34");
    a = 34;
    delay(500);
  }
  else if (content.substring(1) == " 04 85 7B B2 56 5D 81") {
    //Serial.println("num: "34");
    a = 34;
    delay(500);
  }
  else if (content.substring(1) == " 04 D2 75 22 2C 5E 80") {
    //Serial.println("num: "35");
    a = 35;
    delay(500);
  }
  else if (content.substring(1) == " 04 CA 79 22 2C 5E 80") {
    //Serial.println("num: "35");
    a = 35;
    delay(500);
  }
  else if (content.substring(1) == " 04 49 7A 22 2C 5E 81") {
    //Serial.println("num: "36");
    a = 36;
    delay(500);
  }
  else if (content.substring(1) == " 04 90 80 22 2C 5E 80") {
    //Serial.println("num: "37");
    a = 37;
    delay(500);
  }
  else if (content.substring(1) == " 04 65 79 22 2C 5E 81") {
    //Serial.println("num: "38");
    a = 38;
    delay(500);
  }
  else if (content.substring(1) == " 04 24 76 22 2C 5E 80") {
    //Serial.println("num: "39");
    a = 39;
    delay(500);
  }
  else if (content.substring(1) == " 04 5D 7E 22 2C 5E 80") {
    //Serial.println("num: "39");
    a = 39;
    delay(500);
  }
  else if (content.substring(1) == " 04 6F 79 22 2C 5E 81") {
    //Serial.println("num: "40");
    a = 40;
    delay(500);
  }
  else if (content.substring(1) == " 04 3D 7C 22 2C 5E 80") {
    //Serial.println("num: "40");
    a = 40;
    delay(500);
  }
  else if (content.substring(1) == " 04 3A 77 22 2C 5E 81") {
    //Serial.println("num: "41");
    a = 41;
    delay(500);
  }
  else if (content.substring(1) == " 04 D1 79 22 2C 5E 80") {
    //Serial.println("num: "41");
    a = 41;
    delay(500);
  }
  else if (content.substring(1) == " 04 39 77 22 2C 5E 81") {
    //Serial.println("num: "42");
    a = 42;
    delay(500);
  }
  else if (content.substring(1) == " 04 B0 7F 22 2C 5E 80") {
    //Serial.println("num: "42");
    a = 42;
    delay(500);
  }
  else if (content.substring(1) == " 04 28 80 22 2C 5E 80") {
    //Serial.println("num: "43");
    a = 43;
    delay(500);
  }
  else if (content.substring(1) == " 04 C7 76 22 2C 5E 80") {
    //Serial.println("num: "43");
    a = 43;
    delay(500);
  }
  else if (content.substring(1) == " 04 26 75 22 2C 5E 80") {
    //Serial.println("num: "43");
    a = 43;
    delay(500);
  }
  else if (content.substring(1) == " 04 DD 80 22 2C 5E 80") {
    //Serial.println("num: "44");
    a = 44;
    delay(500);
  }
  else if (content.substring(1) == " 04 6D 7E 22 2C 5E 80") {
    //Serial.println("num: "44");
    a = 44;
    delay(500);
  }
  else if (content.substring(1) == " 04 03 78 22 2C 5E 81") {
    //Serial.println("num: "44");
    a = 44;
    delay(500);
  }
  else if (content.substring(1) == " 04 1E 79 22 2C 5E 81") {
    //Serial.println("num: "45");
    a = 45;
    delay(500);
  }
  else if (content.substring(1) == " 04 23 76 22 2C 5E 81") {
    //Serial.println("num: "45");
    a = 45;
    delay(500);
  }
  else if (content.substring(1) == " 04 2E 7D 22 2C 5E 81") {
    //Serial.println("num: "45");
    a = 45;
    delay(500);
  }
  else if (content.substring(1) == " 04 30 77 22 2C 5E 80") {
    //Serial.println("num: "46");
    a = 46;
    delay(500);
  }
  else if (content.substring(1) == " 04 75 7D 22 2C 5E 80") {
    //Serial.println("num: "46");
    a = 46;
    delay(500);
  }
  else if (content.substring(1) == " 04 2C 7D 22 2C 5E 80") {
    //Serial.println("num: "46");
    a = 46;
    delay(500);
  }
  else if (content.substring(1) == " 04 8D 80 22 2C 5E 80") {
    //Serial.println("num: "47");
    a = 47;
    delay(500);
  }
  else if (content.substring(1) == " 04 27 7D 22 2C 5E 81") {
    //Serial.println("num: "47");
    a = 47;
    delay(500);
  }
  else if (content.substring(1) == " 04 6A 7D 22 2C 5E 80") {
    //Serial.println("num: "48");
    a = 48;
    delay(500);
  }
  else if (content.substring(1) == " 04 70 82 22 2C 5E 80") {
    //Serial.println("num: "1");
    a = 1;
    delay(500);
  }
  else if (content.substring(1) == " 04 F0 78 22 2C 5E 80") {
    //Serial.println("num: "2");
    a = 2;
    delay(500);
  }
  else if (content.substring(1) == " 04 47 F2 B2 56 5D 81") {
    //Serial.println("num: "3");
    a = 3;
    delay(500);
  }
  else if (content.substring(1) == " 04 85 80 22 2C 5E 80") {
    //Serial.println("num: "3");
    a = 3;
    delay(500);
  }
  else if (content.substring(1) == " 04 32 77 22 2C 5E 81") {
    //Serial.println("num: "4");
    a = 4;
    delay(500);
  }
  else if (content.substring(1) == " 04 DD 75 22 2C 5E 80") {
    //Serial.println("num: "4");
    a = 4;
    delay(500);
  }
  else if (content.substring(1) == " 04 0E 7D 22 2C 5E 81") {
    //Serial.println("num: "5");
    a = 5;
    delay(500);
  }
  else if (content.substring(1) == " 04 38 7A 22 2C 5E 80") {
    //Serial.println("num: "5");
    a = 5;
    delay(500);
  }
  else if (content.substring(1) == " 04 00 78 22 2C 5E 81") {
    //Serial.println("num: "6");
    a = 6;
    delay(500);
  }
  else if (content.substring(1) == " 04 FA 78 22 2C 5E 80") {
    //Serial.println("num: "6");
    a = 6;
    delay(500);
  }
  else if (content.substring(1) == " 04 55 7A 22 2C 5E 81") {
    //Serial.println("num: "7");
    a = 7;
    delay(500);
  }
  else if (content.substring(1) == " 04 45 7E 22 2C 5E 80") {
    //Serial.println("num: "7");
    a = 7;
    delay(500);
  }
  else if (content.substring(1) == " 04 DD 84 22 2C 5E 80") {
    //Serial.println("num: "7");
    a = 7;
    delay(500);
  }
  else if (content.substring(1) == " 04 DF 75 22 2C 5E 80") {
    //Serial.println("num: "8");
    a = 8;
    delay(500);
  }
  else if (content.substring(1) == " 04 3E 76 22 2C 5E 80") {
    //Serial.println("num: "8");
    a = 8;
    delay(500);
  }
  else if (content.substring(1) == " 04 4E 7A 22 2C 5E 81") {
    //Serial.println("num: "8");
    a = 8;
    delay(500);
  }
  else if (content.substring(1) == " 04 8B 7E 22 2C 5E 81") {
    //Serial.println("num: "9");
    a = 9;
    delay(500);
  }
  else if (content.substring(1) == " 04 F5 78 22 2C 5E 80") {
    //Serial.println("num: "9");
    a = 9;
    delay(500);
  }
  else if (content.substring(1) == " 04 04 7D 22 2C 5E 81") {
    //Serial.println("num: "9");
    a = 9;
    delay(500);
  }
  else if (content.substring(1) == " 04 74 7D 22 2C 5E 80") {
    //Serial.println("num: "10");
    a = 10;
    delay(500);
  }
  else if (content.substring(1) == " 04 7A 79 22 2C 5E 80") {
    //Serial.println("num: "10");
    a = 10;
    delay(500);
  }
  else if (content.substring(1) == " 04 F9 84 22 2C 5E 80") {
    //Serial.println("num: "10");
    a = 10;
    delay(500);
  }
  else if (content.substring(1) == " 04 76 76 22 2C 5E 81") {
    //Serial.println("num: "11");
    a = 11;
    delay(500);
  }
  else if (content.substring(1) == " 04 23 75 22 2C 5E 80") {
    //Serial.println("num: "11");
    a = 11;
    delay(500);
  }
  else if (content.substring(1) == " 04 51 7D 22 2C 5E 81") {
    //Serial.println("num: "12");
    a = 12;
    delay(500);
  }
  else if (content.substring(1) == " 04 59 7D 22 2C 5E 81") {
    //Serial.println("num: "13");
    a = 13;
    delay(500);
  }
  else if (content.substring(1) == " 04 6D 79 22 2C 5E 81") {
    //Serial.println("num: "14");
    a = 14;
    delay(500);
  }
  else if (content.substring(1) == " 04 0D 7D 22 2C 5E 81") {
    //Serial.println("num: "15");
    a = 15;
    delay(500);
  }
  else if (content.substring(1) == " 04 7B 7E 22 2C 5E 80") {
    //Serial.println("num: "15");
    a = 15;
    delay(500);
  }
  else if (content.substring(1) == " 04 33 7A 22 2C 5E 81") {
    //Serial.println("num: "16");
    a = 16;
    delay(500);
  }
  else if (content.substring(1) == " 04 5C 7A 22 2C 5E 81") {
    //Serial.println("num: "16");
    a = 16;
    delay(500);
  }
  else if (content.substring(1) == " 04 9E 85 22 2C 5E 80") {
    //Serial.println("num: "17");
    a = 17;
    delay(500);
  }
  else if (content.substring(1) == " 04 20 77 22 2C 5E 80") {
    //Serial.println("num: "17");
    a = 17;
    delay(500);
  }
  else if (content.substring(1) == " 04 20 75 22 2C 5E 80") {
    //Serial.println("num: "18");
    a = 18;
    delay(500);
  }
  else if (content.substring(1) == " 04 3E 7A 22 2C 5E 80") {
    //Serial.println("num: "18");
    a = 18;
    delay(500);
  }
  else if (content.substring(1) == " 04 84 78 22 2C 5E 81") {
    //Serial.println("num: "19");
    a = 19;
    delay(500);
  }
  else if (content.substring(1) == " 04 F6 78 22 2C 5E 80") {
    //Serial.println("num: "19");
    a = 19;
    delay(500);
  }
  else if (content.substring(1) == " 04 2D 76 22 2C 5E 80") {
    //Serial.println("num: "19");
    a = 19;
    delay(500);
  }
  else if (content.substring(1) == " 04 14 76 22 2C 5E 81") {
    //Serial.println("num: "20");
    a = 20;
    delay(500);
  }
  else if (content.substring(1) == " 04 21 76 22 2C 5E 81") {
    //Serial.println("num: "20");
    a = 20;
    delay(500);
  }
  else if (content.substring(1) == " 04 93 85 22 2C 5E 80") {
    //Serial.println("num: "20");
    a = 20;
    delay(500);
  }
  else if (content.substring(1) == " 04 7A 7D 22 2C 5E 81") {
    //Serial.println("num: "21");
    a = 21;
    delay(500);
  }
  else if (content.substring(1) == " 04 30 76 22 2C 5E 80") {
    //Serial.println("num: "21");
    a = 21;
    delay(500);
  }
  else if (content.substring(1) == " 04 39 76 22 2C 5E 80") {
    //Serial.println("num: "21");
    a = 21;
    delay(500);
  }
  else if (content.substring(1) == " 04 FC 7D 22 2C 5E 80") {
    //Serial.println("num: "22");
    a = 22;
    delay(500);
  }
  else if (content.substring(1) == " 04 49 79 22 2C 5E 81") {
    //Serial.println("num: "22");
    a = 22;
    delay(500);
  }
  else if (content.substring(1) == " 04 2C 77 22 2C 5E 81") {
    //Serial.println("num: "22");
    a = 22;
    delay(500);
  }
  else if (content.substring(1) == " 04 75 7D 22 2C 5E 81") {
    //Serial.println("num: "23");
    a = 23;
    delay(500);
  }
  else if (content.substring(1) == " 04 B1 7F 22 2C 5E 80") {
    //Serial.println("num: "23");
    a = 23;
    delay(500);
  }
  else if (content.substring(1) == " 04 88 79 22 2C 5E 80") {
    //Serial.println("num: "24");
    a = 24;
    delay(500);
  }
  else if (content.substring(1) == " 04 86 80 22 2C 5E 80") {
    //Serial.println("num: "25");
    a = 25;
    delay(500);
  }
  else if (content.substring(1) == " 04 1F 79 22 2C 5E 81") {
    //Serial.println("num: "26");
    a = 26;
    delay(500);
  }
  else if (content.substring(1) == " 04 45 76 22 2C 5E 81") {
    //Serial.println("num: "27");
    a = 27;
    delay(500);
  }
  else if (content.substring(1) == " 04 71 79 22 2C 5E 81") {
    //Serial.println("num: "27");
    a = 27;
    delay(500);
  }
  else if (content.substring(1) == " 04 DB 80 22 2C 5E 80") {
    //Serial.println("num: "28");
    a = 28;
    delay(500);
  }
  else if (content.substring(1) == " 04 A9 75 22 2C 5E 80") {
    //Serial.println("num: "28");
    a = 28;
    delay(500);
  }
  else if (content.substring(1) == " 04 28 77 22 2C 5E 80") {
    //Serial.println("num: "29");
    a = 29;
    delay(500);
  }
  else if (content.substring(1) == " 04 28 76 22 2C 5E 81") {
    //Serial.println("num: "29");
    a = 29;
    delay(500);
  }
  else if (content.substring(1) == " 04 A9 7F 22 2C 5E 80") {
    //Serial.println("num: "30");
    a = 30;
    delay(500);
  }
  else if (content.substring(1) == " 04 6A 79 22 2C 5E 81") {
    //Serial.println("num: "30");
    a = 30;
    delay(500);
  }
  else if (content.substring(1) == " 04 18 76 22 2C 5E 80") {
    //Serial.println("num: "31");
    a = 31;
    delay(500);
  }
  else if (content.substring(1) == " 04 D6 75 22 2C 5E 80") {
    //Serial.println("num: "31");
    a = 31;
    delay(500);
  }
  else if (content.substring(1) == " 04 38 7D 22 2C 5E 81") {
    //Serial.println("num: "31");
    a = 31;
    delay(500);
  }
  else if (content.substring(1) == " 04 2E 77 22 2C 5E 81") {
    //Serial.println("num: "32");
    a = 32;
    delay(500);
  }
  else if (content.substring(1) == " 04 EA 84 22 2C 5E 80") {
    //Serial.println("num: "32");
    a = 32;
    delay(500);
  }
  else if (content.substring(1) == " 04 5A 7D 22 2C 5E 81") {
    //Serial.println("num: "32");
    a = 32;
    delay(500);
  }
  else if (content.substring(1) == " 04 1A 76 22 2C 5E 81") {
    //Serial.println("num: "33");
    a = 33;
    delay(500);
  }
  else if (content.substring(1) == " 04 22 76 22 2C 5E 80") {
    //Serial.println("num: "33");
    a = 33;
    delay(500);
  }
  else if (content.substring(1) == " 04 B8 7F 22 2C 5E 80") {
    //Serial.println("num: "33");
    a = 33;
    delay(500);
  }
  else if (content.substring(1) == " 04 3D 7A 22 2C 5E 80") {
    //Serial.println("num: "34");
    a = 34;
    delay(500);
  }
  else if (content.substring(1) == " 04 42 75 22 2C 5E 80") {
    //Serial.println("num: "34");
    a = 34;
    delay(500);
  }
  else if (content.substring(1) == " 04 2F 7A 22 2C 5E 80") {
    //Serial.println("num: "34");
    a = 34;
    delay(500);
  }
  else if (content.substring(1) == " 04 86 7E 22 2C 5E 80") {
    //Serial.println("num: "35");
    a = 35;
    delay(500);
  }
  else if (content.substring(1) == " 04 63 82 22 2C 5E 80") {
    //Serial.println("num: "35");
    a = 35;
    delay(500);
  }
  else if (content.substring(1) == " 04 E6 84 22 2C 5E 80") {
    //Serial.println("num: "36");
    a = 36;
    delay(500);
  }
  else if (content.substring(1) == " 04 92 85 22 2C 5E 80") {
    //Serial.println("num: "37");
    a = 37;
    delay(500);
  }
  else if (content.substring(1) == " 04 17 76 22 2C 5E 81") {
    //Serial.println("num: "38");
    a = 38;
    delay(500);
  }
  else if (content.substring(1) == " 04 9C 75 22 2C 5E 80") {
    //Serial.println("num: "39");
    a = 39;
    delay(500);
  }
  else if (content.substring(1) == " 04 36 7D 22 2C 5E 81") {
    //Serial.println("num: "39");
    a = 39;
    delay(500);
  }
  else if (content.substring(1) == " 04 70 7D 22 2C 5E 80") {
    //Serial.println("num: "40");
    a = 40;
    delay(500);
  }
  else if (content.substring(1) == " 04 35 7D 22 2C 5E 80") {
    //Serial.println("num: "40");
    a = 40;
    delay(500);
  }
  else if (content.substring(1) == " 04 04 7E 22 2C 5E 81") {
    //Serial.println("num: "41");
    a = 41;
    delay(500);
  }
  else if (content.substring(1) == " 04 21 7A 22 2C 5E 81") {
    //Serial.println("num: "41");
    a = 41;
    delay(500);
  }
  else if (content.substring(1) == " 04 AD 75 22 2C 5E 80") {
    //Serial.println("num: "42");
    a = 42;
    delay(500);
  }
  else if (content.substring(1) == " 04 F7 84 22 2C 5E 80") {
    //Serial.println("num: "42");
    a = 42;
    delay(500);
  }
  else if (content.substring(1) == " 04 A0 85 22 2C 5E 80") {
    //Serial.println("num: "43");
    a = 43;
    delay(500);
  }
  else if (content.substring(1) == " 04 32 7C 22 2C 5E 80") {
    //Serial.println("num: "43");
    a = 43;
    delay(500);
  }
  else if (content.substring(1) == " 04 65 7E 22 2C 5E 81") {
    //Serial.println("num: "43");
    a = 43;
    delay(500);
  }
  else if (content.substring(1) == " 04 4A EC B2 56 5D 81") {
    //Serial.println("num: "44");
    a = 44;
    delay(500);
  }
  else if (content.substring(1) == " 04 D3 75 22 2C 5E 80") {
    //Serial.println("num: "44");
    a = 44;
    delay(500);
  }
  else if (content.substring(1) == " 04 BD 7E 22 2C 5E 80") {
    //Serial.println("num: "44");
    a = 44;
    delay(500);
  }
  else if (content.substring(1) == " 04 74 82 22 2C 5E 80") {
    //Serial.println("num: "45");
    a = 45;
    delay(500);
  }
  else if (content.substring(1) == " 04 22 7A 22 2C 5E 81") {
    //Serial.println("num: "45");
    a = 45;
    delay(500);
  }
  else if (content.substring(1) == " 04 97 80 22 2C 5E 80") {
    //Serial.println("num: "45");
    a = 45;
    delay(500);
  }
  else if (content.substring(1) == " 04 2A 77 22 2C 5E 80") {
    //Serial.println("num: "46");
    a = 46;
    delay(500);
  }
  else if (content.substring(1) == " 04 67 7E 22 2C 5E 80") {
    //Serial.println("num: "46");
    a = 46;
    delay(500);
  }
  else if (content.substring(1) == " 04 CA 75 22 2C 5E 80") {
    //Serial.println("num: "46");
    a = 46;
    delay(500);
  }
  else if (content.substring(1) == " 04 70 7E 22 2C 5E 81") {
    //Serial.println("num: "47");
    a = 47;
    delay(500);
  }
  else if (content.substring(1) == " 04 29 7D 22 2C 5E 81") {
    //Serial.println("num: "47");
    a = 47;
    delay(500);
  }
  else if (content.substring(1) == " 04 37 7D 22 2C 5E 81") {
    //Serial.println("num: "48");
    a = 48;
    delay(500);
  }
  else if (content.substring(1) == " 04 07 7D 22 2C 5E 81") {
    //Serial.println("num: "1");
    a = 1;
    delay(500);
  }
  else if (content.substring(1) == " 04 5F 7E 22 2C 5E 80") {
    //Serial.println("num: "2");
    a = 2;
    delay(500);
  }
  else if (content.substring(1) == " 04 1C 80 22 2C 5E 80") {
    //Serial.println("num: "3");
    a = 3;
    delay(500);
  }
  else if (content.substring(1) == " 04 2B 76 22 2C 5E 80") {
    //Serial.println("num: "3");
    a = 3;
    delay(500);
  }
  else if (content.substring(1) == " 04 74 76 22 2C 5E 81") {
    //Serial.println("num: "4");
    a = 4;
    delay(500);
  }
  else if (content.substring(1) == " 04 51 76 22 2C 5E 81") {
    //Serial.println("num: "4");
    a = 4;
    delay(500);
  }
  else if (content.substring(1) == " 04 68 7E 22 2C 5E 81") {
    //Serial.println("num: "5");
    a = 5;
    delay(500);
  }
  else if (content.substring(1) == " 04 39 7D 22 2C 5E 81") {
    //Serial.println("num: "5");
    a = 5;
    delay(500);
  }
  else if (content.substring(1) == " 04 25 7D 22 2C 5E 81") {
    //Serial.println("num: "6");
    a = 6;
    delay(500);
  }
  else if (content.substring(1) == " 04 82 7E 22 2C 5E 80") {
    //Serial.println("num: "6");
    a = 6;
    delay(500);
  }
  else if (content.substring(1) == " 04 40 76 22 2C 5E 81") {
    //Serial.println("num: "7");
    a = 7;
    delay(500);
  }
  else if (content.substring(1) == " 04 8B 7A 22 2C 5E 80") {
    //Serial.println("num: "7");
    a = 7;
    delay(500);
  }
  else if (content.substring(1) == " 04 7C 7E 22 2C 5E 80") {
    //Serial.println("num: "7");
    a = 7;
    delay(500);
  }
  else if (content.substring(1) == " 04 31 7A 22 2C 5E 80") {
    //Serial.println("num: "8");
    a = 8;
    delay(500);
  }
  else if (content.substring(1) == " 04 7B 76 22 2C 5E 81") {
    //Serial.println("num: "8");
    a = 8;
    delay(500);
  }
  else if (content.substring(1) == " 04 83 7E 22 2C 5E 80") {
    //Serial.println("num: "8");
    a = 8;
    delay(500);
  }
  else if (content.substring(1) == " 04 83 79 22 2C 5E 80") {
    //Serial.println("num: "9");
    a = 9;
    delay(500);
  }
  else if (content.substring(1) == " 04 29 77 22 2C 5E 80") {
    //Serial.println("num: "9");
    a = 9;
    delay(500);
  }
  else if (content.substring(1) == " 04 4A 76 22 2C 5E 81") {
    //Serial.println("num: "9");
    a = 9;
    delay(500);
  }
  else if (content.substring(1) == " 04 FB 7D 22 2C 5E 80") {
    //Serial.println("num: "10");
    a = 10;
    delay(500);
  }
  else if (content.substring(1) == " 04 A6 75 22 2C 5E 80") {
    //Serial.println("num: "10");
    a = 10;
    delay(500);
  }
  else if (content.substring(1) == " 04 75 7E 22 2C 5E 81") {
    //Serial.println("num: "10");
    a = 10;
    delay(500);
  }
  else if (content.substring(1) == " 04 8C 80 22 2C 5E 80") {
    //Serial.println("num: "11");
    a = 11;
    delay(500);
  }
  else if (content.substring(1) == " 04 A8 7F 22 2C 5E 80") {
    //Serial.println("num: "11");
    a = 11;
    delay(500);
  }
  else if (content.substring(1) == " 0red junqiGG") {
    //Serial.println("num: "12");
    a = 12;
    delay(500);
  }
  else if (content.substring(1) == " 04 F5 7E 22 2C 5E 80") {
    //Serial.println("num: "13");
    a = 13;
    delay(500);
  }
  else if (content.substring(1) == " 04 1B 76 22 2C 5E 81") {
    //Serial.println("num: "14");
    a = 14;
    delay(500);
  }
  else if (content.substring(1) == " 04 41 75 22 2C 5E 80") {
    //Serial.println("num: "15");
    a = 15;
    delay(500);
  }
  else if (content.substring(1) == " 04 C2 76 22 2C 5E 80") {
    //Serial.println("num: "15");
    a = 15;
    delay(500);
  }
  else if (content.substring(1) == " 04 55 7E 22 2C 5E 80") {
    //Serial.println("num: "16");
    a = 16;
    delay(500);
  }
  else if (content.substring(1) == " 04 3C 7A 22 2C 5E 80") {
    //Serial.println("num: "16");
    a = 16;
    delay(500);
  }
  else if (content.substring(1) == " 04 C5 7D 22 2C 5E 80") {
    //Serial.println("num: "17");
    a = 17;
    delay(500);
  }
  else if (content.substring(1) == " 04 2F 77 22 2C 5E 81") {
    //Serial.println("num: "17");
    a = 17;
    delay(500);
  }
  else if (content.substring(1) == " 04 C9 7D 22 2C 5E 80") {
    //Serial.println("num: "18");
    a = 18;
    delay(500);
  }
  else if (content.substring(1) == " 04 1D 80 22 2C 5E 80") {
    //Serial.println("num: "18");
    a = 18;
    delay(500);
  }
  else if (content.substring(1) == " 04 9D 75 22 2C 5E 80") {
    //Serial.println("num: "19");
    a = 19;
    delay(500);
  }
  else if (content.substring(1) == " 04 A6 79 22 2C 5E 80") {
    //Serial.println("num: "19");
    a = 19;
    delay(500);
  }
  else if (content.substring(1) == " 04 46 76 22 2C 5E 81") {
    //Serial.println("num: "19");
    a = 19;
    delay(500);
  }
  else if (content.substring(1) == " 04 18 75 22 2C 5E 80") {
    //Serial.println("num: "20");
    a = 20;
    delay(500);
  }
  else if (content.substring(1) == " 04 AB 7F 22 2C 5E 80") {
    //Serial.println("num: "20");
    a = 20;
    delay(500);
  }
  else if (content.substring(1) == " 04 75 7E 22 2C 5E 80") {
    //Serial.println("num: "20");
    a = 20;
    delay(500);
  }
  else if (content.substring(1) == " 04 1A 75 22 2C 5E 80") {
    //Serial.println("num: "21");
    a = 21;
    delay(500);
  }
  else if (content.substring(1) == " 04 CB 75 22 2C 5E 80") {
    //Serial.println("num: "21");
    a = 21;
    delay(500);
  }
  else if (content.substring(1) == " 04 DB 84 22 2C 5E 80") {
    //Serial.println("num: "21");
    a = 21;
    delay(500);
  }
  else if (content.substring(1) == " 04 32 7A 22 2C 5E 80") {
    //Serial.println("num: "22");
    a = 22;
    delay(500);
  }
  else if (content.substring(1) == " 04 13 75 22 2C 5E 80") {
    //Serial.println("num: "22");
    a = 22;
    delay(500);
  }
  else if (content.substring(1) == " 04 44 75 22 2C 5E 80") {
    //Serial.println("num: "22");
    a = 22;
    delay(500);
  }
  else if (content.substring(1) == " 04 F1 78 22 2C 5E 80") {
    //Serial.println("num: "23");
    a = 23;
    delay(500);
  }
  else if (content.substring(1) == " 04 DA 84 22 2C 5E 80") {
    //Serial.println("num: "23");
    a = 23;
    delay(500);
  }
  else if (content.substring(1) == " 04 63 7E 22 2C 5E 80") {
    //Serial.println("num: "24");
    a = 24;
    delay(500);
  }
  else if (content.substring(1) == " 04 ED 84 22 2C 5E 80") {
    //Serial.println("num: "25");
    a = 25;
    delay(500);
  }
  else if (content.substring(1) == " 04 BA 7D 22 2C 5E 80") {
    //Serial.println("num: "26");
    a = 26;
    delay(500);
  }
  else if (content.substring(1) == " 04 1F 76 22 2C 5E 80") {
    //Serial.println("num: "27");
    a = 27;
    delay(500);
  }
  else if (content.substring(1) == " 04 6B 79 22 2C 5E 81") {
    //Serial.println("num: "27");
    a = 27;
    delay(500);
  }
  else if (content.substring(1) == " 04 FC 78 22 2C 5E 80") {
    //Serial.println("num: "28");
    a = 28;
    delay(500);
  }
  else if (content.substring(1) == " 04 75 76 22 2C 5E 81") {
    //Serial.println("num: "28");
    a = 28;
    delay(500);
  }
  else if (content.substring(1) == " 04 71 7D 22 2C 5E 81") {
    //Serial.println("num: "29");
    a = 29;
    delay(500);
  }
  else if (content.substring(1) == " 04 72 7E 22 2C 5E 81") {
    //Serial.println("num: "29");
    a = 29;
    delay(500);
  }
  else if (content.substring(1) == " 04 78 7E 22 2C 5E 81") {
    //Serial.println("num: "30");
    a = 30;
    delay(500);
  }
  else if (content.substring(1) == " 04 E9 80 22 2C 5E 80") {
    //Serial.println("num: "30");
    a = 30;
    delay(500);
  }
  else if (content.substring(1) == " 04 54 7A 22 2C 5E 81") {
    //Serial.println("num: "31");
    a = 31;
    delay(500);
  }
  else if (content.substring(1) == " 04 1A 80 22 2C 5E 80") {
    //Serial.println("num: "31");
    a = 31;
    delay(500);
  }
  else if (content.substring(1) == " 04 00 7D 22 2C 5E 81") {
    //Serial.println("num: "31");
    a = 31;
    delay(500);
  }
  else if (content.substring(1) == " 04 01 7E 22 2C 5E 81") {
    //Serial.println("num: "32");
    a = 32;
    delay(500);
  }
  else if (content.substring(1) == " 04 CD 75 22 2C 5E 80") {
    //Serial.println("num: "32");
    a = 32;
    delay(500);
  }
  else if (content.substring(1) == " 04 5C 7E 22 2C 5E 80") {
    //Serial.println("num: "32");
    a = 32;
    delay(500);
  }
  else if (content.substring(1) == " 04 28 7D 22 2C 5E 81") {
    //Serial.println("num: "33");
    a = 33;
    delay(500);
  }
  else if (content.substring(1) == " 04 E9 79 22 2C 5E 80") {
    //Serial.println("num: "33");
    a = 33;
    delay(500);
  }
  else if (content.substring(1) == " 04 31 7D 22 2C 5E 80") {
    //Serial.println("num: "33");
    a = 33;
    delay(500);
  }
  else if (content.substring(1) == " 04 46 7E 22 2C 5E 80") {
    //Serial.println("num: "34");
    a = 34;
    delay(500);
  }
  else if (content.substring(1) == " 04 D2 84 22 2C 5E 80") {
    //Serial.println("num: "34");
    a = 34;
    delay(500);
  }
  else if (content.substring(1) == " 04 E4 80 22 2C 5E 80") {
    //Serial.println("num: "34");
    a = 34;
    delay(500);
  }
  else if (content.substring(1) == " 04 AD 7F 22 2C 5E 80") {
    //Serial.println("num: "35");
    a = 35;
    delay(500);
  }
  else if (content.substring(1) == " 04 29 76 22 2C 5E 80") {
    //Serial.println("num: "35");
    a = 35;
    delay(500);
  }
  else if (content.substring(1) == " 04 2A 76 22 2C 5E 80") {
    //Serial.println("num: "36");
    a = 36;
    delay(500);
  }
  else if (content.substring(1) == " 04 3B 75 22 2C 5E 80") {
    //Serial.println("num: "37");
    a = 37;
    delay(500);
  }
  else if (content.substring(1) == " 04 40 7C 22 2C 5E 80") {
    //Serial.println("num: "38");
    a = 38;
    delay(500);
  }
  else if (content.substring(1) == " 04 20 80 22 2C 5E 80") {
    //Serial.println("num: "39");
    a = 39;
    delay(500);
  }
  else if (content.substring(1) == " 04 8C F8 B2 56 5D 80") {
    //Serial.println("num: "39");
    a = 39;
    delay(500);
  }
  else if (content.substring(1) == " 04 DB 75 22 2C 5E 80") {
    //Serial.println("num: "40");
    a = 40;
    delay(500);
  }
  else if (content.substring(1) == " 04 6D 7D 22 2C 5E 81") {
    //Serial.println("num: "40");
    a = 40;
    delay(500);
  }
  else if (content.substring(1) == " 04 A2 79 22 2C 5E 80") {
    //Serial.println("num: "41");
    a = 41;
    delay(500);
  }
  else if (content.substring(1) == " 04 31 77 22 2C 5E 81") {
    //Serial.println("num: "41");
    a = 41;
    delay(500);
  }
  else if (content.substring(1) == " 04 67 7D 22 2C 5E 81") {
    //Serial.println("num: "42");
    a = 42;
    delay(500);
  }
  else if (content.substring(1) == " 04 C8 34 02 C6 4E 80") {
    //Serial.println("num: "42");
    a = 42;
    delay(500);
  }
  else if (content.substring(1) == " 04 84 79 22 2C 5E 80") {
    //Serial.println("num: "43");
    a = 43;
    delay(500);
  }
  else if (content.substring(1) == " 04 3C 76 22 2C 5E 80") {
    //Serial.println("num: "43");
    a = 43;
    delay(500);
  }
  else if (content.substring(1) == " 04 31 76 22 2C 5E 80") {
    //Serial.println("num: "43");
    a = 43;
    delay(500);
  }
  else if (content.substring(1) == " 04 84 7E 22 2C 5E 81") {
    //Serial.println("num: "44");
    a = 44;
    delay(500);
  }
  else if (content.substring(1) == " 04 97 85 22 2C 5E 80") {
    //Serial.println("num: "44");
    a = 44;
    delay(500);
  }
  else if (content.substring(1) == " 04 08 7E 22 2C 5E 81") {
    //Serial.println("num: "44");
    a = 44;
    delay(500);
  }
  else if (content.substring(1) == " 04 0A 7D 22 2C 5E 81") {
    //Serial.println("num: "45");
    a = 45;
    delay(500);
  }
  else if (content.substring(1) == " 04 85 7E 22 2C 5E 81") {
    //Serial.println("num: "45");
    a = 45;
    delay(500);
  }
  else if (content.substring(1) == " 04 BE 7E 22 2C 5E 80") {
    //Serial.println("num: "45");
    a = 45;
    delay(500);
  }
  else if (content.substring(1) == " 04 81 7E 22 2C 5E 80") {
    //Serial.println("num: "46");
    a = 46;
    delay(500);
  }
  else if (content.substring(1) == " 04 C5 7E 22 2C 5E 80") {
    //Serial.println("num: "46");
    a = 46;
    delay(500);
  }
  else if (content.substring(1) == " 04 DF 84 22 2C 5E 80") {
    //Serial.println("num: "46");
    a = 46;
    delay(500);
  }
  else if (content.substring(1) == " 04 64 7E 22 2C 5E 81") {
    //Serial.println("num: "47");
    a = 47;
    delay(500);
  }
  else if (content.substring(1) == " 04 0F 7D 22 2C 5E 81") {
    //Serial.println("num: "47");
    a = 47;
    delay(500);
  }
  else if (content.substring(1) == " 04 6E 7D 22 2C 5E 81") {
    //Serial.println("num: "48");
    a = 48;
    delay(500);
  }
  //    Serial.print(content.substring(1));
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

void printHex(byte * buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
    content.concat(String(buffer[i] < 0x10 ? " 0" : " "));
    content.concat(String(buffer[i], HEX));
  }
}

void printDec(byte * buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
    content.concat(String(buffer[i] < 0x10 ? " 0" : " "));
    content.concat(String(buffer[i], DEC));
  }
}
