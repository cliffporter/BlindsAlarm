#include <Wire.h>
#include <DS3231.h>
//#include <LittleFS.h>


RTClib myRTC;
DS3231 Clock;

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
#define bMenu 13
#define dispClk 14
#define dispDat 15


//Global vars
//int curHour=0, curMin=0, curSec=0;

class Alarm
{
  int curStep;
  int curHour, curMin, curSec;
  int sqState, lastSqState, timeInit, millsLastPolled, clkPrinted;
  int a1HourStart, a1MinStart, a1Type;
  int a2Hour, a2Min, a2Sec, a2Type;

  public:
  Alarm()
  {
    timeInit=0;
    curStep=0;
    curHour=0, curMin=0, curSec=0;
    sqState=0, lastSqState=-1;
    clkPrinted=0;

    Clock.enable32kHz(1); //Second pulse
    Clock.enableOscillator(true, false, 0);
    
  }

  void update()
  {
    timeCheck();
    
  }

  void timeCheck()
  {
    DateTime now = myRTC.now();
    sqState = digitalRead(RTCsqwpin);
    
    if (sqState != lastSqState) //Clock edge
    {
      if (sqState == HIGH) //High edge -> Next second
      {
        curSec = now.second();
        millsLastPolled = millis();
        lastSqState = sqState;
      }
      else //Low edge
        lastSqState = sqState;
    }
  
    if((millis()>millsLastPolled+500&&curSec==0) || timeInit==0) //Update min and sec (avoid polling quickly)
      curMin = now.minute();
    if(curSec==1||timeInit==0)
    {
      curHour = now.hour();
      timeInit==1;
    }
    //Clock monitor
    if(clkPrinted==0&&(curSec==00||curSec==15||curSec==30||curSec==45))
    {
      Serial.print("Time: ");
      Serial.print(curHour, DEC);
      Serial.print(':');
      Serial.print(curMin, DEC);
      Serial.print(':');
      if(curSec==0)
        Serial.print('0');
      Serial.print(curSec, DEC);
      Serial.println();
      clkPrinted=1;
    }
    else if (clkPrinted==1&&(curSec==01||curSec==16||curSec==31||curSec==46))
      clkPrinted=0;
  }
  
  void secondDriftShift(int shiftAmt)
  {
    Clock.setSecond(curSec+shiftAmt);
  }
  
};

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

  Wire.begin(); //RTC module (4&5)
}


//Function prototypes
void updateTime();

void loop() 
{
 // DateTime now = myRTC.now();

  
  //Main setup
  //Clock.enable32kHz(1); //Second pulse
  //Clock.enableOscillator(true, false, 0);
  //int lastsqwstate = -1;
  
  Serial.print("Initialized\n");

  Alarm alarm1;
  
  //Actual loop
  while(1)
  {
    //Check for a time update
    alarm1.update();


    

  }
}


//Functions

//Wait for the second to tic over to prevent hammering the RTC
/**
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
*/
