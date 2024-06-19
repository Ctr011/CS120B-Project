/*

    Calvin Trujillo ( ctruj011@ucr.edu )

    Discussion -  021

    Assignment: Custom Lab 120B



    Exercise Description: Full implementation of the custom lab. This file is the main file which will be running all the state machines. Memory allocation is a large problem creating this program
    however nothing that cannot be altered!!! A majority of the program needs to be commented out to save space on the R3 uno. Not sure why there is a small amount of space; hwoever, it pushed many items 
    off the table. Additionally, it at times causes the code to malfunction if there is less than 10% free. 

    Demo: https://youtu.be/SBprF2tVY5A
*/
// The following global variables are used to implement SynchSM
// functionality using the Arduino API. In contrast the zyBook,
// the Arduino API does not provide the programmer with direct
// access to Timer Interrupt functions. 
// The following global variables are used to implement SynchSM
// functionality using the Arduino API. In contrast the zyBook,
// the Arduino API does not provide the programmer with direct
// access to Timer Interrupt functions. 
// The following global variables are used to implement SynchSM
// functionality using the Arduino API. In contrast the zyBook,
// the Arduino API does not provide the programmer with direct
// access to Timer Interrupt functions.

#include <Arduino_AVRSTL.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include "rm.h"
#include "nok.h"
#include "fonts.h"
#include <cstring>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  

/*remove */

using namespace std;


const int MP = 0x68; 
int cn = 0; 
int once = 0;
unsigned int p = 0;

unsigned char x;
int X, Y, Z; 

unsigned int rua = 0;

bool on(){
  bool jim = false;
  if(Y > 28 && Y  < 32){
    jim = true; }
  else{cn++;}
  return jim; 
}


bool access = false; 

unsigned int cnt = 0;
int gcd_delay;
typedef struct task{
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
}task;

const unsigned short tasksNum = 3;
task tasks[tasksNum];


enum M0_States{PM0, PM1, PM2};
int M0_Tick(int stat1){
  switch(stat1){
    case PM0:
    stat1 = PM1;
    break;
    case PM1:
    if(cn == 0 && access == true){
      on();
    if(cnt < 9){
    //Serial.print("Working");
    for(int i = 0; i < 4; i++){
    g = rnd(a % i + m * (i+1) + (seed*cnt+1) * millis());
    if(g > 0){
      seed = g;
    }
    else { seed = g + m;}
    cc[i] = (seed % 10);
  }
  coin(); 
    if(check() == true){
       // Serial.print("Next to nothing");
        noLonger(code, ct);
    }
    //Serial.println("code repeating");
    cnt++; 
    stat1 = PM1;}
    stat1 = PM2;}
    stat1 = PM1; 
    break;
    case PM2:
      Serial.print("Code: ");
      Serial.println(noMore[cnt]);
      /*
      if( cnt < 3){
      CLRSC();
      print_txt("Code: ");
      for(int i = 0; i < 4; i++){
       print_txt(noMore[cnt][i]);}

    }
    */
    stat1 = PM1;
    break;
    }
  switch(stat1){
    case PM0:
    break;
    case PM1:
    break;
    case PM2:
    break;
    }
  return stat1;
}

/*

enum M1_States {GM0, GM1}; //Break LCD and SYSTEM    
int M1_Tick(int stat2){
  switch(stat2){
    case GM0:
    Serial.print("cn: ");
    Serial.println(cn);
    if(cn > 0){
    stat2 = GM1;}
    stat2 = GM0;
    break;
    case GM1:
    CLRSC();
    print_txt("ATTEMPTED TINKER... ENDING PROGRAM..."); //MOVED TO LOOP!!!
    stat2 = GM1;
    break;
    }
  switch(stat2){
    case GM0:
    break;
    case GM1:
    break;}
  return stat2;
  }


  */   /* This state machine did not work as intended. haha */

  
