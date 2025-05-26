#include "config.h"
#include <Arduino.h>

// Rede
byte ARDUINO_MAC[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ARDUINO_IP(192, 168, 0, 200);
IPAddress DB_HOST(10, 21, 1, 92);
IPAddress GATEWAY(192, 168, 0, 1);
IPAddress SUBNET(255, 255, 255, 0);

// Banco de dados
char DB_USER[] = "beta";
char DB_PASS[] = "";
char DB_NAME[] = "pochetesenai";
