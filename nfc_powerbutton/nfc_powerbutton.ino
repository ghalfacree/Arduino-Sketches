/**************************************************************************/
/*! 
    NFC-based power switch authentication utility.
    Based heavily on iso14443a_uid.pde, licensed under BSD by Adafruit Industries.
    Written by Gareth Halfacree
    http://freelance.halfacree.co.uk
*/
/**************************************************************************/
#include <Wire.h>
#include <Adafruit_NFCShield_I2C.h>

#define IRQ   (2)
#define RESET (3)  // Not connected by default on the NFC Shield

Adafruit_NFCShield_I2C nfc(IRQ, RESET);

void setup(void) {
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
  Serial.begin(115200);

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("No PN53x NFC scanner detected; scanning disabled.");
    while (1); // halt
  }
  
  // Got ok data, print it out!
  Serial.print("Found NFC scanner model PN5"); Serial.print((versiondata>>24) & 0xFF, HEX);
  Serial.print(", firmware version "); Serial.print((versiondata>>16) & 0xFF, DEC); 
  Serial.print('.'); Serial.print((versiondata>>8) & 0xFF, DEC); Serial.println(".");
  
  // Set the max number of retry attempts to read from a card
  // This prevents us from waiting forever for a card, which is
  // the default behaviour of the PN532.
  nfc.setPassiveActivationRetries(0xFF);
  
  // configure board to read RFID tags
  nfc.SAMConfig();
    
  Serial.println("Waiting for NFC tag...");
}

void loop(void) {
  uint8_t storedUid[] = { 0x8, 0x251, 0x207, 0x195, 0, 0, 0 }; // The UID of the tag which can turn the PC on
  boolean success;
  boolean verified = false;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  
  // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);
  
  if (success) {
    Serial.println("");
    Serial.print("NFC tag detected, UID:");
    for (uint8_t i=0; i < uidLength; i++) 
    {
      Serial.print(" 0x");Serial.print(uid[i]);
      if (uid[i] == storedUid[i]) {
       verified = true; }
    }
    Serial.println("");
    if ( verified == false ) {
      Serial.println("UID invalid; taking no action."); }
    else {
      Serial.println("UID valid; toggling power switch.");
      digitalWrite(8, HIGH);
      delay(500);
      digitalWrite(8, LOW);}
    // Wait 1 second before continuing
    verified = false;
    Serial.println("");
    delay(1000);
    Serial.println("Waiting for NFC tag...");
  }
  else
  {
    // PN532 probably timed out waiting for a card
    Serial.println("Timed out waiting for a card.");
  }
}
