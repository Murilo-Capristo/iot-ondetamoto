# 📡 iot-ondetamoto

Projeto de IoT para rastreamento de entrada e saída de motos via RFID, desenvolvido como solução para problemas de organização de frotas na startup **Mottu**.

---
## 🧑‍💻 Equipe

- Guilherme Romanholi Santos - RM557462
- Murilo Capristo - RM556794
- Nicolas Guinante Cavalcanti - RM557844

---

## 📋 Como testar o projeto

### 📦 1. Clone o repositório

```bash
git clone https://github.com/Murilo-Capristo/iot-ondetamoto
cd iot-ondetamoto
```

---

### 📲 2. Rode o aplicativo mobile

O app foi desenvolvido em **React Native com Expo**.

##  Como Rodar o Projeto?
```bash

- git clone https://github.com/Murilo-Capristo/mobile-ondetamoto2.git
- cd mobile-ondetamoto2
- npm i
- npx expo start

```

Use o aplicativo **Expo Go** no celular para escanear o QR Code.

---

### 🤖 3. Simule o hardware com Wokwi

O ESP32 simula a leitura de tags RFID.

1. Acesse [https://wokwi.com/projects/443560723871547393](https://wokwi.com/projects/443560723871547393)
2. Rode o Projeto
3. Siga as Instruções

No terminal serial do Wokwi, digite manualmente os IDs simulando a leitura de tags.

---


## 🧱 Arquitetura da Solução

```mermaid
flowchart LR
    MOTO["Moto c/ Tag RFID"]
    ESP32(["ESP32<br>(Leitura RFID + SetorId)"])
    MOSQUITTO["Broker Mosquitto<br>(VM)"]
    NODERED["Node-RED<br>(VM)"]
    DB[(Banco de Dados)]
    BACKEND["Backend .NET<br>(API REST)"]
    FRONTEND["Frontend Web/App Mobile"]

    MOTO -- "Tag RFID lida" --> ESP32
    ESP32 -- "MQTT (SetorId + MotoId)" --> MOSQUITTO
    MOSQUITTO -- "MQTT (repasse de mensagem)" --> NODERED
    NODERED -- "Processa & Insere<br>no Banco de Dados" --> DB
    BACKEND -- "Consulta dados" --> DB
    FRONTEND -- "Consome API" --> BACKEND
    BACKEND -- "Fornece dados via API" --> FRONTEND

```

## ✅ Funcionalidades implementadas

- Simulação de leitura RFID via ESP32
- Publicação MQTT no tópico `rfid-moto/leituras`
- Processamento da mensagem no Node-RED
- Interface web com histórico de leituras
- App mobile com verificação de entrada/saída de motos
- Backend em Java com API REST
- Integração com banco de dados

---


