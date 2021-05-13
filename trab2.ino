//Declaracao e inclusao da biblioteca blynk
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


int sensorPin = A0;// Declaracao do pino de leitura
int sensorValor = 0;// Declaracao da variavel que sera atribuido o valor do sensor
int umidadeValor = 0;//Variavel que vai mostrar a porcentagem da umidade

//Declaracao da chave de autenticacao do blynk e credenciais do roteador wifi
char auth[] = "";
char ssid[] = "";
char pass[] = "";

void setup()
{
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);//Funcao responsavel por fazer a comunicacao da chave com  o roteador
}

void loop()
{
  sensorValor = analogRead(sensorPin);//Leitura e atribuicao do valor do sensor (vai de 0 a 1024)
  umidadeValor = map(sensorValor,0,1023,0,100);//Remapeando o valor para um alcance de 0 a 100
  delay(1000);

  if(umidadeValor>74)//Se o valor do sensor de umidade for maior que 74 a planta deve ser regada
  {
       //print no monitor
       Serial.println("Solo seco! Regue a sua planta!");
       Serial.println(umidadeValor);
       Blynk.notify("Solo seco! Regue a sua planta!");//Funcao que gera a notificacao no app
       delay(1000); 
  }
  else if(umidadeValor<45)//Se o valor do sensor for menor que 45 a umidade esta ideal
  {
       //print no monitor
       Serial.println("Solo molhado o suficiente! Nenhuma acao necessaria");
       Serial.println(umidadeValor);
       Blynk.notify("Solo molhado o suficiente! Nenhuma acao necessaria");//Funcao que gera a notificacao no app
       delay(1000);
  }
  
  Blynk.virtualWrite(V1,umidadeValor);//Funcao que passa o valor lido para o Gauge do app
  Blynk.run();//Funcao que roda o blynk
} 
