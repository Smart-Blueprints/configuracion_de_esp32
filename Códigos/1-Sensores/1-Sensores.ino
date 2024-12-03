#define GAS_SENSOR 36
#define LIGHT_SENSOR 39
#define SOIL_HUMIDITY_SENSOR 34
#define RAIN_SENSOR 35
#define PIR_MOTION_SENSOR 25

volatile double gas = 0;
volatile double light = 0;
volatile double soil = 0;
volatile double rain = 0; 
volatile bool motion = 0;

void setup() {
  Serial.begin(9600);//set baud rate to 9600
  
  pinMode(PIR_MOTION_SENSOR, INPUT);

}

void loop() {
  
  gas = double(analogRead(GAS_SENSOR)*100)/4096;
  light = double(analogRead(LIGHT_SENSOR)*100)/4096;
  soil = double(analogRead(SOIL_HUMIDITY_SENSOR)*100)/4096;  
  rain = double(analogRead(RAIN_SENSOR)*100)/4096;
  motion = digitalRead(PIR_MOTION_SENSOR);

  Serial.println("Gas:" + String(gas));
  Serial.println("Light:" + String(light));
  Serial.println("Soil:" + String(soil));
  Serial.println("Rain:" + String(rain));
  Serial.println("Motion:" + String(motion));
  Serial.println("");
  delay(3000);

}
