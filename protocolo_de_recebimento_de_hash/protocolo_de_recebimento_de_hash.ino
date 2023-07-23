#include <SoftwareSerial.h>
#include <ArduinoJson.h>  // Converter em Json

SoftwareSerial HC12(D3, D4);  // Esp8266
// Rx pino D1 (Ligar no Tx do outro)
// Tx pino D2 (Ligar no Rx do outro)

int tam, proximo = 0;
String img = "";


void protocolo() {
  StaticJsonDocument<300> data;
  String msg, mmm;

  deserializeJson(data, HC12);

  serializeJson(data, msg);
  Serial.println(msg.substring(2, 5));

  String id = msg.substring(2, 5);
  int cod = atoi(id.c_str());

  if (id == "000") {
    tam = data[id];
    if (tam != 0) {
      proximo = 1;
      img = "";
      Serial.println(tam);
    } else {
      HC12.write(proximo);
      Serial.print("Pedindo pra enviar dnv o pedaco: ");
      Serial.println(proximo);
      HC12.flush();
    }

  } else if (id == "###") {
    String aux = data[id];
    if (aux != "null" || aux != "") {
      img += String(aux);
      Serial.println("Adicionando ultimo pedaço");
      Serial.println(img);

      if (tam != img.length()) {
        HC12.write(0);
        Serial.println("Tamanho nao condiz. Pedindo pra enviar dnv");
      }else{
        delay(2000);
      }

    } else {
      HC12.write(proximo);
      Serial.print("Pedindo pra enviar dnv o pedaco: ");
      Serial.println(proximo);
      HC12.flush();
    }
  } else if (cod == proximo) {
    String aux = data[id];
    if (200 == aux.length() && aux != "null" || aux != "") {
      img += String(aux);
      Serial.println("Adicionando");
      proximo++;
    } else {
      HC12.write(proximo);
      Serial.print("Pedindo pra enviar dnv o pedaco: ");
      Serial.println(proximo);
      HC12.flush();
    }

  } else if (cod > proximo) {
    HC12.write(proximo);
    Serial.print("Pedindo pra enviar dnv o pedaco: ");
    Serial.println(proximo);
    HC12.flush();
    delay(1800);
  }

  Serial.println();
  // tam =  data["tam"];
}


void setup() {
  Serial.begin(2400);  // Porta Serial do computador
  HC12.begin(2400);    // Porta Serial do HC12
}
void loop() {

  // Enviar dados do sensor periodicamente
  // Se o intervalo de tempo for maior que 30s
  while (HC12.available()) {
    // Envia dados do sensor ao Banco de Dados
    protocolo();
  }
  //Serial.println("terminei");
  //HC12.flush();
  //delay(10000);
}