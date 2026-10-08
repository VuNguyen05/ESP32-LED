#include <Arduino.h>
#include <OneButton.h>
#define LED_PIN     25  
#define BUTTON_PIN  22  
OneButton button(BUTTON_PIN, true, true);
bool isBlinking = false; 
bool ledState = false;  

unsigned long previousMillis = 0;
const long interval = 500; 

void handleClick() {
  isBlinking = false;    
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState ? HIGH : LOW);
}


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
  // Lắng nghe và cập nhật trạng thái nút bấm liên tục
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