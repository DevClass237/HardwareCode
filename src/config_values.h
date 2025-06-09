#ifndef CONFIG_VALUES_H
#define CONFIG_VALUES_H

#include <Arduino.h>
#include <Ethernet.h>

// Declarations only (no definitions!)
extern byte ARDUINO_MAC[];
extern IPAddress ARDUINO_IP;
extern IPAddress DB_HOST;
extern IPAddress GATEWAY;
extern IPAddress SUBNET;

extern char DB_USER[];
extern char DB_PASS[];
extern char DB_NAME[];

#endif

