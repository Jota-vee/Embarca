#include <Keypad.h>
#include <Servo.h>

#define led5 0
#define led4 1
#define led3 11
#define led2 12
#define led1 13

String senha = "";
const String senhaCorreta = "1717";

Servo meuServo;

// Definição das linhas e colunas do teclado
const byte LINHAS = 4;
const byte COLUNAS = 4;

// Mapeamento das teclas
char teclas[LINHAS][COLUNAS] = {
  {'D', 'C', 'B', 'A'},
  {'#', '9', '6', '3'},
  {'0', '8', '5', '2'},
  {'*', '7', '4', '1'}
};

// Pinos do Arduino conectados ao teclado
byte pinosLinhas[LINHAS] = {2, 3, 4, 5};
byte pinosColunas[COLUNAS] = {6, 7, 8, 9};

// Criando o objeto do teclado
Keypad teclado = Keypad(makeKeymap(teclas), pinosLinhas, pinosColunas, LINHAS, COLUNAS);

void setup() {
  meuServo.attach(10);
  meuServo.write(120);
  
  // Configurando os pinos dos LEDs como saída
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);

  // Inicializando os LEDs desligados
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
}

void loop() {
  char tecla = teclado.getKey(); // Verifica se uma tecla foi pressionada

  if (tecla) {
    if (tecla == 'D') {  // Resetar senha
      if (senha == senhaCorreta) {
          // Acionando o servo
          meuServo.write(30);  // Mover servo para 90 graus
          delay(2000);         // Manter posição por 2 segundos
          meuServo.write(30);
        } 
        else {
          // Senha errada - piscar LED vermelho
          for (int i = 0; i < 3; i++) {
            digitalWrite(led1, HIGH);
            delay(500);
            digitalWrite(led1, LOW);
            delay(500);
          }
        }
      senha = "";
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
    } 
    else if (tecla == 'C') {
      meuServo.write(120);
      // Fechar (pode adicionar ação aqui)
    } 
    else {  
      senha += tecla;  // Adicionar tecla à senha

      // Atualizar LEDs conforme o comprimento da senha
      if (senha.length() == 1) digitalWrite(led1, HIGH);
      else if (senha.length() == 2) digitalWrite(led2, HIGH);
      else if (senha.length() == 3) digitalWrite(led3, HIGH);
      else if (senha.length() == 4) digitalWrite(led4, HIGH);
      else if (senha.length() == 5) {
        digitalWrite(led5, HIGH);

        delay(500);  // Pequena pausa para visualização

        if (senha == senhaCorreta) {
          // Acionando o servo
          meuServo.write(90);  // Mover servo para 90 graus
          delay(2000);         // Manter posição por 2 segundos
          meuServo.write(0);   // Retornar à posição inicial
        } 
        else {
          // Senha errada - piscar LED vermelho
          for (int i = 0; i < 3; i++) {
            digitalWrite(led1, HIGH);
            delay(500);
            digitalWrite(led1, LOW);
            delay(500);
          }
        }
        
        // Resetar senha e apagar LEDs
        senha = "";
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(led4, LOW);
        digitalWrite(led5, LOW);
      }
    }
  }
}
