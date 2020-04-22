#include <Wire.h>

int led = 13;

int pot;

void setup()
{
  Serial.begin(9600);
  Wire.begin(8);
  Wire.onReceive(dataReceived);
  pinMode(8, OUTPUT);
  pinMode(led, OUTPUT);
}

void loop()
{
}

void dataReceived(int howMany)
{
  pot = Wire.read();
  analogWrite(led, pot);
}