#include <WiFi.h>
#include <PubSubClient.h>

// Configurações WiFi (no Wokwi não conecta, só pra simular)
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Broker MQTT público (não usado no Wokwi, só placeholder)
const char* mqtt_server = "104.41.50.188";  // IP correto
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Simulador RFID - Digite o ID da tag e aperte ENTER:");

  // Conecta WiFi (simulado)
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" conectado.");

  // Configura servidor MQTT (simulado)
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  // Se não conectado, tenta conectar (simulado)
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Lê entrada Serial simulando tag RFID
  if (Serial.available() > 0) {
    String tagID = Serial.readStringUntil('\n');
    tagID.trim();
    if (tagID.length() > 0) {
      Serial.print("Tag RFID lida: ");
      Serial.println(tagID);

      // Simula publicar no MQTT
      if (client.connected()) {
        client.publish("rfid-moto/leituras", tagID.c_str());
        Serial.println("Publicado no MQTT (simulado).");
      } else {
        Serial.println("Não conectado ao MQTT.");
      }
    }
  }
  delay(100);
}
void reconnect() {
  Serial.print("Conectando ao MQTT...");
  while (!client.connected()) {
    if (client.connect("ESP32Simulado", "admin", "otm-password-VM#")) {
      Serial.println(" conectado.");
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente...");
      delay(2000);
    }
  }
}