#include <DHT.h>

#define PIN_DHT 2
#define PIN_BUZZER 9
#define LED_VERDE 4
#define LED_AMARELO 6
#define LED_VERMELHO 7

DHT dht(PIN_DHT, DHT11);

float temperatura = 0.0;
float umidade = 0.0;
unsigned long lastPublish = 0;
const long publishInterval = 5000;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  Serial.println("Sistema iniciado.");
}

void loop() {
  if (millis() - lastPublish >= publishInterval) {
    temperatura = dht.readTemperature();
    umidade = dht.readHumidity();

    if (isnan(temperatura) || isnan(umidade)) {
      Serial.println("{\"erro\":\"Falha ao ler DHT\"}");
      return;
    }

    String estadoTemp = verificarEstadoTemperatura();
    String estadoUmi = verificarEstadoUmidade();

    // Envia JSON via serial
    Serial.print("{\"temperatura\":");
    Serial.print(temperatura);
    Serial.print(",\"umidade\":");
    Serial.print(umidade);
    Serial.print(",\"estado_temperatura\":\"");
    Serial.print(estadoTemp);
    Serial.print("\",\"estado_umidade\":\"");
    Serial.print(estadoUmi);
    Serial.println("\"}");

    lastPublish = millis();
  }
}

void desligarTudo() {
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(PIN_BUZZER, LOW);
}

String verificarEstadoTemperatura() {
  desligarTudo();
  String estado = "Desconhecido";

  if (temperatura >= 20 && temperatura < 35.25) {
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(PIN_BUZZER, HIGH);
    delay(300);
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(PIN_BUZZER, LOW);
    delay(300);
    estado = "HIPOTÉRMICO";
  } else if (temperatura >= 35.5 && temperatura < 37.25) {
    digitalWrite(LED_VERDE, HIGH);
    estado = "Normal";
  } else if (temperatura >= 37.5 && temperatura <= 39.5) {
    digitalWrite(LED_AMARELO, HIGH);
    estado = "Febre";
  } else if (temperatura > 39.75) {
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(PIN_BUZZER, HIGH);
    estado = "CRÍTICO";
  }

  return estado;
}

String verificarEstadoUmidade() {
  if (umidade < 30) {
    return "Desconfortavel, baixa";
  } else if (umidade >= 30 && umidade <= 60) {
    return "Ideal";
  } else {
    return "Desconfortavel, alta";
  }
}
