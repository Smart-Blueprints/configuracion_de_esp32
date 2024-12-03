
#define fan_pin 13

int canal = 0;
int frecuencia = 5000;
int resolucion = 8;

void setup() {

  ledcSetup(canal, frecuencia, resolucion);
  ledcAttachPin(fan_pin, canal);

}

void loop() {

  for( int i = 255; i >= 0; i-=5){
    ledcWrite(canal, i);
    delay(30);
  }    

  delay(1000);

  for( int i = 0; i <= 255; i+=5){
    ledcWrite(canal, i);
    delay(30);
  }

    delay(1000);
  


}
