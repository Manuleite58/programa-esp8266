#include <ESP8266WiFi.h>
#include <servo.h>
#include <PubSubClient.h>

//wifi mobil
#define MAX_INTENTOS 50
#define WIFI_SSID "wifi_leite"
#define WIFI_PASS "pass1234"
#define LED 14
int tempo = 500;
bool conectado = false;

//MQTT
#define MQTT_HOST IPAdress(52, 13, 116, 147)
#define MQTT_NOME_PORT 1883

//servo
#define SERVOPIN 0
servo motor;
#define MQTT_PUB_SERVO "wemos/robotica/servo"
#define MQTT_NOME_CLIENTE "cliente servo"

WifiClient espClient;
PubSubClient mqttClient(espClient);

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  motor.attach(SERVOPIN);  
  conectado = conectarWiFi();
  mqttClient.setServer (MQTT_HOST, MQTT_PORT);
  mqttClient.setCallback(callback);
}
void loop() {
  if (WiFi.status != WL_CONNECTED) {
    conectado = conectarWiFi();
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
void callback(String topic, byte* message, unsigned int len){
Serial.print("Nova mensaxe no topic: ");
Serial.print(" . Mensaxe: ");
String mensaxeTmp = "";
for(int i=0; i < len; i++){
Serial.print((char)message[i]);
mensaxeTmp += (char)message[i];
}
Serial.println ();
}   

//funcion que conecta a rede    
bool conectarWiFi() {
  WiFi.mode(WIFI_STA); //indica modo station
  WiFi.disconnect(); //desconecta conexion previa
  WiFi.begin(WIFI_SSID, WIFI_PASS); //inicia conexion nova
  Serial.print("\n\nAgardando pola WiFi "); 
  int contador = 0; //comproba o estado da wifi
  while(WiFi.status() !=WL_CONNECTED and contador < MAX_INTENTOS) {
  contador++;
  delay(500);
  Serial.print(".");
  }
  
  Serial.println("");

//informa do estado da conexion e IP en caso de exito

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
