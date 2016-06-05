/*
   Santiago Paiz 15849
   Santiago No.2
   Diego Sosa
   Proyecto Circuitos
   Ultima Modificacion: 5/26/2016 - Santiago #1, terminado en teoria
*/
#include <Servo.h>

int mssg; //variable para guardar el mensaje
bool local;
//contadorBinario
int a;
int b;
int c;
int d;
int contadorBinario = 0;
//Servo
Servo servoUsado;
int servoPin;
int servoVelocidad;
int posicionDelServo = 1;
bool servoDireccion = true;

//potenciometro
int potenciometroMap;
int contadorGradualmente = 1;

//funcion4
bool bottonPrimeraVezPresionado = false;
int randomNumberForPins;
bool bottonSegundaVezPresionado = false;
int numeroEstatico;
bool todosEnsendidos;
bool funcion2On = false;
byte givenArray[2];
void setup()
{
  pinMode(13, OUTPUT); //establecemos 13 como salida
  Serial.begin(9600); //iniciando Serial

  //contadorBinario
  //inputs
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  //outputs
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(11, OUTPUT);
  // FIN DE CONTADOR BINARIO
  //Servo
  servoUsado.attach(12);
  pinMode(A2, INPUT_PULLUP);
}

void loop()
{
  if (Serial.available() > 0)
  {
    mssg = Serial.read();

    //switch para ver cual funcion se usa
    switch (mssg) {
      case 'a':
        ServoOn = false;
        Funcion1(1);
        break;
      case 'z':
        ServoOn = false;
        Funcion1(2);
        break;
      case 's':
        ServoOn = true;
        break;
      case 'x':
        ServoOn = false;
        Funcion3();
        break;
      case 'd':
        ServoOn = false;
        Funcion4(1);
        break;
      case 'c':
        ServoOn = false;
        Funcion4(2);
        break;
    }
    if (!todosEnsendidos) {
      //funcion 4 tiene que continuar fuera de su funcion
      if (bottonPrimeraVezPresionado && !bottonSegundaVezPresionado) {
        randomNumberForPins = pow(2, random(0, 3));
        Transformador(randomNumberForPins);
        delay(50);
      }
      if (bottonSegundaVezPresionado && !todosEnsendidos) {
        Transformador(numeroEstatico);
      }
    }
  }
  digitalWrite(11, d);
  digitalWrite(6, c);
  digitalWrite(5, b);
  digitalWrite(3, a);
  todosEnsendidos = false;
  Funcion2(ServoOn);
}
/*
     Función 01:
     La primera función es un contador binario controlado por los dos pushbuttons. Un botón
     aumenta el contador y el otro lo disminuye. Debe topar en 0000 y en 1111.
*/
void Funcion1(int button) {
  //Funcion1: Contador Binario
  bottonPrimeraVezPresionado = false;
  if (button == 1) contadorBinario++;
  if (button == 2) contadorBinario--;
  //topadores (maximo y minimo)
  if (contadorBinario >= 15) contadorBinario = 15;
  if (contadorBinario <= 0) contadorBinario = 0;
  //Transformador
  Transformador(contadorBinario);
}
/*
     Función 02:
     El Servo se mueve solo de un lado a otro. El potenciómetro controla la velocidad de
     movimiento. Los LEDs deben encenderse dependiendo de la posición del servo
*/
void Funcion2(ServoOn) {
  if(ServoOn){
    servoVelocidad = int(mssg);
    if (servoDireccion)
    {
      posicionDelServo += 20;
      if (posicionDelServo >= 180) {
        servoDireccion = false;
      }
    }
    else
    {
      posicionDelServo -= 20;
      if (posicionDelServo <= 0 ) {
        servoDireccion = true;
      }

    }
    delay(servoVelocidad*5);
    servoUsado.write(posicionDelServo);
  }
}
/*
    Función 03:
    El potenciómetro enciende los LEDs en orden (de un lado a otro), pero los va encendiendo
    gradualmente.
*/
void Funcion3() {
  bottonPrimeraVezPresionado = false;
  potenciometroMap = int(mssg);
  potenciometroMap = map (potenciometroMap, 0, 1023, 1, 4);
  contadorGradualmente = pow(2, potenciometroMap) - 1;
  Transformador(contadorGradualmente);
}
/*
    Función 04:
    Presionar PushButton 01 hace que los LEDs se enciendan de forma aleatoria (sólo 1 LED
    encendido a la vez). Presionar PushButton01 de nuevo hace que los LEDs se queden estáticos
    (el último encendido se queda encendido y los otros 3 apagados). Presionar PushButton 02
    enciende todos los LEDs. Al soltar PushButton 02 se queda encendido sólo el que originalmente
    estaba encendido.
*/
void Funcion4(int bottonPresionado) {
  if (bottonPrimeraVezPresionado) {
    bottonSegundaVezPresionado = true;
    numeroEstatico = randomNumberForPins;
  }
  if (bottonPresionado == 1) {
    bottonPrimeraVezPresionado = true;
  }
  if (bottonPresionado == 2)
  {
    Transformador(15); //Enciende todos los numeros
    todosEnsendidos = true;
  }
}
//Transformador: transforma a binario un numero y los guarda en a,b,c,d
void Transformador(int numeroParaTransformar)
{
  a = numeroParaTransformar % 2;
  b = numeroParaTransformar / 2 % 2;
  c = numeroParaTransformar / 4 % 2;
  d = numeroParaTransformar / 8 % 2;
}
