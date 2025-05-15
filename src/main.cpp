#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>
#include <DIYables_Keypad.h>

MFRC522 mfrc522(53, 49);
const byte ROWS = 4;
const byte COLS = 4;
int C5 = 523;
int Cs5 = 554;
int D5 = 587;
int Ds5 = 622;
int E5 = 659;
int F5 = 698;
int Fs5 = 739;
int G5 = 783;
int Gs5 = 830;
int a5 = 880;
int As5 = 932;
int B5 = 987;
byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] = {26, 27, 28, 29};
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
DIYables_Keypad keypad = DIYables_Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
int InBuzzerD48 = 11;
void setup()
{
  // put your setup code here, to run once:
  pinMode(InBuzzerD48, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Indentify yourself");
}

String PASSWORD_PROFESSOR = "1234";
String UID_PROFESSOR = "";

void loop()
{

  while (UID_PROFESSOR != PASSWORD_PROFESSOR)
  {
    char key = keypad.getKey();

    if (key)
    {
      tone(InBuzzerD48, G5, 500);
      delay(500);
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
      if (UID_PROFESSOR.length() == 4)
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

  for (int i = 0; i < 5; i++)
  {
    if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial())
    {
      Serial.println("No card found");
    }
    else
    {

      Serial.print("UID tag: ");
      String content = "";
      for (byte i = 0; i < mfrc522.uid.size; i++)
      {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        content += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
        content += String(mfrc522.uid.uidByte[i], HEX);
      }
      Serial.println();
      tone(InBuzzerD48, G5, 500);
      delay(500);
      break;
    }
    delay(1000);
  }

  UID_PROFESSOR = "";
}