#include <SPI.h>
#include <MFRC522.h>

int b1,b2;
int red_w = 3;
int yellow_w = 4;

#define RST_PIN   9
#define SS_1_PIN  10
#define SS_2_PIN  8
#define NR_OF_READERS   2    // number of RC522 modules

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

void(* resetFunc) (void) = 0; //制造重启命令

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
int SCAN_tags(int X,int Y)
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
    int X = 1;
    //    delay(2000);
    return b1;
  }
  else if (content.substring(1) == "47 58 24 33")
  {
    Serial.println("黄-师长");
    int Y = 3;
    return b2;
  }
  else   {
    ;
    delay(2000);
  }
}
void loop() {
  for (int a=0;a<3;a++){
      if (a==0){
           ;
           continue;
      }
      else if (a==1) {
          /* code */
      }
      else if (a ==2)
      {
          SCAN_tags(X,Y);
          SUANFA();
          resetFunc();      //重启程序开始
      }

  }
  
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