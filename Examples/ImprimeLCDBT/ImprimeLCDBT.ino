/*
  Programa que permite establecer una comunicacion con el modulo Bluetooth HC-05
  y mostrar el texto recibido por Bluetooth en el LCD I2C
*/

#include <SoftwareSerial.h> // libreria que permite establecer pines digitales
// para comunicacion serie
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial miBT(11, 10);  // pin 10 como RX, pin 11 como TX

String msj_recibido = "";

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  Serial.begin(9600);   // comunicacion de monitor serial a 9600 bps
  miBT.begin(9600);    // comunicacion serie entre Arduino y el modulo a 38400 bps o a 9600.
  lcd.init();
  lcd.backlight();
}

void loop() {
  if (miBT.available())   {    // si hay informacion disponible desde modulo
    msj_recibido = miBT.readString();
    Serial.println(msj_recibido);
    lcd.clear();
    Serial.println(msj_recibido.length());
    if(msj_recibido.length() < 16){
     lcd.setCursor(0, 0);
     lcd.print(msj_recibido);
     //Serial.println(msj_recibido);
    //lcd.print(msj_recibido[0, msj_recibido.length()-1]);
    }
    else{
      //lcd.setCursor(0, 0);
      //lcd.print(msj_recibido[0,15]);
      //lcd.setCursor(0,1);
      //lcd.print(msj_recibido[16, msj_recibido.length()-1]);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(msj_recibido.substring(0,16));
      lcd.setCursor(0,1);
      lcd.print(msj_recibido.substring(16, msj_recibido.length()));
    }
  }

}
