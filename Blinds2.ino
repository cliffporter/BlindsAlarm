#include <Wire.h>
#include <DS3231.h>
#include <LittleFS.h>


//~~~~~Alarm times~~~~~
#define closeHour 5
#define alarmHour 8 //24hour time
#define startMin 28
#define endMin 30

//~~~~~~Settings~~~~~~~
#define resetTime 10
#define contSteps false
#define descStepNum 2


//Configuration
#define STP1 6
#define STP2 7
#define STP3 8
#define STP4 9
//Clk d%clk 5&6
#define clkSqw 
#define bUp 10
#define bCent 11
#define bDwn 12

//Global vars
int Step = 0;


RTClib myRTC;


void setup() {
  Serial.begin(9600);
  pinMode(STP1, OUTPUT);
  pinMode(STP2, OUTPUT);
  pinMode(STP3, OUTPUT);
  pinMode(STP4, OUTPUT);
  pinMode(bUp, INPUT_PULLUP);
  pinMode(bDwn, INPUT_PULLUP);
  pinMode(bCent, INPUT_PULLUP);
  Serial.write("Start\n");
  Wire.begin();
  LittleFS.begin();
}

void loop() {
  DateTime now = myRTC.now();
  
}
