#include <LiquidCrystal_I2C.h>
#include "DHT.h"

// Declaración de componentes
LiquidCrystal_I2C lcd(0x27,16,2);
const int BUZZER = 2, LED = 3, pinDHT = 4;
DHT dht(pinDHT, DHT11);

void esperar(float segundos){
  delay(segundos*1000);
}

void setup(){
  // Dirección de pines
  pinMode(LED_BUILTIN, OUTPUT); pinMode(LED, OUTPUT); pinMode(BUZZER, OUTPUT); pinMode(pinDHT, INPUT);
  // Inicio de componentes
  dht.begin(); lcd.init();
  // Secuencia de inicio del programa
  lcd.setCursor(5, 0); lcd.print("Hola!");
  esperar(1);
  lcd.setCursor(2, 1); lcd.print("Sensor Tmp."); 
  
  lcd.backlight(); tone(BUZZER,800,250);
  esperar(3);
  lcd.clear(); lcd.noBacklight();

  esperar(1);
  // Activar si se desea ver en el monitor
  // Serial.begin(9600);
}

void loop()
{
  float H = dht.readHumidity(), T = dht.readTemperature();
  // Serial.print("Temperatura: "); Serial.print(T,1); Serial.println(" grados.");
  // Serial.print("Humedad: "); Serial.print(H); Serial.println(" porciento.");

  // Secuencia si el sensor no puede leer los datos
  if(isnan(T) || isnan(H)){
    // Serial.println("Error de lectura");
    lcd.print("No se pudo detectar el tiempo atmosférico");
    esperar(1.5);
  } 
  else { 
    digitalWrite(LED, HIGH); lcd.backlight();
    lcd.print("Estado: ");
    // Estado optimo
    if(18<=T && T<=25) {
      esperar(0.1);
      digitalWrite(LED, LOW);
      // Secuencia LCD
      lcd.print("Optimo"); esperar(0.3);
      lcd.setCursor(10, 1); lcd.print(T); lcd.print("C");
      esperar(3);
    // Estado no optimo
    } else { 
      digitalWrite(LED, HIGH);
      // Secuencia LCD
      lcd.print("NO");
      lcd.setCursor(0, 1); lcd.print("optimo");
      lcd.setCursor(10, 1); lcd.print(T); lcd.print("C");
      // Alarma buzzer
      for(int i = 0; i < 10; i++) {
        tone(BUZZER,777,500);
        esperar(0.75);
      }
    }
    lcd.clear(); esperar(1);
  } // Fin del análisis de datos
} // Fin del loop