/**********************************************************************************************************************************
  Elismar Silva(https://github.com/ElismarSilva)
  Ciência da Computação - UDF
  02 de agosto de 2023

  Projeto de uma lixeira que sorteira um dos nomes entre
  todos os nomes da lista, quando estiver cheia.



*********************************************************************************************************************************/

#include <Servo.h>
#define SENSOR_LIMIT 2 //sensor que controla se a lixeira esta cheia ou vazia
#define SENSOR_PROXIMIT 4 //Sensor de proximidade para acionar a abertura da tampa
#define PIN_MOTOR 3   //Servo da tampa da lixeira
#define BTN 5 //botao que deliga o buzzer

//Lista de nomes que ira sortear ([5] matriz com 5 strings)([10] cada string
//com ate 10 caracters.
char retirar_lixo[5][10] = {"", "", "", "", ""}; // Coloque aqui quem ira sortear, mas lembre de ajustar o numero de elementos.

//cria um objeto
Servo motor_lixeira;

//armazena os valores dos sensores
int estado_Sensor_limit;
int estado_Sensor_Proximit;
int estado_Btn_OFF;

//variavel de controle
int aux = 0;
int aux1 = 0;

void executar();
void setup()
{
  motor_lixeira.attach(PIN_MOTOR);
  pinMode(SENSOR_PROXIMIT, INPUT_PULLUP);
  pinMode(SENSOR_LIMIT, INPUT_PULLUP); // Configura o pino do botão como entrada com pull-up
  pinMode(BTN, INPUT_PULLUP);
  Serial.begin(9600); // Inicializa a comunicação serial
  motor_lixeira.write(0);
  delay(100);

}


void loop()
{
  estado_Btn_OFF = digitalRead(BTN);
  estado_Sensor_Proximit = digitalRead(SENSOR_PROXIMIT);
  estado_Sensor_limit = digitalRead(SENSOR_LIMIT); // Lê o estado do botão

  int index = random(5); // Gera um índice aleatório entre 0 e 4

  if ( !estado_Sensor_Proximit) {
    abrir();
  } else {
    fechar();
  }

  if (!estado_Sensor_limit && aux == 0)
  {
    char *nomes = retirar_lixo[index]; // Obtém o item da lista usando o índice 0 ate 4
    Serial.println("Quem ira retirar o lixo eh: " + String(nomes)); // Imprime o nome selecionado

    delay(1000); // Aguarda 1 segundo
    aux = 1;
  }
  else if (!estado_Sensor_limit) {
    tone(8, 400, 500);
    delay(1000);


  } else {
    aux = 0;
  }

  if (!estado_Btn_OFF) {
    noTone(8);
    delay(15000);
    aux = 1;
  }
}

void abrir() {
  motor_lixeira.write(180);
  delay(5000);
}

void fechar() {
  motor_lixeira.write(0);
  delay(1000);
}
