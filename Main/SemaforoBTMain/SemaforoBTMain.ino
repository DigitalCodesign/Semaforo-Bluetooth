/* Semáforo de Violencia de Género controlado mediante Bluetooth y con luces controladas mediante
   módulo de relés. Implementa memorización del estado en la EEPROM
   Se recibe un carácter desde Bluetooth por puerto serie. Según su valor se activa un color:
      - '1' -> Rojo
      - '2' -> Amarillo
      - '3' -> Verde
      - '0' -> Apagar todo
   Autores: José Luis González de Chávez y Augusto Samuel Hernández Martín
   Github: DigitalCodesign (https://github.com/DigitalCodesign) y AugustoS97 (https://github.com/AugustoS97)
*/

/*  CONEXIÓN DE LA ELECTRÓNICA
    Módulo de Relé:
      Canal 1 (Rojo) -> D2
      Canal 2 (Verde) -> D3
      Canal 3 (Ámbar) -> D4
      Vcc -> 5V
      GND -> GND
    Módulo Bluetooth:
      Rx BT -> D11
      Tx BT -> D10
      Vcc -> 5V
      GND -> GND
*/

#include <SoftwareSerial.h> // libreria que permite establecer pines digitales
#include <EEPROM.h> //Libreria para almacenar en memoria en Arduino

#define releR  2
#define releV 3
#define releN 4

#define SERIAL_PRINT //Para utilizar los mensajes seriales

SoftwareSerial miBT(10, 11);  // pin 10 como RX, pin 11 como TX

String msj_recibido = "";

void setup() {
#ifdef SERIAL_PRINT
  Serial.begin(9600);   // comunicacion de monitor serial a 9600 bps
#endif
  miBT.begin(9600);    // comunicacion serie entre Arduino y el modulo a 38400 bps o a 9600.
  pinMode(releR, OUTPUT);
  pinMode(releV, OUTPUT);
  pinMode(releN, OUTPUT);
  digitalWrite(releR, HIGH); //Trabajan con logica negada. HIGH para apagar rele y LOW encender
  digitalWrite(releV, HIGH);
  digitalWrite(releN, HIGH);

  //Se lee de la EEPROM el ultimo estado y se coloca en ese estado
  char ultimo_estado = char(EEPROM.read(0x00));
  //Se actua en los reles de acuerdo al valor almacenado

  enciendeSemaforo(ultimo_estado); //Se enciende el semaforo con el valor del ultimo estado
} //Fin del Setup

void loop() { //Inicio Loop
  if (miBT.available())   {    // si hay informacion disponible desde modulo
    msj_recibido = miBT.readString();

    //Se guarda en la EEPROM el nueo valor recibido
    if ((char(EEPROM.read(0x00)) != msj_recibido[0]) && (msj_recibido[0] == '1' || msj_recibido[0] == '2' || msj_recibido[0] == '3' || msj_recibido[0] == '0')) {
      EEPROM.write(0x00, char(msj_recibido[0]));
#ifdef SERIAL_PRINT
      Serial.print("Almacenando el valor recibido en la EEPROM:");
      Serial.println(char(msj_recibido[0]));
#endif
    }
#ifdef SERIAL_PRINT
    Serial.print(msj_recibido[0]);
#endif
    enciendeSemaforo (char(msj_recibido[0])); //Se activa el color del semaforo segun el mensaje recibido
  }

} //Fin del Loop

//Funcion para encender semaforo
void enciendeSemaforo (char mensaje) {
  if (mensaje == '1') { //Rojo
#ifdef SERIAL_PRINT
    Serial.print("Encendiendo luz Roja");
#endif
    digitalWrite(releR, LOW);
    digitalWrite(releV, HIGH);
    digitalWrite(releN, HIGH);
  }
  else if (mensaje == '2') { //Amarillo
#ifdef SERIAL_PRINT
    Serial.print("Encendiendo luz Amarilla");
#endif
    digitalWrite(releR, HIGH);
    digitalWrite(releV, HIGH);
    digitalWrite(releN, LOW);
  }
  else if (mensaje == '3') { //Verde
#ifdef SERIAL_PRINT
    Serial.print("Encendiendo luz Verde");
#endif
    digitalWrite(releR, HIGH);
    digitalWrite(releV, LOW);
    digitalWrite(releN, HIGH);
  }
  else if (mensaje == '0') { //Semaforo apagado
#ifdef SERIAL_PRINT
    Serial.print("Apagando todas las luces");
#endif
    digitalWrite(releR, HIGH);
    digitalWrite(releV, HIGH);
    digitalWrite(releN, HIGH);
  }
}
