// MiCS-5524 Sensor Alcohol Tester with output on a Nokia LCD5110
//
#include <LCD5110_Graph.h>

//Gas Sensor
int TIME_UNTIL_WARMUP = 10; // warm up for 15 minutes!
unsigned long time;

int analogPin = 0;
int val = 0;

unsigned long previousMillis = 0;
long blinkInterval = 250;

//LCD Screen
LCD5110 myGLCD(8, 9, 10, 12, 11);

extern uint8_t SmallFont[];

void setup()
{
  Serial.begin(9600);

  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  randomSeed(analogRead(7));
}

void loop()
{

  delay(100);

  val = readAlcohol();
  printWarming();

  time = millis() / 1000;

  if (time <= TIME_UNTIL_WARMUP)
  {
    time = map(time, 0, TIME_UNTIL_WARMUP, 0, 100);
  } else
  {
    myGLCD.clrScr();
    printAlcohol(val);
    printAlcoholLevel(val);
    myGLCD.update();
  }

  myGLCD.update();

}

void printWarming()
{
  myGLCD.print("Breathalyzer", CENTER, 12);
  myGLCD.print("Warming up", CENTER, 24);
  Serial.println(analogRead(0));
}

void printAlcohol(int value)
{
  myGLCD.print(String(readAlcohol(), DEC), CENTER, 24);
}
void printAlcoholLevel(int value)
{
  if (value < 150)
  {
    myGLCD.print("You are sober.", CENTER, 12);
    Serial.println(analogRead(0));
  }
  if (value >= 150 && value < 250)
  {
    myGLCD.print("One beer.", CENTER, 12);
    Serial.println(analogRead(0));
  }
  if (value >= 250 && value < 350)
  {
    myGLCD.print("2+ beers.", CENTER, 12);
    Serial.println(analogRead(0));
  }
  if (value >= 350 && value < 450)
  {
    myGLCD.print("Many beers.", CENTER, 12);
    Serial.println(analogRead(0));
  }
  if (value > 450)
  {
    myGLCD.print("You are drunk!", CENTER, 12);
    Serial.println(analogRead(0));
  }
}

int readAlcohol()
{
  int val = 0;
  int val1;
  int val2;
  int val3;

  myGLCD.clrScr();
  val1 = analogRead(analogPin);
  delay(10);
  val2 = analogRead(analogPin);
  delay(10);
  val3 = analogRead(analogPin);

  val = (val1 + val2 + val3) / 3;
  return val;
}
