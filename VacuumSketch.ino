#include <NewPing.h>
#include <AccelStepper.h>
#define SONAR_NUM 3      
#define MAX_DISTANCE 200 

NewPing sonar[SONAR_NUM] = {   
  NewPing(8, 9, MAX_DISTANCE),  
  NewPing(8, 10, MAX_DISTANCE), 
  NewPing(8, 11, MAX_DISTANCE)
};

AccelStepper myStepper(8, 0, 1, 2, 3);
AccelStepper myStepper2(8, 4, 5, 6, 7);
void setup() { 
  myStepper.setMaxSpeed(1000);
  myStepper2.setMaxSpeed(1000); 
}

void forward()
{
myStepper.setCurrentPosition(0);
myStepper2.setCurrentPosition(0);
while(myStepper.currentPosition()!=-1000 && myStepper2.currentPosition()!=-1000)
{myStepper.setSpeed(-500);
myStepper.runSpeed();
myStepper2.setSpeed(-500);
myStepper2.runSpeed();
}
}
void backward()
{
myStepper.setCurrentPosition(0);
myStepper2.setCurrentPosition(0);
while(myStepper.currentPosition()!=2000 && myStepper2.currentPosition()!=2000)
{myStepper.setSpeed(500);
myStepper.runSpeed();
myStepper2.setSpeed(500);
myStepper2.runSpeed();
right();
}
}

void left()
{
myStepper.setCurrentPosition(0);
myStepper2.setCurrentPosition(0);
while(myStepper.currentPosition()!=-4500 && myStepper2.currentPosition()!=4500)
{myStepper.setSpeed(-500);
myStepper.runSpeed();
myStepper2.setSpeed(500);
myStepper2.runSpeed();
}
forward();
myStepper.setCurrentPosition(0);
myStepper2.setCurrentPosition(0);
while(myStepper.currentPosition()!=-4500 && myStepper2.currentPosition()!=4500)
{myStepper.setSpeed(-500);
myStepper.runSpeed();
myStepper2.setSpeed(500);
myStepper2.runSpeed();
}
}

void right()
{
myStepper.setCurrentPosition(0);
myStepper2.setCurrentPosition(0);
while(myStepper.currentPosition()!=4500 && myStepper2.currentPosition()!=-4500)
{myStepper.setSpeed(500);
myStepper.runSpeed();
myStepper2.setSpeed(-500);
myStepper2.runSpeed();
}
forward();
myStepper.setCurrentPosition(0);
myStepper2.setCurrentPosition(0);
while(myStepper.currentPosition()!=4500 && myStepper2.currentPosition()!=-4500)
{myStepper.setSpeed(500);
myStepper.runSpeed();
myStepper2.setSpeed(-500);
myStepper2.runSpeed();
}
}
/*
 sonar[0]=dreapta
 sonar[1]=fata
 sonar[2]=stanga
 */

void verificare()
{
  if(sonar[0].convert_cm(sonar[0].ping_median()) && sonar[1].convert_cm(sonar[1].ping_median()) && sonar[2].convert_cm(sonar[2].ping_median()))
  if(sonar[1].convert_cm(sonar[1].ping_median())>7.)
  forward();
  else
{
  if(sonar[0].convert_cm(sonar[0].ping_median())<7. && sonar[2].convert_cm(sonar[2].ping_median())<7.)
  backward();
  else
  {if(sonar[0].convert_cm(sonar[0].ping_median())<7. && sonar[2].convert_cm(sonar[2].ping_median())>7.)
  left();
  else{
  if(sonar[0].convert_cm(sonar[0].ping_median())>7. && sonar[2].convert_cm(sonar[2].ping_median())<7.)
  right();
  else
  {if(sonar[0].convert_cm(sonar[0].ping_median())>7. && sonar[2].convert_cm(sonar[2].ping_median())>7.)
  right();
}
  }
}
}
}
/*
 verificare:
 0 - forward
 1 - backward
 2 - right
 3 - left
 4 - com
 */

void loop() {
  delay(100);
bool ok=true;
for(uint8_t i=0;i<SONAR_NUM && ok;i++)
  {
  if(sonar[i].convert_cm(sonar[i].ping_median())!=0.)
  if(sonar[i].convert_cm(sonar[i].ping_median())<7.)
  ok=false;
  }
  if(ok)
  {
  forward();  
  }
  else
  {
  verificare();
  }
  
}
