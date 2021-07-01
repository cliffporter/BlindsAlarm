#include <Wire.h>
#include <DS3231.h>
//#include <LittleFS.h>

RTClib myRTC;
DS3231 Clock;

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

//Clk dat/clk 5&6
#define RTCsqwpin 2

#define bUp 10
#define bCent 11
#define bDwn 12
//#define bMenu 
//#define dispClk 
//#define dispDat 


//Global vars
int Step = 0;





void setup() 
{
  Serial.begin(9600);
  
  pinMode(STP1, OUTPUT);
  pinMode(STP2, OUTPUT);
  pinMode(STP3, OUTPUT);
  pinMode(STP4, OUTPUT);
  pinMode(bUp, INPUT_PULLUP);
  pinMode(bDwn, INPUT_PULLUP);
  pinMode(bCent, INPUT_PULLUP);

  pinMode(RTCsqwpin, INPUT);

  Wire.begin();
}

void updateTime();

int curHour=0, curMin=0, curSec=0;

void loop() 
{
  DateTime now = myRTC.now();

  
  //Main setup
  Clock.enable32kHz(1); //Second pulse
  Clock.enableOscillator(true, false, 0);
  int lastsqwstate = -1;
  
  Serial.print("Initialized\n");

  
  //Actual loop
  while(1)
  {
    //Check for a time update
    lastsqwstate = updateTime(lastsqwstate);
    

  }
}

//Functions

//Wait for the second to tic over to prevent hammering the RTC
int updateTime(int lastsqwstate)
{
  DateTime now = myRTC.now();
  int sqwstate = digitalRead(RTCsqwpin);
  if (sqwstate != lastsqwstate) //Clock edge
  {
    if (sqwstate == HIGH) //High edge -> Next second
    {
      
      curSec = now.second();
      lastsqwstate = sqwstate;
      
      Serial.print("Sec: "); //Drift log
      Serial.print(curSec, DEC);
      Serial.write("\n");
    }
    else //Low edge
      lastsqwstate = sqwstate;
  }

  if(curSec==0)
    curMin = now.minute();
  if(curMin==0)
    curHour = now.hour();

  return sqwstate;
}
