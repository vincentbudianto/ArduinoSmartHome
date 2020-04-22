#include <LiquidCrystal.h>
#include <Wire.h>

//               (RS, Enable, DB4, DB5, DB6, DB7)
LiquidCrystal lcd(12,     11,   5,   4,   3,   2);

int rangeEcho = 7;
int rangeTrig = 8;
int motion = 9;
int buzzer = 13;
int temperature = A0;
int potentiometer = A1;

double temp;
int pot;
int distance;
long duration;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(rangeEcho, INPUT);
  pinMode(motion, INPUT);
  pinMode(temperature, INPUT);
  pinMode(potentiometer, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(rangeTrig, OUTPUT);
  lcd.begin(16, 2);
}

void loop() {
  temp = ((((double)analogRead(temperature) / 1024) * 5) - 0.5) *100;
  
  digitalWrite(rangeTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(rangeTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(rangeTrig,LOW);
  duration = pulseIn(rangeEcho, HIGH);
  distance = duration * 0.034 / 2;
  
  if (temp > 75) {
    lcd.setCursor(0, 0);
    tone(buzzer, 500);
    delay(100);
    tone(buzzer, 200);
    delay(100);
    
  	if (distance > 100) {
	    lcd.print("Kebakaran||Open ");
    } else {
	    lcd.print("Kebakaran||Close");
	}
  } else {
    lcd.setCursor(0, 0);
  	noTone(buzzer);
    
  	if (distance > 100) {
	    lcd.print("         ||Open ");
	} else {
	    lcd.print("         ||Close");
	}
  }
  
  if (digitalRead(motion)) {
    lcd.setCursor(0, 1);
    lcd.print("Seseorang datang");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("                ");
  }
  
  pot = ((double)analogRead(potentiometer) / 1024) * 255;
  
  Wire.beginTransmission(8);
  Wire.write(pot);
  Wire.endTransmission();
}
 