enum M2_States {HM0, HM1}; //RFID
int M2_Tick(int stat3){
  switch(stat3){
    case HM0:
    if(rua == 0){
    if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    stat3 = HM0;
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    stat3 = HM0;
  }
    // Dump debug info about the card; PICC_HaltA() is automatically called
    mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
 
    Serial.print("UID tag :");
    String da= "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) 
    {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     da.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     da.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
    Serial.println();
    Serial.print("Message : ");
    da.toUpperCase();
    if (da.substring(1) == "53 6C D0 0B") // Make sure you change this with your own UID number
    {
    Serial.println("Authorised access");
    Serial.println();
   // CLRSC();
   // print_txt("Access Granted..."); //ALLOCATED MEMORY DISALLOWS US TO USE THIS FUNCTION. 
    access = true;
    rua = 1;
    stat3 = HM1;
   }
    }
    stat3 = HM0;
    break;
    case HM1:
    
    stat3  = HM1;
    break;
    }
  switch(stat3){
    case HM0:
    break;
    case HM1:
    break;}
  return stat3;
}

enum M3_States {ZM0, ZM1, ZM2};
int M3_Tick(int stat4){
  switch(stat4){
    case ZM0:
    if(cn == 0){
    Wire.beginTransmission(MP);
    Wire.write(0x43);
    Wire.endTransmission(false);
    Wire.requestFrom(MP, 6, true);

    //X = Wire.read()<<8|Wire.read();
    Y = Wire.read()<<8|Wire.read();
   // Z = Wire.read()<<8|Wire.read();

   // X = X/131;
    Y = Y/131;
  //  Z = Z/131;

    //Serial.print("X Axis: ");
    //Serial.println(X);     
    //Serial.print("Y Axis: ");
    //Serial.println(Y);
    //Serial.print("Z Axis: ");
    //Serial.println(Z);
    }
    else if(cn > 0){
      stat4 = ZM1;}
    stat4 = ZM0;
    break;
    case ZM1:
    //Serial.println("Tinkering!! Stopping the code!!!");
    stat4  = ZM1;
    break;
    }
  switch(stat4){
    case ZM0:
    break;
    case ZM1:
    break;
    }
  return stat4;
}


void setup() {
  // put your setup code here, to run once:
  pinMode(RES, OUTPUT);
  pinMode(SCE, OUTPUT);
  pinMode(DC,  OUTPUT);
  pinMode(DIN, OUTPUT);
  pinMode(CLK, OUTPUT);

  initFunct();
 // CLRSC();
 // print_txt("Welcome to the party!");
  //delay(100);
  //writedata(0xFF);
 // print_txt(" Lol does not change lanes!");

 
  Wire.begin();
  Wire.beginTransmission(MP);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  mfrc522.PCD_Init();   // Initiate MFRC522
  
  Serial.begin(9600);
  SPI.begin();      
  mfrc522.PCD_Init();   
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  

  unsigned char i = 0;//code generator
  tasks[i].state = PM0;
  tasks[i].period = 1000;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct =  &M0_Tick;
  i++;
  /*
  tasks[i].state = GM0; //IR reader 
  tasks[i].period = 1;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct =  &M1_Tick;
  i++;
  */

  tasks[i].state = HM0; //NFC Chip Reader
  tasks[i].period = 200;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct =  &M2_Tick;
  i++;
  
  tasks[i].state = ZM0; //gyro
  tasks[i].period = 500;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct =  &M3_Tick;

  gcd_delay = 1;

}

void loop() {
  // put your main code here, to run repeatedly:
  char pp[4];

  
  if(cn > 0 && once == 0)
  {
    CLRSC();
    print_txt("SHUTTING DOWN!");
    once++;
  }
  
  else if(cnt == 9 && once == 0){
    CLRSC();
   /*
    for(int i = 0; i < 4; i++){
      print_txt(cc[i]);
    }

    strcpy(pp, noMore[cnt].c_str());
    print_txt(pp);

    
    */
   // print_txt("ADMINS will be with you shortly... ");
    cnt++;
  }
  //DID NOT WORK CORRECTLY. FAILURE IN THE CODING 

 
  unsigned char i;
  for(i = 0; i < tasksNum; i++){
    if((millis() - tasks[i].elapsedTime) >= tasks[i].period){
      tasks[i].state = tasks[i].TickFct(tasks[i].state);
      tasks[i].elapsedTime = millis(); 
    }
  }

}
