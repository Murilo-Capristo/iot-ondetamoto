#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqtt_server = "104.41.50.188";  
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

// Variável fixa durante a execução
String setorID = "";

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Simulador RFID");

  // Conecta WiFi 
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" conectado.");

  // Configura servidor MQTT
  client.setServer(mqtt_server, mqtt_port);

  // Pede o setor só uma vez
  Serial.println("Digite o ID do setor e aperte ENTER:");
  while (setorID == "") {
    if (Serial.available() > 0) {
      setorID = Serial.readStringUntil('\n');
      setorID.trim();
      if (setorID.length() > 0) {
        Serial.print("Setor definido: ");
        Serial.println(setorID);
        Serial.println("Agora digite a TAG RFID da moto e aperte ENTER:");
      }
    }
  }
}

void loop() {
  // Se não conectado, tenta conectar
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Lê entrada Serial simulando tag RFID da moto
  if (Serial.available() > 0) {
    String motoID = Serial.readStringUntil('\n');
    motoID.trim();

    if (motoID.length() > 0) {
      Serial.print("Moto lida: ");
      Serial.println(motoID);

      // Monta JSON simples com setor + moto
      String mensagem = "{ \"setor\": \"" + setorID + "\", \"moto\": \"" + motoID + "\" }";

      // Publica no MQTT
      if (client.connected()) {
        client.publish("rfid-moto/leituras", mensagem.c_str());
        Serial.print("Publicado no MQTT: ");
        Serial.println(mensagem);
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
