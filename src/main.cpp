#include <Arduino.h>
#include <OneButton.h>

#define LED_PIN     25  
#define BUTTON_PIN  22  
OneButton button(BUTTON_PIN, true, true);

bool isBlinking = false; 
bool ledState = false;  

unsigned long previousMillis = 0;
const long interval = 500; 

// Hàm xử lý sự kiện Nhấn đơn (Single Click)
void handleClick() {
  isBlinking = false;    
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState ? HIGH : LOW);
}

// Hàm xử lý sự kiện Nhấn kép (Double Click)
void handleDoubleClick() {
  isBlinking = !isBlinking; 
  
  if (!isBlinking) {
    ledState = false;
    digitalWrite(LED_PIN, LOW);
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  button.attachClick(handleClick);             
  button.attachDoubleClick(handleDoubleClick); 
}

void loop() {
  button.tick();
  if (isBlinking) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState ? HIGH : LOW);
    }
  }
}