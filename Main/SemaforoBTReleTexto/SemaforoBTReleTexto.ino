/* Semáforo de Violencia de Género controlado mediante Bluetooth y con luces controladas mediante
   módulo de relés.
   Se recibe un carácter desde Bluetooth por puerto serie con el color a encender. Según su valor se activa un color:
      - '1' -> Rojo
      - '2' -> Amarillo
      - '3' -> Verde
      - '0' -> Apagar todo
      Se recibe un mensaje bluetooth por puerto serie con el texto a mostrar en el LCD.
*/

/*  CONEXIÓN DE LA ELECTRÓNICA
    Módulo de Relé:
      Rele maestro (General) -> D2
      Canal 1 (Rojo) -> D3
      Canal 2 (Verde) -> D4
      Canal 3 (Ámbar) -> D5
      Vcc -> 5V
      GND -> GND
    Módulo Bluetooth:
      Rx BT -> D11
      Tx BT -> D10
      Vcc -> 5V
      GND -> GND

   Pantalla I2C: 
      Vcc -> Vcc
      GND -> GND
      SCL -> A5
      SDA -> A4
*/
#include <SoftwareSerial.h> // libreria que permite establecer pines digitales

// para comunicacion serie
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define releR  3
#define releV 4
#define releN 5
#define releMaster 2

SoftwareSerial miBT(10, 11);  // pin 10 como RX, pin 11 como TX

LiquidCrystal_I2C lcd (0x27, 20, 4); //Se crea el LCD de 20x4

String msj_recibido = "";


void setup() {
  Serial.begin(9600);   // comunicacion de monitor serial a 9600 bps
  miBT.begin(9600);    // comunicacion serie entre Arduino y el modulo a 38400 bps o a 9600.
  pinMode(releR, OUTPUT);
  pinMode(releV, OUTPUT);
  pinMode(releN, OUTPUT);
  pinMode(releMaster, OUTPUT);
  digitalWrite(releR, HIGH); //Trabajan con logica negada. HIGH para apagar rele y LOW encender
  digitalWrite(releV, HIGH);
  digitalWrite(releN, HIGH);
  digitalWrite(releMaster, LOW);
  lcd.init(); //Se configura e inicia el LCD
  lcd.clear();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Parate y di"); //Mensaje en el inicio
  lcd.setCursor(0,1);
  lcd.print("NO a la violencia");
  lcd.setCursor(0,2);
  lcd.print("de genero");
} //Fin del Setup

void loop() { //Inicio Loop
  if (miBT.available())   {    // si hay informacion disponible desde modulo
    msj_recibido = miBT.readString();
    Serial.print(msj_recibido[0]);
    if (msj_recibido[0] == '1') { //Rojo
      digitalWrite(releR, LOW);
      digitalWrite(releV, HIGH);
      digitalWrite(releN, HIGH);
    }
    else if (msj_recibido[0] == '2') { //Amarillo
      digitalWrite(releR, HIGH);
      digitalWrite(releV, HIGH);
      digitalWrite(releN, LOW);
    }
    else if (msj_recibido[0] == '3') { //Verde
      digitalWrite(releR, HIGH);
      digitalWrite(releV, LOW);
      digitalWrite(releN, HIGH);
    }
    else if (msj_recibido[0] == '0') { //Semaforo apagado
      digitalWrite(releR, HIGH);
      digitalWrite(releV, HIGH);
      digitalWrite(releN, HIGH);
    }
    else { //Lo que se recibe es el texto a representar en pantalla
      int longitud = sizeof(msj_recibido); //Calculo la longitud del string
      lcd.clear(); //Se limpia la pantalla
      if (longitud < 20) { //Menos de 20 caracteres. Se puede representar en la primera línea solo
        lcd.setCursor(0, 0);
        lcd.print(msj_recibido.substring(0, longitud - 1));
      }
      else if (longitud >= 20 && longitud < 40) { //Hasta 40 caracteres. Usar 2 lineas
        lcd.setCursor(0, 0);
        lcd.print(msj_recibido.substring(0, 19));
        lcd.setCursor(0, 1);
        lcd.print(msj_recibido.substring(20, longitud - 1));
      }
      else if (longitud >= 40 && longitud < 60) { //Hasta 60 caracteres. Usar 3 lineas
        lcd.setCursor(0, 0);
        lcd.print(msj_recibido.substring(0, 19));
        lcd.setCursor(0, 1);
        lcd.print(msj_recibido.substring(20, 39));
        lcd.setCursor(0, 2);
        lcd.print(msj_recibido.substring(40, longitud - 1));
      }
      else { //Mas de 60 caracteres. 4 lineas
        lcd.setCursor(0, 0);
        lcd.print(msj_recibido.substring(0, 19));
        lcd.setCursor(0, 1);
        lcd.print(msj_recibido.substring(20, 39));
        lcd.setCursor(0, 2);
        lcd.print(msj_recibido.substring(40, 59));
        lcd.setCursor(0, 3);
        lcd.print(msj_recibido.substring(60, min(longitud - 1, 79)));
      }
    }
  }

} //Fin del Loop
