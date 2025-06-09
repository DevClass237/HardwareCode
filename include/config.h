#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>

#include <IPAddress.h>

// Rede
extern byte ARDUINO_MAC[];
extern IPAddress ARDUINO_IP;
extern IPAddress DB_HOST;
extern IPAddress GATEWAY;
extern IPAddress SUBNET;

// Banco de dados
extern char DB_USER[];
extern char DB_PASS[];
extern char DB_NAME[];

#endif
