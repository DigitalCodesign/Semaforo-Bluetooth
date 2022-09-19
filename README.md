# Semáforo Bluetooth con Pantalla LCD

Proyecto desarrollado para implementar un semaforo controlado por Bluetooth mediante una App movil. El Arduino se encarga de controlar el encendido de 3 relés que activan cada bombilla del semáforo. Asimismo, dispone de un LCD 20x4 para mostrar mensajes enviados por la App Móvil.

## Autores
- José Luis González de Chávez 
- Augusto Samuel Hernández Martín
- Miqueas Z. Fortes

## Materiales
- [Arduino Nano](https://www.digitalcodesign.com/shop/00017176-placa-compatible-con-arduino-nano-v3-0-4062?search=nano#attr=)
- [Protoboard MB-102](https://www.digitalcodesign.com/shop/00010979-protoboard-mb-102-830-puntos-3442?search=protoboard#attr=)
- [Alimentador MB-102](https://www.digitalcodesign.com/shop/00016933-modulo-alimentacion-mb-102-protoboard-3-3-5v-4038?search=mb-102#attr=)
- [Fuente Alimentacion 12V 2A](https://www.digitalcodesign.com/shop/00019231-fuente-de-alimentacion-12v-2a-con-conector-dc-jack-5063)
- [Módulo de 4 relés](https://www.digitalcodesign.com/shop/00010252-modulo-rele-5v-10a-de-4-canales-3370?search=rel%C3%A9#attr=)
- [Módulo Bluetooth HC-06](https://www.digitalcodesign.com/shop/00016469-modulo-bluetooth-hc-06-3991?search=HC-06#attr=)
- [Display LCD 16x02](https://www.digitalcodesign.com/shop/00016025-pantalla-lcd-16x2-modulo-i2c-3947?search=16x2#attr=)

## Conexiones

 - LCD 16x02 I2C:
 	- Vcc -> 5V
 	- GND -> GND
 	- SDA -> SDA (D4)
 	- SCL -> SCL (D3)
- Módulo de Relé:
	- Canal 1 (Rojo) -> D2
	- Canal 2 (Verde) -> D3
	- Canal 3 (Ámbar) -> D4
	- Vcc -> 5V
	- GND -> GND
- Módulo Bluetooth:
	- Rx BT -> D11
	- Tx BT -> D10
	- Vcc -> 5V
	- GND -> GND

## Librerias

Debe instalarse lo siguiente:

- Librería LiquidCrystal I2C disponible en el Gestor de Librerias

## Tools

- Se dispone de un escaner I2C para determinar las direcciones del PCF8574 del Display LCD.
- Se dispone de un configurador para programar el módulo Bluetooth con los comandos AT

## App móvil

- Se dispone del código fuente de la App en [MIT  App Inventor](http://ai2.appinventor.mit.edu/)
