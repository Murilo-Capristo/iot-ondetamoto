# 📡 iot-ondetamoto

Projeto de IoT para rastreamento de entrada e saída de motos via RFID, desenvolvido como solução para problemas de organização de frotas na startup **Mottu**.

---

## 📋 Como testar o projeto

### 🖥️ 1. Suba a VM no Azure

Execute os comandos listados no arquivo `azure.txt` (fornecido na entrega) para iniciar a máquina virtual com:

- Mosquitto (broker MQTT)
- Node-RED

> A VM será responsável por receber dados do ESP32 e repassar ao backend (em construção).

---

### 📦 2. Clone o repositório

```bash
git clone https://github.com/Murilo-Capristo/iot-ondetamoto.git
cd iot-ondetamoto
```

### 📲 3. Rode o aplicativo mobile
O app foi desenvolvido em React Native com Expo.

```bash
cd Front-end
npm install
npx expo start
```

### 🤖 4. Simule o hardware com Wokwi
O ESP32 simula a leitura de tags RFID.

1. Acesse https://wokwi.com
2. Crie um novo projeto
3. Substitua o conteúdo pelo código da pasta:
```bash
Esp-32-Wokwi/
```



