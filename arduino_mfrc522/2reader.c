#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN                9          // Configurable, see typical pin layout above
#define SS_1_PIN              10          // Configurable, see typical pin layout above
#define SS_2_PIN               8          // Configurable, see typical pin layout above
#define TAG_LED_1_PIN          5          // COnfigurable, authorized card = blinking LED tag1
#define TAG_LED_2_PIN          6          // COnfigurable, authorized card = blinking LED tag2
#define READER_LED_1_PIN       4          // COnfigurable, identification by reader = blinking LED reader1
#define READER_LED_2_PIN       3          // COnfigurable, identification by reader = blinking LED reader2

#define NR_OF_READERS   2         // number of RC522 modules

byte ssPins[] = {SS_1_PIN, SS_2_PIN};

MFRC522 mfrc522[NR_OF_READERS];   // Create MFRC522 instance.

/**
   Initialize.
*/
void setup() {

  pinMode(TAG_LED_1_PIN, OUTPUT); //Set TAG_LED_1_PIN as an output
  pinMode(TAG_LED_2_PIN, OUTPUT); //Set TAG_LED_2_PIN as an output
  pinMode(READER_LED_1_PIN, OUTPUT); //Set READER_LED_1_PIN as an output
  pinMode(READER_LED_2_PIN, OUTPUT); //Set READER_LED_2_PIN as an output
  Serial.begin(9600);       // Initialize serial communications with the PC
  SPI.begin();        // Init SPI bus

  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN); // Init each MFRC522 card
  }
  Serial.println("Waiting for Tag ....");
  Serial.println();

}

/**
   Main loop.
*/
void loop() {

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
          digitalWrite (READER_LED_1_PIN, HIGH) ;    // Reader 1 LED On
          digitalWrite (TAG_LED_1_PIN, HIGH) ;       // Tag 1 LED On
          delay (2000) ;
          digitalWrite (READER_LED_1_PIN, LOW) ;     // Reader 1 LED Off
          digitalWrite (TAG_LED_1_PIN, LOW) ;        // Tag 1 LED Off
          delay (200) ;
        }
        else if (reader == 1)                       //identification Tag 1 for reader 2
        {
          Serial.print("Reader 2 ");
          Serial.println("Tag 1 ");
          Serial.print(card.substring(1));
          Serial.println();
          digitalWrite (READER_LED_2_PIN, HIGH) ;    // Reader 2 LED On
          digitalWrite (TAG_LED_1_PIN, HIGH) ;       // Tag 1 LED On
          delay (2000) ;
          digitalWrite (READER_LED_2_PIN, LOW) ;     // Reader 2 LED Off
          digitalWrite (TAG_LED_1_PIN, LOW) ;        // Tag 1 LED Off
          delay (200) ;
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
          digitalWrite (READER_LED_1_PIN, HIGH) ;    // Reader 1 LED On
          digitalWrite (TAG_LED_2_PIN, HIGH) ;       // Tag 2 LED On
          delay (2000) ;
          digitalWrite (READER_LED_1_PIN, LOW) ;     // Reader 1 LED Off
          digitalWrite (TAG_LED_2_PIN, LOW) ;        // Tag 2 LED Off
          delay (200) ;
        }
        else if (reader == 1)                       //identification Tag 2 for reader 2
        {
          Serial.print("Reader 2 ");
          Serial.println("Tag 2 ");
          Serial.print(card.substring(1));
          Serial.println();
          digitalWrite (READER_LED_2_PIN, HIGH) ;    // Reader 2 LED On
          digitalWrite (TAG_LED_2_PIN, HIGH) ;       // Tag 2 LED On
          delay (2000) ;
          digitalWrite (READER_LED_2_PIN, LOW) ;     // Reader 2 LED Off
          digitalWrite (TAG_LED_2_PIN, LOW) ;        // Tag 2 LED Off
          delay (200) ;
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
    } //if (mfrc522[reader].PICC_IsNewC
  } //for(uint8_t reader
}

/**
   Helper routine to dump a byte array as hex values to Serial.
*/
void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}