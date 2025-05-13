#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>
#include <DIYables_Keypad.h>

MFRC522 mfrc522(53, 49);
const byte ROWS = 4;
const byte COLS = 4;

byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] = {26, 27, 28, 29};

char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
DIYables_Keypad keypad = DIYables_Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup()
{
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Indentify yourself");
}

String PASSWORD_PROFESSOR = "12345678";
String UID_PROFESSOR = "";

void loop()
{
  while (UID_PROFESSOR != PASSWORD_PROFESSOR)
  {
    char key = keypad.getKey();

    if (key)
    {

      if (key == '*')
      {
        if (UID_PROFESSOR.length() > 0)
        {
          UID_PROFESSOR.remove(UID_PROFESSOR.length() - 1);
          Serial.println("Backspace");
        }
      }
      else
      {
        UID_PROFESSOR += key;
        Serial.print("Typed: ");
        Serial.println(UID_PROFESSOR);
      }
      if (UID_PROFESSOR.length() == 8)
      {
        if (UID_PROFESSOR == PASSWORD_PROFESSOR)
        {
          Serial.println("Access Granted");
          break;
        }
        else
        {
          Serial.println("Wrong password, try again");
          UID_PROFESSOR = "";
        }
      }
    }
  }

  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial())
  {
    String uidString = "";
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
      if (mfrc522.uid.uidByte[i] < 0x10)
        uidString += "0";
      uidString += String(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.print("RFID UID: ");
    Serial.println(uidString);

    mfrc522.PICC_HaltA();
  }
  UID_PROFESSOR = "";
}