/* Semáforo de Violencia de Género controlado mediante Bluetooth y con luces controladas mediante
 * módulo de relés.
 * Se recibe un carácter desde Bluetooth por puerto serie. Según su valor se activa un color:
 *    - '1' -> Rojo
 *    - '2' -> Amarillo
 *    - '3' -> Verde
 *    - '0' -> Apagar todo
 * Autores: José Luis González de Chávez y Augusto Samuel Hernández Martín
 * Github: DigitalCodesign (https://github.com/DigitalCodesign) y AugustoS97 (https://github.com/AugustoS97)
*/

/*  CONEXIÓN DE LA ELECTRÓNICA
 *  Módulo de Relé:
 *    Canal 1 (Rojo) -> D2
 *    Canal 2 (Verde) -> D3
 *    Canal 3 (Ámbar) -> D4
 *    Vcc -> 5V
 *    GND -> GND
 *  Módulo Bluetooth:
 *    Rx BT -> D11
 *    Tx BT -> D10
 *    Vcc -> 5V
 *    GND -> GND
 */
#include <SoftwareSerial.h> // libreria que permite establecer pines digitales

// para comunicacion serie
//#include <Wire.h>
//#include <LiquidCrystal_I2C.h>

#define releR  2
#define releV 3
#define releN 4

SoftwareSerial miBT(10, 11);  // pin 10 como RX, pin 11 como TX

String msj_recibido = "";


void setup() {
  Serial.begin(9600);   // comunicacion de monitor serial a 9600 bps
  miBT.begin(9600);    // comunicacion serie entre Arduino y el modulo a 38400 bps o a 9600.
  pinMode(releR, OUTPUT);
  pinMode(releV, OUTPUT);
  pinMode(releN, OUTPUT);
  digitalWrite(releR, HIGH); //Trabajan con logica negada. HIGH para apagar rele y LOW encender
  digitalWrite(releV, HIGH);
  digitalWrite(releN, HIGH);
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
  }

} //Fin del Loop
