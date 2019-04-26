#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 8
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

int b1 = 0;
int b2 = 0;
int red_w = 3;
int yellow_w = 4;

void setup()
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("welcome! pls put your TAGS in the reader");
  Serial.println();
}

void loop()
{
  b1 = SCAN_ytags(b1);
  b2 = SCAN_rtags(b2);
  SUANFA();
}

int SCAN_ytags(int b1)
{
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
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "FC 16 2F 02")
  {
    Serial.println("红-司令");
    int b1 = 1;
    //    delay(2000);
    return b1;
  }
  else if (content.substring(1) == "2A 77 B3 65")
  {
    Serial.println("红-师长");
    int b1 = 3;
    return b1;
  }
  else   {
    ;
    delay(2000);
  }
}
int SCAN_rtags(int b2)
{
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
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "47 58 24 33")
  {
    Serial.println("黄-司令");
    int b2 = 1;
    return b2;
  }
  else if (content.substring(1) == "4C FB 2E 02")
  {
    Serial.println("黄-地雷");
    int b2 = 12;
    return b2;
  }
  else   {
    ;
    delay(1000);
  }
}
void SUANFA() {

  //比較大小，普通的情况
  if (b1 == 0 || b2 == 0) {
    Serial.println("no enough card");
  }
  else if (b1 < 10 && b2 < 10 && b1 < b2) {
    b1_win();
  } else if (b1 < 10 && b2 < 10 && b1 > b2) {
    b2_win();
  } else if (b1 < 10 && b2 < 10 && b1 == b2) {
    no_win();
    //吃掉军棋的情况
  } else if (b1 == 12) {
    end_ywin();
  } else if (b2 == 12) {
    end_rwin();
    //炸弹的情况
  } else if (b1 == 11 || b2 == 11) {
    no_win();
    //地雷的情况
  } else if (b1 == 10) {
    if (b2 == 9) {
      b2_win();
    } else if (b2 == 11) {
      no_win();
    } else {
      b1_win();
    }
  } else if (b2 == 10) {
    if (b1 == 9) {
      b1_win();
    } else if (b1 == 11) {
      no_win();
    } else {
      b2_win();
    }
  }
}


void b1_win() {
  Serial.println("red side win");
  digitalWrite(red_w, HIGH);
  delay(1000);
}
void b2_win() {
  Serial.println("yellow side win");
  digitalWrite(yellow_w, HIGH);
  delay(1000);
  return b1=0;
}
void no_win() {
  Serial.println("all out");
  digitalWrite(yellow_w, HIGH);
  digitalWrite(red_w, HIGH);
  delay(1000);
}
void end_rwin() {
  Serial.println("game over redside win");
  digitalWrite(red_w, HIGH);
  delay(400);
  digitalWrite(red_w, LOW);
  delay(400);
  digitalWrite(red_w, HIGH);
  delay(400);
  digitalWrite(red_w, LOW);
  delay(400);
  digitalWrite(red_w, HIGH);
  delay(400);
  digitalWrite(red_w, LOW);
}
void end_ywin() {
  Serial.println("game over yellowside win");
  digitalWrite(yellow_w, HIGH);
  delay(400);
  digitalWrite(yellow_w, LOW);
  delay(400);
  digitalWrite(yellow_w, HIGH);
  delay(400);
  digitalWrite(yellow_w, LOW);
  delay(400);
  digitalWrite(yellow_w, HIGH);
  delay(400);
  digitalWrite(yellow_w, LOW);
}
void ERROR_GAME() {
  Serial.println("game ERROR!!");
}