#include <Arduino.h>
#include <SPI.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h> //Bliblioteca para executar comandos no SQL

//Configurações de Rede
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);
IPAddress server_addr(192, 168, 1, 100);

//Acesso ao Banco de Dados
char user[] = ""; //Substituir no futuro
char password[] = ""; //Substituir no futuro

//Objetos
EthernetClient;
MySQL_Connection conn(Client*(&client));

//Funçaõ responsavel por conectar ao banco de da
void ConectarBanco() {

    Ethernet.begin(mac, ip);
     
}

