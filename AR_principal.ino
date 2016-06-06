/*
   Santiago Paiz 15849
   Santiago Solorzano 14619
   Diego Sosa
   Proyecto Circuitos
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
bool bottonPrimeraVezPresionado2 = true;
int randomNumberForPins;
int lastRandomNumberForPins;
bool bottonSegundaVezPresionado = false;

bool ServoOn = false;
bool LEDsOn = false;

int numeroEstatico;
bool todosEnsendidos;
bool funcion2On = false;
byte givenArray[2];


bool led1Full = false;
bool led2Full = false;
bool led3Full = false;
bool led4Full = false;
bool subida = true;
bool bajada = false;

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
        Funcion1(1);
        break;
      case 'z':
        Funcion1(2);
        break;
      case 's':
        ServoOn = true;
        break;
      case 'x':
        LEDsOn = true;
        Funcion3(LEDsOn);
        break;
      case 'd':
        Funcion4(1);
        break;
      case 'c':
        Funcion4(2);
        break;
      case 'f':
        ServoOn = false;
        break;
      case 'v':
        LEDsOn = false;
        break;
    }
  }
  //RandPin(bottonPrimeraVezPresionado);
  Funcion2(ServoOn);
  Funcion3(LEDsOn);
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
void Funcion2(bool ServoOn) {
  if(ServoOn)
  {
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
    if(mssg == '0')
    {
      delay(servoVelocidad*50);
    }
    else if (mssg == '1')
    {
      delay(servoVelocidad*40);
    }
    else if (mssg == '2')
    {
      delay(servoVelocidad*30);
    }
    else if (mssg == '3')
    {
      delay(servoVelocidad*20);
    }
    else if (mssg == '4')
    {
      delay(servoVelocidad*10);
    }
    else if (mssg == '5')
    {
      delay(servoVelocidad);
    }
    servoUsado.write(posicionDelServo);
  }
}
/*
    Función 03:
    El potenciómetro enciende los LEDs en orden (de un lado a otro), pero los va encendiendo
    gradualmente.
*/
void Funcion3(bool LEDsOn) {
  if(LEDsOn)
  {
    if(subida == true)
    {
      if(led1Full == false and led2Full == false and led3Full == false and led4Full == false)
      {
        if(mssg == '0')
        {
          analogWrite(11, 0);
          analogWrite(6, 0);
          analogWrite(5, 0);
          analogWrite(3, 0);
        }
        else if(mssg == '1')
        {
          analogWrite(11, 50);
          analogWrite(6, 0);
          analogWrite(5, 0);
          analogWrite(3, 0);
        }
        else if(mssg == '2')
        {
          analogWrite(11, 100);
          analogWrite(6, 0);
          analogWrite(5, 0);
          analogWrite(3, 0);
        }
        else if(mssg == '3')
        {
          analogWrite(11, 155);
          analogWrite(6, 0);
          analogWrite(5, 0);
          analogWrite(3, 0);
        }
        else if(mssg == '4')
        {
          digitalWrite(11, 200);
          digitalWrite(6, 0);
          digitalWrite(5, 0);
          digitalWrite(3, 0);
        }
        else if(mssg == '6')
        {
          digitalWrite(11, 255);
          digitalWrite(6, 0);
          digitalWrite(5, 0);
          digitalWrite(3, 0);
          led1Full = true;
          mssg = ' ';
        }
      }
      
      else if(led1Full == true and led2Full == false and led3Full == false and led4Full == false)
      {
        if(mssg == '0')
        {
          analogWrite(11, 255);
          analogWrite(6, 0);
          analogWrite(5, 0);
          analogWrite(3, 0);
        }
        else if(mssg == '1')
        {
          analogWrite(11, 255);
          analogWrite(6, 50);
          analogWrite(5, 0);
          analogWrite(3, 0);
        }
        else if(mssg == '2')
        {
          analogWrite(11, 255);
          analogWrite(6, 100);
          analogWrite(5, 0);
          analogWrite(3, 0);
        }
        else if(mssg == '3')
        {
          analogWrite(11, 255);
          analogWrite(6, 155);
          analogWrite(5, 0);
          analogWrite(3, 0);
        }
        else if(mssg == '4')
        {
          digitalWrite(11, 255);
          digitalWrite(6, 200);
          digitalWrite(5, 0);
          digitalWrite(3, 0);
        }
        else if(mssg == '6')
        {
          digitalWrite(11, 255);
          digitalWrite(6, 255);
          digitalWrite(5, 0);
          digitalWrite(3, 0);
          led2Full = true;
          mssg = ' ';
        }
      }
  
      else if(led1Full == true and led2Full == true and led3Full == false and led4Full == false)
      {
        if(mssg == '0')
        {
          analogWrite(11, 255);
          analogWrite(6, 255);
          analogWrite(5, 0);
          analogWrite(3, 0);
        }
        else if(mssg == '1')
        {
          analogWrite(11, 255);
          analogWrite(6, 255);
          analogWrite(5, 50);
          analogWrite(3, 0);
        }
        else if(mssg == '2')
        {
          analogWrite(11, 255);
          analogWrite(6, 255);
          analogWrite(5, 100);
          analogWrite(3, 0);
        }
        else if(mssg == '3')
        {
          analogWrite(11, 255);
          analogWrite(6, 255);
          analogWrite(5, 155);
          analogWrite(3, 0);
        }
        else if(mssg == '4')
        {
          digitalWrite(11, 255);
          digitalWrite(6, 255);
          digitalWrite(5, 200);
          digitalWrite(3, 0);
        }
        else if(mssg == '6')
        {
          digitalWrite(11, 255);
          digitalWrite(6, 255);
          digitalWrite(5, 255);
          digitalWrite(3, 0);
          led3Full = true;
          mssg = ' ';
        }
      }
  
      else if(led1Full == true and led2Full == true and led3Full == true and led4Full == false)
      {
        if(mssg == '0')
        {
          analogWrite(11, 255);
          analogWrite(6, 255);
          analogWrite(5, 255);
          analogWrite(3, 0);
        }
        else if(mssg == '1')
        {
          analogWrite(11, 255);
          analogWrite(6, 255);
          analogWrite(5, 255);
          analogWrite(3, 50);
        }
        else if(mssg == '2')
        {
          analogWrite(11, 255);
          analogWrite(6, 255);
          analogWrite(5, 255);
          analogWrite(3, 100);
        }
        else if(mssg == '3')
        {
          analogWrite(11, 255);
          analogWrite(6, 255);
          analogWrite(5, 255);
          analogWrite(3, 155);
        }
        else if(mssg == '4')
        {
          digitalWrite(11, 255);
          digitalWrite(6, 255);
          digitalWrite(5, 255);
          digitalWrite(3, 200);
        }
        else if(mssg == '6')
        {
          digitalWrite(11, 255);
          digitalWrite(6, 255);
          digitalWrite(5, 255);
          digitalWrite(3, 255);
          led4Full = true;
          mssg = ' ';
          subida = false;
        }
      }
    }
    else if(subida == false)
    {
      if(led1Full == true and led2Full == true and led3Full == true and led4Full == true)
      {
        if(mssg == '6')
        {
          analogWrite(11, 255);
          analogWrite(6, 255);
          analogWrite(5, 255);
          analogWrite(3, 255);
        }
        else if(mssg == '4')
        {
          analogWrite(11, 255);
          analogWrite(6, 255);
          analogWrite(5, 255);
          analogWrite(3, 200);
        }
        else if(mssg == '3')
        {
          analogWrite(11, 255);
          analogWrite(6, 255);
          analogWrite(5, 255);
          analogWrite(3, 155);
        }
        else if(mssg == '2')
        {
          analogWrite(11, 255);
          analogWrite(6, 255);
          analogWrite(5, 255);
          analogWrite(3, 100);
        }
        else if(mssg == '1')
        {
          digitalWrite(11, 255);
          digitalWrite(6, 255);
          digitalWrite(5, 255);
          digitalWrite(3, 50);
        }
        else if(mssg == '0')
        {
          digitalWrite(11, 255);
          digitalWrite(6, 255);
          digitalWrite(5, 255);
          digitalWrite(3, 0);
          led4Full = false;
          mssg = ' ';
        }
      }

      else if(led1Full == true and led2Full == true and led3Full == true and led4Full == false)
      {
        if(mssg == '6')
        {
          analogWrite(11, 255);
          analogWrite(6, 255);
          analogWrite(5, 255);
          analogWrite(3, 0);
        }
        else if(mssg == '4')
        {
          analogWrite(11, 255);
          analogWrite(6, 255);
          analogWrite(5, 200);
          analogWrite(3, 0);
        }
        else if(mssg == '3')
        {
          analogWrite(11, 255);
          analogWrite(6, 255);
          analogWrite(5, 155);
          analogWrite(3, 0);
        }
        else if(mssg == '2')
        {
          analogWrite(11, 255);
          analogWrite(6, 255);
          analogWrite(5, 100);
          analogWrite(3, 0);
        }
        else if(mssg == '1')
        {
          digitalWrite(11, 255);
          digitalWrite(6, 255);
          digitalWrite(5, 50);
          digitalWrite(3, 0);
        }
        else if(mssg == '0')
        {
          digitalWrite(11, 255);
          digitalWrite(6, 255);
          digitalWrite(5, 0);
          digitalWrite(3, 0);
          led3Full = false;
          mssg = ' ';
        }
      }

      else if(led1Full == true and led2Full == true and led3Full == false and led4Full == false)
      {
        if(mssg == '6')
        {
          analogWrite(11, 255);
          analogWrite(6, 255);
          analogWrite(5, 0);
          analogWrite(3, 0);
        }
        else if(mssg == '4')
        {
          analogWrite(11, 255);
          analogWrite(6, 200);
          analogWrite(5, 0);
          analogWrite(3, 0);
        }
        else if(mssg == '3')
        {
          analogWrite(11, 255);
          analogWrite(6, 155);
          analogWrite(5, 0);
          analogWrite(3, 0);
        }
        else if(mssg == '2')
        {
          analogWrite(11, 255);
          analogWrite(6, 100);
          analogWrite(5, 0);
          analogWrite(3, 0);
        }
        else if(mssg == '1')
        {
          digitalWrite(11, 255);
          digitalWrite(6, 55);
          digitalWrite(5, 0);
          digitalWrite(3, 0);
        }
        else if(mssg == '0')
        {
          digitalWrite(11, 255);
          digitalWrite(6, 0);
          digitalWrite(5, 0);
          digitalWrite(3, 0);
          led2Full = false;
          mssg = ' ';
        }
      }

      else if(led1Full == true and led2Full == false and led3Full == false and led4Full == false)
      {
        if(mssg == '6')
        {
          analogWrite(11, 255);
          analogWrite(6, 255);
          analogWrite(5, 0);
          analogWrite(3, 0);
        }
        else if(mssg == '4')
        {
          analogWrite(11, 200);
          analogWrite(6, 0);
          analogWrite(5, 0);
          analogWrite(3, 0);
        }
        else if(mssg == '3')
        {
          analogWrite(11, 155);
          analogWrite(6, 0);
          analogWrite(5, 0);
          analogWrite(3, 0);
        }
        else if(mssg == '2')
        {
          analogWrite(11, 100);
          analogWrite(6, 0);
          analogWrite(5, 0);
          analogWrite(3, 0);
        }
        else if(mssg == '1')
        {
          digitalWrite(11, 55);
          digitalWrite(6, 0);
          digitalWrite(5, 0);
          digitalWrite(3, 0);
        }
        else if(mssg == '0')
        {
          digitalWrite(11, 0);
          digitalWrite(6, 0);
          digitalWrite(5, 0);
          digitalWrite(3, 0);
          led1Full = false;
          mssg = ' ';
          subida = true;
        }
      }

      
    }

    
  }
}
/*
    Función 04:
    Presionar PushButton 01 hace que los LEDs se enciendan de forma aleatoria (sólo 1 LED
    encendido a la vez). Presionar PushButton01 de nuevo hace que los LEDs se queden estáticos
    (el último encendido se queda encendido y los otros 3 apagados). Presionar PushButton 02
    enciende todos los LEDs. Al soltar PushButton 02 se queda encendido sólo el que originalmente
    estaba encendido.
*/
void Funcion4(int bottonPresionado) 
{
  if (bottonPresionado == 1) 
  {
    if(bottonPrimeraVezPresionado == true)
    {
        randomNumberForPins = random(0,4);
        if(randomNumberForPins == 0)
        {
          digitalWrite(11, 0);
          digitalWrite(6, 0);
          digitalWrite(5, 0);
          digitalWrite(3, 1);
        }
        else if(randomNumberForPins == 1)
        {
          digitalWrite(11, 0);
          digitalWrite(6, 1);
          digitalWrite(5, 0);
          digitalWrite(3, 0);
        }
        else if(randomNumberForPins == 2)
        {
          digitalWrite(11, 0);
          digitalWrite(6, 0);
          digitalWrite(5, 1);
          digitalWrite(3, 0);
        }
        else if(randomNumberForPins == 3)
        {
          digitalWrite(11, 1);
          digitalWrite(6, 0);
          digitalWrite(5, 0);
          digitalWrite(3, 0);
        }
     
        bottonPrimeraVezPresionado = false;
    } 
    else 
    {
      digitalWrite(11, LOW);
      digitalWrite(6, LOW);
      digitalWrite(5, LOW);
      digitalWrite(3, HIGH);
      bottonPrimeraVezPresionado = true;
    }
  }
  if (bottonPresionado == 2)
  {
    if(bottonPrimeraVezPresionado2 == true)
    {
      Transformador(15); //Enciende todos los numeros
      bottonPrimeraVezPresionado2 = false;
    } 
    else if(bottonPrimeraVezPresionado2 == false)
    {
      if(randomNumberForPins == 0)
        {
          digitalWrite(11, 0);
          digitalWrite(6, 0);
          digitalWrite(5, 0);
          digitalWrite(3, 1);
        }
        else if(randomNumberForPins == 1)
        {
          digitalWrite(11, 0);
          digitalWrite(6, 1);
          digitalWrite(5, 0);
          digitalWrite(3, 0);
        }
        else if(randomNumberForPins == 2)
        {
          digitalWrite(11, 0);
          digitalWrite(6, 0);
          digitalWrite(5, 1);
          digitalWrite(3, 0);
        }
        else if(randomNumberForPins == 3)
        {
          digitalWrite(11, 1);
          digitalWrite(6, 0);
          digitalWrite(5, 0);
          digitalWrite(3, 0);
        }
        bottonPrimeraVezPresionado2 = true;
    }
  }
}

//Transformador: transforma a binario un numero y los guarda en a,b,c,d
void Transformador(int numeroParaTransformar)
{
  a = numeroParaTransformar % 2;
  b = numeroParaTransformar / 2 % 2;
  c = numeroParaTransformar / 4 % 2;
  d = numeroParaTransformar / 8 % 2;

  digitalWrite(11, d);
  digitalWrite(6, c);
  digitalWrite(5, b);
  digitalWrite(3, a);
}
