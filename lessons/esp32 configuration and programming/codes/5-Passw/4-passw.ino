#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>
//Set the communication address of I2C to 0x27, display 16 characters every line, two lines in total
LiquidCrystal_I2C mylcd(0x27, 16, 2);

//set ports of two servos to digital 9 and 10
Servo servo_puerta;

volatile int btn1_num;//set variable btn1_num
volatile int btn2_num;//set variable btn2_num
volatile int button1;//set variable button1
volatile int button2;//set variable button2

String passwd;//string type variable passwd

void setup() {

}

void loop() {

  passwd = "";
  mylcd.init();
  mylcd.backlight();//initialize LCD
  //LCD shows "password:" at first row and column
  mylcd.setCursor(1 - 1, 1 - 1);
  mylcd.print("password:");
  
  servo_puerta.attach(19);//make servo connect to digital
  servo_puerta.write(10);//set servo connected digital to 10°
  
  pinMode(26, INPUT);//set digital 26 to output
  pinMode(27, INPUT);//set digital 27 to output
  
  while(!door());
  
  delay(2000);

}


bool door() 
{  
  button1 = digitalRead(26);
  button2 = digitalRead(27);

  if (button1 == 0)
  {
    while (button1 == 0)
    {
      button1 = digitalRead(26);
      btn1_num = btn1_num + 1;
      delay(100);
    }
  }
  
  if (btn1_num >= 1 && btn1_num < 5)
  {
    Serial.print("*");
    Serial.print("");
    passwd = passwd + String("*");//set passwd
    //LCD shows pass at the first row and column
    mylcd.setCursor(1 - 1, 2 - 1);
    mylcd.print(passwd);
  }
  if (btn1_num >= 5)
  {
    Serial.print("_");
    passwd = passwd + String("_");//Set passwd
    //LCD shows pass at the first row and column
    mylcd.setCursor(1 - 1, 2 - 1);
    mylcd.print(passwd);
  }
  
  if (button2 == 0)
  {
      if (passwd == "**_*")
      {
        mylcd.clear();//clear LCD screen
        //LCD shows "open!" at first character on second row
        mylcd.setCursor(1 - 1, 2 - 1);
        mylcd.print("Open!");
        servo_puerta.write(150);
        return true;
      } 
      else
      {
        mylcd.clear();//clear LCD screen
        //LCD shows "error!"at first character on first row
        mylcd.setCursor(1 - 1, 1 - 1);
        mylcd.print("Error!");
        passwd = "";
        delay(1000);
        //LCD shows "again" at first character on first row
        mylcd.setCursor(1 - 1, 1 - 1);
        mylcd.print("Try again:");
      }
  }
  
  btn1_num = 0;//set btn1_num to 0
  btn2_num = 0;//set btn2_num to 0
  return false;
}
