#define led_pin 12

int canal = 0;
int frecuencia = 5000;
int resolucion = 8;

void setup() {

  ledcSetup(canal, frecuencia, resolucion);
  ledcAttachPin(led_pin, canal);

}

void loop() {

  for( int i = 0; i <= 255; i+=5){
    ledcWrite(canal, i);
    delay(30);
  }

  for( int i = 255; i >= 0; i-=5){
    ledcWrite(canal, i);
    delay(30);
  }    
  
}
