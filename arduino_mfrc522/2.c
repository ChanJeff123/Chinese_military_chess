#include <SPI.h>
#include <MFRC522.h>

int b1,b2;
int red_w = 3;
int yellow_w = 4;
#define RST_PIN   9
#define SS_1_PIN  10
#define SS_2_PIN  8

#define NR_OF_READERS   2    // number of RC522 modules
//void SUANFA();
byte ssPins[] = {SS_1_PIN, SS_2_PIN};
MFRC522 mfrc522[NR_OF_READERS];   // Create MFRC522 instance.

void setup() {
  Serial.begin(9600);
  SPI.begin();
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN); // Init each MFRC522 card
  }
  Serial.println("welcome! pls put your TAGS in the reader");
  Serial.println();
}
void loop() {
  SCAN_tags(&b1,&b2);
  SUANFA();
}

int SCAN_tags(int *b1,int *b2){
    *b1=1;
    *b2=3;
    return b1, b2;
}


void SUANFA() {
  //比較大小，普通的情况
  //    if (b1 == 0 || b2 == 0) {
  //      Serial.println("no enough card");
  //    }
  //    else
  if (b1 < 10 && b2 < 10 && b1 < b2) {
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
  return 0;
}
void b2_win() {
  Serial.println("yellow side win");
  digitalWrite(yellow_w, HIGH);
  delay(1000);
  return b1 = 0;
}
void no_win() {
  Serial.println("all out");
  digitalWrite(yellow_w, HIGH);
  digitalWrite(red_w, HIGH);
  delay(1000);
  return 0;
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
  return 0;
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
  return 0;
}
void ERROR_GAME() {
  Serial.println("game ERROR!!");
  return 0;
}

/**
   Helper routine to dump a byte array as hex values to Serial.
*/
void dump_byte_array(byte * buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}


for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
  // Look for new cards
  if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {
    Serial.print(F("Reader: "));
    Serial.print(reader);
    // Show some details of the PICC (that is: the tag/card)
    Serial.print(F(" Card UID:"));
    dump_byte_array(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size);
    Serial.println();
    Serial.print(F("PICC type: "));
    MFRC522::PICC_Type piccType = mfrc522[reader].PICC_GetType(mfrc522[reader].uid.sak);
    Serial.println(mfrc522[reader].PICC_GetTypeName(piccType));
    if (mfrc522[reader].uid.uidByte[0] == 140 &
        mfrc522[reader].uid.uidByte[1] == 120 &
        mfrc522[reader].uid.uidByte[2] == 34 &
        mfrc522[reader].uid.uidByte[3] == 43 &
        reader == 0 ) {
      Serial.println(F("pirmā karte atrasta"));
      a++;
    }
    if (mfrc522[reader].uid.uidByte[0] != 140 &
        mfrc522[reader].uid.uidByte[1] != 120 &
        mfrc522[reader].uid.uidByte[2] != 34 &
        mfrc522[reader].uid.uidByte[3] != 43 &
        reader == 0 ) {
      Serial.println(F("pirmā karte nodzes"));
      a = 0;
    }

    if (mfrc522[reader].uid.uidByte[0] == 5 &
        mfrc522[reader].uid.uidByte[1] == 233 &
        mfrc522[reader].uid.uidByte[2] == 26 &
        mfrc522[reader].uid.uidByte[3] == 43 &
        reader == 1 ) {
      Serial.println(F("otrā karte atrasta"));
      b++;
    }
    if (mfrc522[reader].uid.uidByte[0] != 5 &
        mfrc522[reader].uid.uidByte[1] != 233 &
        mfrc522[reader].uid.uidByte[2] != 26 &
        mfrc522[reader].uid.uidByte[3] != 43 &
        reader == 1 ) {
      Serial.println(F("otrā karte nodzēs"));
      b = 0;
    }

    if (mfrc522[reader].uid.uidByte[0] == 140 &
        mfrc522[reader].uid.uidByte[1] == 120 &
        mfrc522[reader].uid.uidByte[2] == 34 &
        mfrc522[reader].uid.uidByte[3] == 43 &
        reader == 1 ) {
      Serial.println(F("otrā karte nodzēs"));
      b = 0;
    }

    if (mfrc522[reader].uid.uidByte[0] == 5 &
        mfrc522[reader].uid.uidByte[1] == 233 &
        mfrc522[reader].uid.uidByte[2] == 26 &
        mfrc522[reader].uid.uidByte[3] == 43 &
        reader == 0 ) {
      Serial.println(F("pirmā karte nodzes"));
      a = 0;
    }
    Serial.println();

    // Halt PICC
    mfrc522[reader].PICC_HaltA();
    // Stop encryption on PCD
    mfrc522[reader].PCD_StopCrypto1();
  } //if (mfrc522[reader].PICC_IsNewC
} //for(uint8_t reader
if (a > 0 & b > 0)
{
  digitalWrite(LedPin, HIGH);
  delay(1000);
  digitalWrite(LedPin, LOW);
}
