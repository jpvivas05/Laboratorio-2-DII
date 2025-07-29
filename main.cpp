//Librerías incluidas

#include <Arduino.h>
#include <stdint.h>

// Definición de pines
#define LED1 32
#define LED2 25
#define LED3 14
#define LED4 13
#define B1 18 // Botón para aumentar
#define B2 21 // Botón para disminuir
#define B3 23 // Botón para cambiar de modo

// Variables globales
int cont = 0;
bool modoBinario = false; // Comienza en decimal

// Estado anterior de cada botón para detectar el flanco de subida/bajada
bool ultimoEstadoB1 = LOW;
bool ultimoEstadoB2 = HIGH;
bool ultimoEstadoB3 = LOW;

// Tiempos para el debounce de cada botón
unsigned long tiempoUltimaPulsacionB1 = 0;
unsigned long tiempoUltimaPulsacionB2 = 0;
unsigned long tiempoUltimaPulsacionB3 = 0;

const unsigned long DEBOUNCE_DELAY = 250; // Retardo de debounce en milisegundos.

// Prototipos de funciones
void actualizarLeds();
void mostrarDecimal(int valor);
void mostrarBinario(int valor);

void setup() {
  // Configuración de pines de LEDs como salidas
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  // Configuración de botones como entradas
  pinMode(B1, INPUT_PULLDOWN); // B1 activa en HIGH
  pinMode(B2, INPUT_PULLUP);   // B2 activa en LOW
  pinMode(B3, INPUT); // B3 manual

  // Inicializa los LEDs en el estado inicial
  actualizarLeds();
}
//Funciones principales
void loop() {

  unsigned long tiempoActual = millis();

  // Lógica para el botón B1
  bool lecturaB1 = digitalRead(B1);
  // Detectar un flanco de subida
  if (lecturaB1 == HIGH && ultimoEstadoB1 == LOW) {
    if ((tiempoActual - tiempoUltimaPulsacionB1) > DEBOUNCE_DELAY) {
      if (modoBinario) {
        cont = (cont + 1) % 16; //Se especifica tamaño del contador con %
      } else {
        cont = (cont + 1) % 4;
      }
      actualizarLeds();
      tiempoUltimaPulsacionB1 = tiempoActual; // Guarda el tiempo de esta pulsación válida
    }
  }
  ultimoEstadoB1 = lecturaB1; // Actualiza el estado anterior del botón B1

  //Lógica para el botón B2
  bool lecturaB2 = digitalRead(B2);
  //Detectar un flanco de bajada
  if (lecturaB2 == LOW && ultimoEstadoB2 == HIGH) {
    if ((tiempoActual - tiempoUltimaPulsacionB2) > DEBOUNCE_DELAY) {
      if (modoBinario) {
        cont = (cont - 1 + 16) % 16;
      } else {
        cont = (cont - 1 + 4) % 4;
      }
      actualizarLeds();
      tiempoUltimaPulsacionB2 = tiempoActual; // Guarda el tiempo de esta pulsación válida
    }
  }
  ultimoEstadoB2 = lecturaB2; // Actualiza el estado anterior del botón B2

  // Lógica para el botón B3
  bool lecturaB3 = digitalRead(B3);
  // Detectar un flanco de subida
  if (lecturaB3 == HIGH && ultimoEstadoB3 == LOW) {
    if ((tiempoActual - tiempoUltimaPulsacionB3) > DEBOUNCE_DELAY) {
      modoBinario = !modoBinario; // Invierte el estado del modo
      cont = 0;               // Reinicia el contador al cambiar de modo
      actualizarLeds();
      tiempoUltimaPulsacionB3 = tiempoActual; // Guarda el tiempo de esta pulsación válida
    }
  }
  ultimoEstadoB3 = lecturaB3; // Actualiza el estado anterior del botón B3
}

// Funciones Auxiliares
void actualizarLeds() {
  if (modoBinario) {
    mostrarBinario(cont);
  } else {
    mostrarDecimal(cont);
  }
}

void mostrarDecimal(int valor) {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);

  switch (valor) {
    case 0:
      digitalWrite(LED1, HIGH);
      break;
    case 1:
      digitalWrite(LED2, HIGH);
      break;
    case 2:
      digitalWrite(LED3, HIGH);
      break;
    case 3:
      digitalWrite(LED4, HIGH);
      break;
  }
}

void mostrarBinario(int valor) {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);

  switch (valor) {
    case 0:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      break;
    case 1:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      break;
    case 2:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      break;
    case 3:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      break;
    case 4:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, LOW);
      break;
      case 5:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, LOW);
      break;
      case 6:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, LOW);
      break;
      case 7:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, LOW);
      break;
      case 8:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, HIGH);
      break;
    case 9: 
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, HIGH);
      break;
    case 10: 
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, HIGH);
      break;
    case 11:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, HIGH);
      break;
    case 12:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
      break;
    case 13:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
      break;
    case 14:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
      break;
    case 15:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
      break;
  }
}