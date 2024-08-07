//@author: Vitoria Quadros
// github: vitoriacquadros
// date: 06/08/2024

#include <DHT.h>

#define DHTPIN 2     // Pino de dados do DHT11
#define DHTTYPE DHT11   // Tipo do sensor DHT

#define RED_PIN 3   // Pino para a cor vermelha do LED RGB
#define GREEN_PIN 4 // Pino para a cor verde do LED RGB
#define BLUE_PIN 5  // Pino para a cor azul do LED RGB
//#define Pin_led_sensor_gas_vermelho 13 //pino para cor vermelha do sensor de gás
#define Pin_led_sensor_gas_verde 12 
#define GAS_SENSOR_PIN A0 //pino analógico para o sensor de gás
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  
  dht.begin();
  
  // Configurar pinos do LED RGB como saída
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(GAS_SENSOR_PIN, INPUT);
//  pinMode(Pin_led_sensor_gas_vermelho, OUTPUT);
  pinMode(Pin_led_sensor_gas_verde, OUTPUT);
  
  setColor(255, 255, 255); // Branco
}

void loop() {
  // Esperar entre leituras
  delay(2000);
  
  // Leitura de umidade e temperatura
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  // leitura do sensor de gás (model MQ-2)

  int gasValue = analogRead(GAS_SENSOR_PIN);
  // Verificar se a leitura falhou
  if (isnan(h) || isnan(t)) {
    Serial.println("Falha na leitura do DHT11!");
    return;
  }
  
  if (gasValue >= 200)
  {
    Serial.println("Fumaça/gás detectado:");
    digitalWrite(Pin_led_sensor_gas_verde, HIGH);
 //   digitalWrite(Pin_led_sensor_gas_vermelho, HIGH);
  }
  else {
    Serial.println("Fumaça/gás não detectado");
    digitalWrite(Pin_led_sensor_gas_verde, LOW);  //  digitalWrite(Pin_led_sensor_gas_verde, LOW);
  //  digitalWrite(Pin_led_sensor_gas_vermelho, LOW);
  }
  // Imprimir valores no monitor serial
  Serial.print("Umidade: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" *C");
  Serial.print("Valor do gás: ");
  Serial.println(gasValue);
  
  // Ajustar a cor do LED RGB com base na temperatura
  if (t > 20) {
    // Quente: Vermelho
    setColor(255, 0, 0);
  } else if (t < 15) {
    // Frio: Azul
    setColor(0, 0, 255);
  } else {
    // Morno: Violeta
    setColor(128, 0, 128); // Valor aproximado para violeta
  }
}

// Função para definir a cor do LED RGB
void setColor(int red, int green, int blue) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}
