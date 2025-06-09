#include <Ethernet.h>
#include <config_values.h>
// Assuming same MAC/IP setup as before
EthernetClient client;
IPAddress apiServer(192, 168, 0, 50);


void enviarParaAPI(String uid, String senha) {
  if (client.connect(apiServer, 7054)) {
    Serial.println("🌐 Conectado à API");

    // JSON string
    String json = "{\"Uid\":\"" + uid + "\",\"Password\":\"" + senha + "\"}";

    // HTTP POST request
    client.println("POST /api/access HTTP/1.1");
    client.println("Host: 192.168.0.50");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(json.length());
    client.println();
    client.println(json);

    // Debug response
    while (client.connected()) {
      if (client.available()) {
        String line = client.readStringUntil('\n');
        Serial.println(line);
      }
    }

    client.stop();
  } else {
    Serial.println("❌ Falha na conexão com a API");
  }
}
