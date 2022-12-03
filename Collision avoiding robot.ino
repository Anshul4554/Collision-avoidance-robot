#include <Wire.h> 
#include <DHT.h> //DHT and LCD libraries
#include <LiquidCrystal_I2C.h>
#define I2C_ADDR 0x27 
#define DHTPIN 13
#define DHTTYPE DHT11
int direction_pin1=2;
int direction_pin2=3;
int speed_pin1=6;
int direction_pin3=4;
int direction_pin4=5;
int speed_pin2=10;
int speed=255;
int trig =11;
int echo=9;
float distance;
float duration;
DHT dht(DHTPIN,DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);
void setup() 
{
 pinMode(direction_pin1,OUTPUT);
 pinMode(direction_pin2,OUTPUT);
 pinMode(speed_pin1,OUTPUT);

 pinMode(direction_pin3,OUTPUT);
 pinMode(direction_pin4,OUTPUT);
 pinMode(speed_pin2,OUTPUT);

 pinMode(trig,OUTPUT);
 pinMode(echo,INPUT);
 
 Serial.begin(9600);
 lcd.clear();
 lcd.backlight();// turn on lcd backlight
 lcd.init();// initialize lcd
 dht.begin();// initialize the sensor
}
void forward()
 {
  digitalWrite(direction_pin1,LOW);
  digitalWrite(direction_pin2,HIGH);
  analogWrite(speed_pin1,speed);

  digitalWrite(direction_pin3,LOW);
  digitalWrite(direction_pin4,HIGH);
  analogWrite(speed_pin2,speed);
 }
 void backward()
 {
  digitalWrite(direction_pin1,HIGH);
  digitalWrite(direction_pin2,LOW);
  analogWrite(speed_pin1,speed);

  digitalWrite(direction_pin3,HIGH);
  digitalWrite(direction_pin4,LOW);
  analogWrite(speed_pin2,speed);
 }
void left()
 {
  digitalWrite(direction_pin1,LOW);
  digitalWrite(direction_pin2,HIGH);
  analogWrite(speed_pin1,speed);

  digitalWrite(direction_pin3,HIGH);
  digitalWrite(direction_pin4,LOW);
  analogWrite(speed_pin2,speed);
  delay(500);
 }
void right()
 {
  digitalWrite(direction_pin1,HIGH);
  digitalWrite(direction_pin2,LOW);
  analogWrite(speed_pin1,speed);

  digitalWrite(direction_pin3,LOW);
  digitalWrite(direction_pin4,HIGH);
  analogWrite(speed_pin2,speed);
 }
 
void loop()
{ 
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration = pulseIn(echo,HIGH);
  distance = (0.034*duration)/2;
  Serial.println(distance);
  lcd.clear();
  lcd.setCursor(0,0);
  int chk = dht.read(DHTPIN);
    
    if(distance<=10){
   lcd.setCursor(0,0);
   lcd.print("Humidity=");
   lcd.print((float)dht.readHumidity());
   lcd.print("%");
   lcd.setCursor(0,1);
   lcd.print("Temp=");
   lcd.print((float)dht.readTemperature());
   lcd.print("Celsius");
   delay(2000);
   lcd.clear();
    left();}
  else
    forward();
 }
