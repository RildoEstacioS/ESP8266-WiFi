#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "ESP8266";         // Nome da sua rede Wi-Fi
const char* password = "12345678";     // Senha da sua rede Wi-Fi


// Defina os pinos GPIO para os LEDs
uint8_t equipamento1pin = 5;
bool equipamento1Status  = LOW;

uint8_t equipamento2pin = 4;
bool equipamento2Status  = LOW;

//Adicionar Variaveis para equip. 3 e 4

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);

  IPAddress ip(192, 168, 1, 100);  // Defina o endereço IP estático desejado
  IPAddress gateway(192, 168, 1, 1);  // Endereço IP do gateway da sua rede
  IPAddress subnet(255, 255, 255, 0);  // Máscara de sub-rede da sua rede
 
  // Configuração dos pinos dos LEDs como saída
  pinMode(equipamento1pin, OUTPUT);
  pinMode(equipamento2pin, OUTPUT);

  // Conectar-se à rede Wi-Fi
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(ip, gateway, subnet);
  delay(100);

  // Definir rotas para o servidor web
  server.on("/",  handleRoot);
  server.on("/led1on",  handleEquip1On);
  server.on("/led1off",  handleEquip1Off);
  server.on("/led2on",  handleEquip2On);
  server.on("/led2off",  handleEquip2Off);
  //Adicionar comandos do servidor para equip. 3 e 4

  server.on("/toggle", HTTP_GET, []() {
  if (server.arg("led") == "1") {
    toggleLED(1);
  } else if (server.arg("led") == "2") {
    toggleLED(2);
  }
  server.send(200, "text/plain", "LEDs atualizados");
});
  server.onNotFound(handle_NotFound);

  // Iniciar o servidor web
  server.begin();
}

void loop() {
  server.handleClient();
  if(equipamento1Status )
    {digitalWrite(equipamento1pin, HIGH);}
    else
    {digitalWrite(equipamento1pin, LOW);}
    
  if(equipamento2Status )
    {digitalWrite(equipamento2pin, HIGH);}
    else
    {digitalWrite(equipamento2pin, LOW);}

    //Adicionar mudança de status para equip. 3 e 4
}

void handleRoot() {
String html = "<html><head>";
html += "<style>";
html += "body {font-family: Arial, Helvetica, sans-serif; background-color: #000; color: #fff;}";
html += ".container {text-align: center; padding: 20px;}";
html += ".button {background-color: #0074cc; border: none; color: #fff; padding: 15px 30px; text-align: center; text-decoration: none; display: inline-block; font-size: 24px; margin: 10px 5px; cursor: pointer; border-radius: 5px;}";
html += ".button-on {background-color: #0074cc;}";
html += ".button-off {background-color: #0074cc;}";
html += ".column {display: inline-block; width: 45%; margin: 2.5%; text-align: center;}";
html += "</style>";
html += "</head><body>";
html += "<div class='container'>";
html += "<h1>Projeto - ESP8266</h1>";

// Botão para ligar/desligar Equipamento 1
html += "<div class='column'>";
html += "<button class='button button-on' onclick='toggleLED(1)'>";
html += "Equipamento 1 ";
html += "</button>";
html += "</div>";

// Botão para ligar/desligar Equipamento 2
html += "<div class='column'>";
html += "<button class='button button-on' onclick='toggleLED(2)'>";
html += "Equipamento 2 ";
html += "</button>";
html += "</div>";

// Botão para ligar/desligar Equipamento 3
html += "<div class='column'>";
html += "<button class='button button-on' onclick='toggleLED(3)'>"; //Ele envia o código 3 lá para o ToggleLed, botar If Lá
html += "Equipamento 3";
html += "</button>";
html += "</div>";

// Botão para ligar/desligar Equipamento 4
html += "<div class='column'>";
html += "<button class='button button-on' onclick='toggleLED(4)'>";
//Ele envia o código 3 lá para o ToggleLed, botar If Lá 
html += "Equipamento 4";
html += "</button>";
html += "</div>";

// Descrição dos botões
html += "<div style='clear: both;'></div>"; // Limpar floats para evitar problemas de layout
html += "<p>";
html += "Clique nos botões para ligar/desligar os Equipamentos.";
html += "</p>";

// Script JavaScript
html += "<script>";
html += "function toggleLED(led) {";
html += "  var xhr = new XMLHttpRequest();";
html += "  xhr.open('GET', '/toggle?led=' + led, true);";
html += "  xhr.send();";
html += "}";
html += "</script>";

html += "</div>";
html += "</body></html>";

server.send(200, "text/html", html);

}
//COMANDOS PINO 1
void handleEquip1On() {
  digitalWrite(equipamento1pin, HIGH);
  server.send(200, "text/plain", "Equipamento 1 ligado");
}

void handleEquip1Off() {

  digitalWrite(equipamento1pin, LOW);
  server.send(200, "text/plain", "Equipamento 1 desligado");
}
//COMANDOS PINO 2
void handleEquip2On() {
  digitalWrite(equipamento2pin, HIGH);
  server.send(200, "text/plain", "Equipamento 2 ligado");
}

void handleEquip2Off() {

  digitalWrite(equipamento2pin, LOW);
  server.send(200, "text/plain", "Equipamento 2 desligado");
}

//COMANDO PINO 3
//COMANDO PINO 4

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

void toggleLED(int equipamento) {
  if (equipamento == 1) {
    equipamento1Status = !equipamento1Status;
    digitalWrite(equipamento1pin, equipamento1Status );
  } 

  else if (equipamento == 2) {
    equipamento2Status = !equipamento2Status;
    digitalWrite(equipamento2pin, equipamento2Status);
  }

  //Adicionar Comando para equip. 3 e 4
}
