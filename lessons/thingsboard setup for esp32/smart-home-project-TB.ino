#include <WiFi.h>
#include <ThingsBoard.h>
#include <Arduino_MQTT_Client.h>
#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>

// Wifi
#define WIFI_AP "Smart_Home"
#define WIFI_PASS "87654321"

// Server
#define TB_SERVER "thingsboard.cloud"
#define TOKEN "XDi2Z7CC4RDNV24uIbDX"

// Parameters
#define GAS_SENSOR 36
#define LIGHT_SENSOR 39
#define SOIL_HUMIDITY_SENSOR 34
#define RAIN_SENSOR 35
#define PIR_MOTION_SENSOR 25
#define BUTTON_1 26
#define BUTTON_2 27
#define PASSIVE_BUZZER 14
#define YELLOW_LED 12
#define FAN 13
#define RELAY 23
#define SERVO_DOOR 19
#define SERVO_WINDOW 18
#define WHITE_LED 4

constexpr uint16_t MAX_MESSAGE_SIZE = 128U;

constexpr char WHITE_LED_STATE_ATTR[] = "whiteLedState";
constexpr char YELLOW_LED_STATE_ATTR[] = "yellowLedState";
constexpr char FAN_STATE_ATTR[] = "fanState";
constexpr char RELAY_STATE_ATTR[] = "relayState";
constexpr char SERVO_DOOR_STATE_ATTR[] = "servoDoorState";
constexpr char SERVO_WINDOWS_STATE_ATTR[] = "servoWindowState";

constexpr std::array<const char *, 8U> SHARED_ATTRIBUTES_LIST = {
  WHITE_LED_STATE_ATTR,
  YELLOW_LED_STATE_ATTR,
  FAN_STATE_ATTR,
  RELAY_STATE_ATTR,
  SERVO_DOOR_STATE_ATTR,
  SERVO_WINDOWS_STATE_ATTR
};

LiquidCrystal_I2C mylcd(0x27, 16, 2);
  
Servo servo_door;
Servo servo_window;

volatile double gas = 0;
volatile double light = 0;
volatile double soil = 0;
volatile double rain = 0; 
volatile bool motion = 0;

volatile bool whiteLed = false;
volatile bool yellowLed = false;
volatile bool fan = false;
volatile bool relay = false;
volatile bool servoDoor = false;
volatile bool servoWindow = false;

unsigned long previousTime;

WiFiClient espClient;
Arduino_MQTT_Client mqttClient(espClient);
ThingsBoardSized<256> tb(mqttClient, MAX_MESSAGE_SIZE);

/**
 * connectToWiFi 
**/
void connectToWiFi() {
  Serial.println("Connecting to WiFi...");
  int attempts = 0;
  
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    WiFi.begin(WIFI_AP, WIFI_PASS, 6);
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nFailed to connect to WiFi.");
  } else {
    Serial.println("\nConnected to WiFi");
  }
}

/**
 * connectToThingsBoard 
**/
void connectToThingsBoard() {
  Serial.println("Connecting to ThingsBoard server");
    
  if (!tb.connect(TB_SERVER, TOKEN)) {
      Serial.println("Failed to connect to ThingsBoard");
  } 
  else {
    Serial.println("Connected to ThingsBoard");
  }
}

/**
 * sendDataToThingsBoard
 * Send data to ThingsBoard
**/
void sendDataToThingsBoard(int gas, int light, int soil, int rain, bool motion) {
  String jsonData = "{\"Gas\":" + String(gas) + ", \"Light\":" + String(light) + ", \"Soil\":" + String(soil) + ", \"Rain\":" + String(rain) + ", \"Motion\":" + String(motion) + "}";
  tb.sendTelemetryJson(jsonData.c_str());
  Serial.println("Data sent");
}

/**
 * processSharedAttributes
 * Send data to ThingsBoard
**/
void processSharedAttributes(const Shared_Attribute_Data &data) {
  for (auto it = data.begin(); it != data.end(); ++it) {
    if (strcmp(it->key().c_str(), WHITE_LED_STATE_ATTR) == 0) {
      whiteLed = it->value().as<bool>();
      digitalWrite(WHITE_LED, whiteLed);
    }
    else if (strcmp(it->key().c_str(), YELLOW_LED_STATE_ATTR) == 0) {
      yellowLed = it->value().as<bool>();
      digitalWrite(YELLOW_LED, yellowLed);
    }
    else if (strcmp(it->key().c_str(), FAN_STATE_ATTR) == 0) {
      fan = it->value().as<bool>();
      digitalWrite(FAN, !fan);
    }
    else if (strcmp(it->key().c_str(), RELAY_STATE_ATTR) == 0) {
      relay = it->value().as<bool>();
      digitalWrite(RELAY, relay);
    }
    else if (strcmp(it->key().c_str(), SERVO_DOOR_STATE_ATTR) == 0) {
      servoDoor = it->value().as<bool>();   
      servo_door.write(servoDoor ? 180: 0);
    }
    else if (strcmp(it->key().c_str(), SERVO_WINDOWS_STATE_ATTR) == 0) {
      servoWindow = it->value().as<bool>();
        servo_window.write(servoWindow ? 210: 75);
    }
  }
}

const Shared_Attribute_Callback attributes_callback(&processSharedAttributes, SHARED_ATTRIBUTES_LIST.cbegin(), SHARED_ATTRIBUTES_LIST.cend());
const Attribute_Request_Callback attribute_shared_request_callback(&processSharedAttributes, SHARED_ATTRIBUTES_LIST.cbegin(), SHARED_ATTRIBUTES_LIST.cend());


/**
 * setup 
**/
void setup() {
  Serial.begin(115200);
  
  // init lcd
  mylcd.init();
  mylcd.backlight();
  mylcd.setCursor(0, 0);
  mylcd.print("Welcome!");
  
  // init servos
  servo_door.attach(SERVO_DOOR);
  servo_window.attach(SERVO_WINDOW);
  servo_door.write(0);
  servo_window.write(75);
  
  // ping assigned
  pinMode(PIR_MOTION_SENSOR, INPUT);
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  
  pinMode(PASSIVE_BUZZER, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(FAN, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(WHITE_LED, OUTPUT);

  // init analog pins
  digitalWrite(YELLOW_LED, yellowLed);
  digitalWrite(FAN, !fan);
  digitalWrite(RELAY, relay);
  digitalWrite(WHITE_LED, whiteLed);

  previousTime = millis();
}



/**
 * loop 
**/
void loop() {
  
   connectToWiFi();

   if (!tb.connected()) {
    connectToThingsBoard();
      
    if (!tb.Shared_Attributes_Subscribe(attributes_callback)) {
     Serial.println("Failed to subscribe for shared attribute updates");
     return;
    }
    else
      Serial.println("Subscribe done");

    // Request current states of shared attributes
    if (!tb.Shared_Attributes_Request(attribute_shared_request_callback)) {
     Serial.println("Failed to request for shared attributes");
     return;
    }
    else
      Serial.println("Subscribe done");
  }

    if ( (millis() - previousTime) > 1000 )
    {
      gas = double(analogRead(GAS_SENSOR)*100)/4096;
      light = double(analogRead(LIGHT_SENSOR)*100)/4096;
      soil = double(analogRead(SOIL_HUMIDITY_SENSOR)*100)/4096;  
      rain = double(analogRead(RAIN_SENSOR)*100)/4096;
      motion = digitalRead(PIR_MOTION_SENSOR);
      
      sendDataToThingsBoard(gas, light, soil, rain, motion);
      
      previousTime = millis();
    }
  
  tb.loop();
}
