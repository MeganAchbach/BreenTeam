#include"NewPing.h"
#include<LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);

#define TRIGGER_A 7
#define ECHO_A 8
#define TRIGGER_B 9
#define ECHO_B 10
#define MAX_DISTANCE 200

NewPing sonar[2] = {
  NewPing(TRIGGER_A, ECHO_A, MAX_DISTANCE),
  NewPing(TRIGGER_B, ECHO_B, MAX_DISTANCE)
}

float distanceA, distanceB;
int enA=A0;
int in1=A1;
int in2=A2;

void runElevator();

void setup() {
  lcd.begin(16,2);
  lcd.clear();
  pinMode(enA,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
}

void loop() {
  distanceA = sonar[0].ping_cm();
  if(distanceA == 0){
    distanceB = sonar[1].ping_cm();
    if (distanceB <= 10){
      runElevator();
    }
  }
  delay(500);
}

void runElevator(){
  while(distanceA < 125){
    digitalWrite(in1,HIGH);
    digitalWrite(in2,HIGH);
    distanceA = sonar[0].ping_cm();
    delay(10);
  }
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  delay(7500);
  distanceA = sonar[0].ping_cm();
  while(distanceA != 0){
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    distanceA = sonar[0].ping_cm();
    delay(10);
  }
}
