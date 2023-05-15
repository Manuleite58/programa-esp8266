#include <ESP8266WiFi.h>
//wifi mobil
#define MAX_INTENTOS 50
#define WIFI_SSID "wifi_leite"
#define WIFI_PASS "pass"
#define LED 14
int tempo = 500;
bool conectado = false;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  conectado = conectarWiFi();
}
void loop() {
  if (WiFi.status != WL_CONNECTED) {
    conectado = conectarWiFi;
    }
  if(conectado) escintila (tempo);
  else escintila (tempo/10);
  }
  void escintila(int espera){
    digitalWrite(LED, HIGH);
    delay(espera);
    digitalWrite(LED, LOW);
    delay(espera);
    }
bool conectarWiFi() {
  WiFi.mode(WIFI_STA); //indica modo station
  WiFi.disconnect();
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("\n\nAgardando pola WiFi ");
  int contador = 0;
  while(WiFi.status() !=WL_CONNECTED and contador < MAX_INTENTOS) {
  contador++;
  delay(500);
  Serial.print(".");
  }
  
  Serial.println("");

  if(contador < MAX_INTENTOS){
    Serial.print("conectado a WiFi coa IP: "); Serial.println(WiFi.localIP());
    conectado = true;
  }
  else{
    Serial.println("Non se puido conectar a WiFi");
    conectado = false;
  }
  return(conectado);
 }
