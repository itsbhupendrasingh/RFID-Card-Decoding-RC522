/*
 * UID- Unique ID
 * 
 */

#include <SPI.h> 
#include <MFRC522.h> 

byte ReadCard[4];     // Array that will hold UID of the RFID card.
int ScanDone;

MFRC522 mfrc522(10, 9);   // (SDA pin, RST pin)
MFRC522::MIFARE_Key key;          // Creates MIFARE key instance.

void setup()
{
  Serial.begin(9600);
  SPI.begin(); 
  mfrc522.PCD_Init(); 
  Serial.println("RFID initiated.");
  Serial.println("Please Tab your Card to the RFID Reader");

  do {
    ScanDone = scan_UID();     // Loops getID library function until reading process is done.
  }
  
  while (!ScanDone);
}

void loop()
{
scan_UID(); 
}


int scan_UID() // Function to read RFID Card UID
{
  if ( ! mfrc522.PICC_IsNewCardPresent())  // If statement that looks for new cards.
  {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial())    // If statement that selects one of the cards.
  {
    return;
  }
  
  Serial.print("Hi, Your Card UID is: ");    
  for (int i = 0; i < mfrc522.uid.size; i++) {  
    ReadCard[i] = mfrc522.uid.uidByte[i];   
    Serial.print(ReadCard[i], HEX);         
  }
  Serial.println("");
  mfrc522.PICC_HaltA();     // Halt the Card Scanning
}
