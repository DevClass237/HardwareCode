#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <Ethernet.h>
#include "config.h"
#include "database.h"

EthernetClient client;
MySQL_Connection conn((Client *)&client);

void conectarBanco() {
  if (conn.connect(DB_HOST, 3306, DB_USER, DB_PASS)) {
    Serial.println("✅ Conectado ao banco de dados.");
  } else {
    Serial.println("❌ FALHA na conexão com o banco.");
  }
}

void inserirDados(String conteudo1, String conteudo2) {
  if (conn.connected()) {
    char query[256];
    sprintf(query,
            "INSERT INTO %s.dados_temporarios (conteudo1, conteudo2) VALUES ('%s', '%s');",
            DB_NAME, conteudo1.c_str(), conteudo2.c_str());

    MySQL_Cursor *cur = new MySQL_Cursor(&conn);
    cur->execute(query);
    delete cur;

    Serial.println("📥 Dados inseridos no banco.");
  } else {
    Serial.println("⚠️ Banco desconectado.");
  }
}
