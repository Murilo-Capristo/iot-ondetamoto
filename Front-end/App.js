import React, { useEffect, useState } from 'react';
import { View, Text, ScrollView, StyleSheet } from 'react-native';
import { Client, Message } from 'paho-mqtt';

export default function App() {
  const [messages, setMessages] = useState([]);

  const mensagens = [];

  const verificarMensagens = (msg) => {
    let i = 0;
    for (i in mensagens) {
      if (mensagens[i] === msg) {
        return " Saindo Do Setor"; 
      }
    }
    mensagens.push(msg);
    return " Entrando No Setor";
  } 

  useEffect(() => {
    const client = new Client(
      '104.41.50.188',
      8080,
      '/mqtt',
      'clientId-' + Math.random().toString(16).substr(2, 8)
    );

    client.connect({
      userName: 'admin',
      password: 'otm-password-VM#',
      useSSL: false,
      onSuccess: () => {
        console.log('MQTT conectado');
        client.subscribe('rfid-moto/leituras');
      },
      onFailure: (err) => {
        console.log('Erro conexão MQTT:', err);
      },
    });

    client.onMessageArrived = (message) => {
      console.log(`Mensagem no tópico ${message.destinationName}: ${message.payloadString}`);
      setMessages((oldMsgs) => [...oldMsgs, message.payloadString]);
    };

    client.onConnectionLost = (responseObject) => {
      if (responseObject.errorCode !== 0) {
        console.log('Conexão perdida: ' + responseObject.errorMessage);
      }
    };

    return () => {
      if (client.isConnected()) client.disconnect();
    };
  }, []);

  return (
    <View style={styles.container}>
      <Text style={styles.title}>OndeTaMoto?</Text>
      <Text style={styles.subtitle}>Leitura RFID Recebidas:</Text>
      <ScrollView style={styles.scroll}>
        {messages.map((msg, index) => (
          <View key={index} style={styles.messageBox}>
            <Text style={styles.messageText}>{msg} {verificarMensagens(msg)}</Text>
          </View>
        ))}
      </ScrollView>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fce4ec', // rosa claro
    padding: 20,
    paddingTop: 60,
  },
  title: {
    fontSize: 32,
    fontWeight: '900',
    color: '#880e4f', // rosa escuro
    textAlign: 'center',
    marginBottom: 15,
    fontFamily: 'sans-serif-condensed',
  },
  subtitle: {
    fontSize: 20,
    fontWeight: '700',
    color: '#ad1457', // rosa médio
    marginBottom: 10,
  },
  scroll: {
    marginTop: 5,
  },
  messageBox: {
    backgroundColor: '#f8bbd0', // rosa médio claro
    padding: 12,
    borderRadius: 10,
    marginBottom: 8,
    shadowColor: '#ad1457',
    shadowOffset: { width: 0, height: 2 },
    shadowOpacity: 0.3,
    shadowRadius: 4,
    elevation: 3,
  },
  messageText: {
    color: '#4a148c', // roxo escuro para contraste
    fontSize: 16,
  },
});
