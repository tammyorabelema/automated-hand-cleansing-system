
#include <LiquidCrystal.h>
int Tank_height = 6; // Distance from the installed face of the transducer, down to the bottom of the tank
int Fill_height = 4; // Distance from the bottom of the tank,up to the maximum desired liquid height
//----------------------------------------//
const long eventInterval = 15000;
unsigned long startTime = 0 ;
unsigned long elapsedTime;
const unsigned long eventInterval1 = 20000;
unsigned int timeRunning;
long t;
int distance_Measured;
int distance_Sensor_to_Fill;

unsigned char a = 0;
unsigned int level = 0;
unsigned int temp = 2;
int tankLevel;

//int SCL_PIN = 4;
//int SDA_PIN = 5;

int trigPin = 7;
int echoPin = 6;
int IRSensor1 = 8;
int IRSensor = 9; // connect IR sensor module to Arduino pin D9
int HUMID = 13; // connect LED to Arduino pin 13
int Fan = A4;
int MuteSwitch = A5;
int alarm_output = 10;
// Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup()
{
  
   Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //pinMode(SCL_PIN,OUTPUT);
 // pinMode(SDA_PIN,OUTPUT);  
  pinMode(alarm_output,OUTPUT); 
  pinMode(MuteSwitch,INPUT_PULLUP);      
  digitalWrite(alarm_output,LOW); 
 // digitalWrite(SCL_PIN,HIGH);;;

pinMode(IRSensor, INPUT); // IR Sensor pin INPUT
  pinMode(HUMID, OUTPUT); // LED Pin Output
 pinMode(Fan, OUTPUT);
    delay(10);
    
    //oled_init
    int k;
    for(k=0;k<26;k++)
    {
//    write_cmd(pgm_read_byte(&init_display[k]));    
    }
           
    distance_Sensor_to_Fill = Tank_height - Fill_height;

     // set up the LCD's number of columns and rows:
 lcd.begin(16, 2);
  lcd.setCursor(2, 0);
  lcd.print("HAND CLEANSER");
  lcd.setCursor(0, 1);
  lcd.print("BIOMEDICAL ENG.");
  delay(3000);
  lcd.clear();
   lcd.setCursor(1, 0);
  lcd.print("PROJECT DEVICE");
  lcd.setCursor(3, 1);
  lcd.print("HAND CLEANSER");
  delay(3000);
  lcd.clear();
   lcd.setCursor(2, 0);
  lcd.print("Supervised By");
  lcd.setCursor(0, 1);
  lcd.print("ENGR.T.OLUTOSOYE ");
  delay(1000);
  lcd.clear();
}


void loop()
{
  unsigned long currentTime = millis();
 int sensorStatus = digitalRead(IRSensor); // Set the GPIO as Input
 int sensorStatus1 = digitalRead(IRSensor1);
  if (sensorStatus == 0 && sensorStatus1 == 0 ) // Check if the pin high or not
  {  
    //unsigned long currentTime = millis();
   // Serial.println(currentTime);
   // Serial.println(previousTime);
    // if the pin is high turn off the onboard Led
    
    Serial.println("Motion Detected!"); // print Motion Detected! on the serial monitor window
    if (tankLevel >= 10)
    {
    if (timeRunning == 0){
      startTime =millis();
      timeRunning = 1;
      digitalWrite(HUMID, HIGH);
      Serial.println("TIME started FOR Humid");
      Serial.println(startTime);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Misting Hands");
    }
     elapsedTime = currentTime - startTime;
    if (elapsedTime >= eventInterval){
       digitalWrite(HUMID, LOW);
       digitalWrite(Fan, HIGH);
       Serial.println("Fan started!");
       Serial.println("Humid stoped!");
       lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Drying Hands");
      
      }
     if (elapsedTime >= eventInterval1){
       digitalWrite(Fan, LOW);
       Serial.println("Fan stopped!");
       lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("DONE !!!");
    }
    }
    else {
       lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("PLEASE REFILL !!");
    }
  }
  else  {
    //unsigned long currentTime = millis();
    elapsedTime = 0;
    timeRunning = 0;
     Serial.println("Time stopped!");
  // unsigned long previousTime = millis() ;
    //else turn on the onboard LED
    digitalWrite(HUMID, LOW); // LED High
    digitalWrite(Fan, LOW);
    Serial.println("Motion Ended!"); // print Motion Ended! on the serial monitor window
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Insert Palms");
  }

  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  t = pulseIn(echoPin, HIGH);
  distance_Measured = t/58;

  tankLevel = map(distance_Measured, distance_Sensor_to_Fill, Tank_height, 100, 0);
  if (tankLevel > 100) 
  tankLevel = 100;
  if (tankLevel < 0) 
  tankLevel = 0;
   
  lcd.setCursor(0, 1);
  lcd.print("LIQUID Level:");
  lcd.print(tankLevel);
  lcd.print("%");
  
  Serial.print("Tank Level:");
  Serial.print(tankLevel);
  Serial.println("%");

  if(tankLevel < 25)
  {
  level = 0;
  }
  else
  if((tankLevel >= 25) && (tankLevel < 50))
  {
  level = 1;
  }  

  else
  if((tankLevel >= 50) && (tankLevel < 75))
  {
  level = 2;
  }  

  else
  if((tankLevel >= 75) && (tankLevel < 100))
  {
  level = 3;
  }  

  else
  if(tankLevel >= 100)
  {
  level = 4;
  } 
  if(level != temp)
  {
    temp = level;

  displayLevel();
  }


    if(level == 0)
    alarmEmpty();

    if(level == 1)
    a=0;
    
    if(level == 2)
    a=0;

    if(level == 3)
    a=0;    
    
    if(level == 4)
    alarmFull();

    delay(300);
}  
  
void alarmFull()
{
  
if(digitalRead(MuteSwitch) == LOW)
a = 1;

if(a == 0)
{  
unsigned int i, k;
  
for(k = 0; k < 2; k++)  
{  
for(i = 0; i < 200; i++)
{
digitalWrite(alarm_output,HIGH);
delayMicroseconds(250);
digitalWrite(alarm_output,LOW);
delayMicroseconds(250);
}

for(i = 0; i < 250; i++)
{
digitalWrite(alarm_output,HIGH);
delayMicroseconds(200);
digitalWrite(alarm_output,LOW);
delayMicroseconds(200);
}  
}
} 
}

void alarmEmpty()
{
  
if(digitalRead(MuteSwitch) == LOW)
a = 1;

if(a == 0)
{ 
  
unsigned int i;

for(i = 0; i < 400; i++)
{
digitalWrite(alarm_output,HIGH);
delayMicroseconds(200);
digitalWrite(alarm_output,LOW);
delayMicroseconds(200);
} 
}
}

 void displayLevel()
 {
  if(level == 0){
  
  }

  if(level == 1)
 {
 }

 if(level == 2)
 {
 }






 if(level == 3)
 {
 }

  if(level == 4)
  {
  }

 

 
 
 
}
