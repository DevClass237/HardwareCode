#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>
#include "database.h"
#include <DIYables_Keypad.h>
#include <Ethernet.h>
// RFID
#define SS_PIN 53
#define RST_PIN 49
MFRC522 mfrc522(SS_PIN, RST_PIN);

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 100, 177);

int C5 = 523;
int D5 = 587;
int E5 = 659;
int F5 = 698;
int G5 = 783;
int a5 = 880;
int B5 = 987;
unsigned long startTime;
unsigned long interval = 20000;
// Teclado
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

// Outros
int buzzer = 11;
String PASSWORD_PROFESSOR = "1234";
String UID_PROFESSOR = "";

void setup()
{

  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  Ethernet.begin(mac, ip);
  Serial.println(Ethernet.localIP());
  mfrc522.PCD_Init();
  Serial.println("Iniciando sistema...");
  delay(1000);

  Serial.println("Conectando ao banco de dados...");
}
String print_tag();
void check_professor_uid(String uid);
void loop()
{
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  else
  {
    startTime = millis();
    String uid = print_tag();
    check_professor_uid(uid);
    UID_PROFESSOR = "";
  }
}
String print_tag()
{
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content += String(mfrc522.uid.uidByte[i], HEX);
  }
  tone(buzzer, 1000, 250);
  Serial.println();
  delay(250);
  return content;
}
void check_professor_uid(String uid)
{

  while (UID_PROFESSOR.length() < 4)
  {
    if (millis() - startTime <= interval)
    {
      char key = keypad.getKey();

      if (key)
      {
        tone(buzzer, G5, 250);
        delay(250);
        UID_PROFESSOR += key;
        if (UID_PROFESSOR.length() == 4)
        {

          String json = "{\"ProfessorMatricula\":" + UID_PROFESSOR + ",\"PocheteId\":\"" + uid + "\"}";
          Serial.println(json);
          break;
        }
      }
    }
    else if (millis() - startTime >= interval)
    {
      tone(buzzer, a5, 250);
      tone(buzzer, F5, 250);
      Serial.println("Time out");
      break;
    }
  }
}