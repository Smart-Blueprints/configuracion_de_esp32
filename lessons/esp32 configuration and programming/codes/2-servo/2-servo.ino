#include <ESP32Servo.h>

Servo servo; 

void setup() {
 
  servo.attach(19);
  
}

int a = 10;

void loop() {
  
  servo.write(a);
  delay(500);

  a += 10;
    
  if (a == 160)
    a = 10;



}
