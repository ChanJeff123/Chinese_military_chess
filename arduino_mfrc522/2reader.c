#include <SPI.h>
#include <MFRC522.h>

int A;
int B = 0;
int SUM_C= B*100+B2;
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

void(* resetFunc) (void) = 0; //制造重启命令

// int SCAN_ytags(int b1)
// {
//   // Look for new cards
//   if ( ! mfrc522.PICC_IsNewCardPresent())
//   {
//     return;
//   }
//   // Select one of the cards
//   if ( ! mfrc522.PICC_ReadCardSerial())
//   {
//     return;
//   }
//   //Show UID on serial monitor
//   Serial.print("UID tag :");
//   String content = "";
//   byte letter;
//   for (byte i = 0; i < mfrc522.uid.size; i++)
//   {
//     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
//     Serial.print(mfrc522.uid.uidByte[i], HEX);
//     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
//     content.concat(String(mfrc522.uid.uidByte[i], HEX));
//   }
//   Serial.println();
//   Serial.print("Message : ");
//   content.toUpperCase();
//   if (content.substring(1) == "FC 16 2F 02")
//   {
//     Serial.println("红-司令");
//     int b1 = 1;
//     //    delay(2000);
//     return b1;
//   }
//   else if (content.substring(1) == "2A 77 B3 65")
//   {
//     Serial.println("红-师长");
//     int b1 = 3;
//     return b1;
//   }
//   else   {
//     ;
//     delay(2000);
//   }
// }
int SCAN_rtags(int b2) {
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    // Look for new cards

    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {
      Serial.println();
      String card = "";   // String of tag ID, delceration of attribute card

      for (byte i = 0; i < mfrc522[reader].uid.size; i++) //loop for write card ID in HEXA to string
      {
        card.concat(String(mfrc522[reader].uid.uidByte[i] < 0x10 ? " 0" : " "));
        card.concat(String(mfrc522[reader].uid.uidByte[i], HEX));
      }

      card.toUpperCase();
      if (card.substring(1) == "04 25 CC 22 30 4D 81") {  //Comparation of Tag 1 (INSERT HERE YOUR ID OF TAG 1)
        if (reader == 0)                            //identification Tag 1 for reader 1
        {
          Serial.print("Reader 1 ");
          Serial.println("Tag 1 ");
          Serial.print(card.substring(1));
          Serial.println();
        }
        else if (reader == 1)                       //identification Tag 1 for reader 2
        {
          Serial.print("Reader 2 ");
          Serial.println("Tag 1 ");
          Serial.print(card.substring(1));
          Serial.println();
        }
        delay(300);
      }
      else if (card.substring(1) == "04 1D CC 22 30 4D 81") {  //Comparation of Tag 1 (INSERT HERE YOUR ID OF TAG 1)
        if (reader == 0)                            //identification Tag 2 for reader 1
        {
          Serial.print("Reader 1 ");
          Serial.println("Tag 2 ");
          Serial.print(card.substring(1));
          Serial.println();
        }
        else if (reader == 1)                       //identification Tag 2 for reader 2
        {
          Serial.print("Reader 2 ");
          Serial.println("Tag 2 ");
          Serial.print(card.substring(1));
          Serial.println();
        }
        delay(300);
      }
      else {
        Serial.println("Different Tag ");
        Serial.println(card.substring(1));
        if (reader == 0)
        {
          Serial.println("Reader 1 ");
        }
        else if (reader == 1)
        {
          Serial.println("Reader 2 ");
        }

        Serial.println();
        delay(300);
      }
      // Halt PICC
      mfrc522[reader].PICC_HaltA();
      // Stop encryption on PCD
      mfrc522[reader].PCD_StopCrypto1();
    }
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
//一起出局的情况

if (((SUM_C %101==0) &&(SUM_C /101<10)) ||((SUM_C % 100 == 11)&&(SUM_C /100<12))\
||((SUM_C / 100 == 11)&&(SUM_C <1113))){
    A=1;
    return A;
}
else if (102,103,104,105,106,107,108,109,203,\
204,205,206,207,208,209,304,305,306,307,308,\
309,405,406,407,408,409,506,507,508,509,607,\
608,609,708,709,809,910) {
    A=2;
    return A;
}
else if (102,103,104,105,106,107,108,109,203,\
204,205,206,207,208,209,304,305,306,307,308,\
309,405,406,407,408,409,506,507,508,509,607,\
608,609,708,709,809,910) {
    A=2;
    return A;
}


switch (A)
{
case 1:
  Serial.println("all out");
  digitalWrite(yellow_w, HIGH);
  digitalWrite(red_w, HIGH);
  delay(1000);
  break;
case 2:
  Serial.println("red side win");
  digitalWrite(red_w, HIGH);
  delay(1000);
  break;
case 3:
  Serial.println("yellow side win");
  digitalWrite(yellow_w, HIGH);
  delay(1000);
  break;
case 4:
  Serial.println("game over redside win");
  for (i = 1; i <= 5; i++) {
    digitalWrite(red_w, HIGH);
    delay(400);
    digitalWrite(red_w, LOW);
    delay(400);
  }
  break;
case 5:
  Serial.println("game over yellowside win");
  for (i = 1; i <= 5; i++) {
    digitalWrite(yellow_w, HIGH);
    delay(400);
    digitalWrite(yellow_w, LOW);
    delay(400);
  }
  break;
default:
  Serial.println("ERROR!!!");
  break;
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