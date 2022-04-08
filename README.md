# Semáforo Violencia de Género

Proyecto desarrollado para el IES Güimar para implementar un semaforo controlado por Bluetooth mediante una App movil. El Arduino se encarga de controlar el encendido de 3 relés que activan cada bombilla del semáforo.

## Autores
- José Luis González de Chávez 
- Augusto Samuel Hernández Martín

## Materiales
- Arduino Nano
- Protoboard MB-102
- Alimentador MB-102
- Fuente Alimentacion 12V 2A
- Módulo de 3 relés
- Módulo Bluetooth HC-06
- Display LCD 16x02

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

- Se dispone del código fuente de la App en MIT  App Inventor
