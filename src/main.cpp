#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>
#include <DIYables_Keypad.h>
#include "database.h"
#include "config.h"
#include <Ethernet.h>


// RFID
#define SS_PIN 53
#define RST_PIN 49
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Teclado
const byte ROWS = 4;
const byte COLS = 4;
byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] = {26, 27, 28, 29};

char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

DIYables_Keypad keypad = DIYables_Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Outros
int buzzer = 11;
String PASSWORD_PROFESSOR = "1234";
String inputPassword = "";

void setup() {
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  Serial.println("Iniciando sistema...");

  Ethernet.begin(ARDUINO_MAC, ARDUINO_IP, GATEWAY, SUBNET);
  delay(1000);

  Serial.println("Conectando ao banco de dados...");
  conectarBanco();
}

void loop() {
  // Autenticação
  while (inputPassword != PASSWORD_PROFESSOR) {
    char key = keypad.getKey();

    if (key) {
      tone(buzzer, 1000, 200);
      delay(200);

      if (key == '*') {
        if (inputPassword.length() > 0) {
          inputPassword.remove(inputPassword.length() - 1);
          Serial.println("Backspace");
        }
      } else {
        inputPassword += key;
        Serial.print("Digitado: ");
        Serial.println(inputPassword);
      }

      if (inputPassword.length() == 4) {
        if (inputPassword == PASSWORD_PROFESSOR) {
          Serial.println("✅ Acesso permitido!");
          break;
        } else {
          Serial.println("❌ Senha incorreta. Tente novamente.");
          inputPassword = "";
        }
      }
    }
  }

  // Leitura do cartão
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    Serial.println("Aproxime o cartão...");
    delay(1000);
  } else {
    String uid = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      uid += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
      uid += String(mfrc522.uid.uidByte[i], HEX);
    }
    uid.toUpperCase();
    Serial.print("Cartão lido: ");
    Serial.println(uid);

    tone(buzzer, 800, 300);
    delay(500);

    inserirDados(uid, "12345678");  // Dados fictícios
  }

  inputPassword = "";  // Reset senha para o próximo

  Serial.println("Aguardando próximo...");
  delay(3000);
}
