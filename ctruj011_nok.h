#include "fonts.h"
#include "commands.h"


/*
 * NOKIA 5110 IMPLEMENTATION
 */

 #define RES 6 
 #define SCE 7
 #define DC  5
 #define DIN 4
 #define CLK 8

void shift(uint8_t ddin, uint8_t dclk, uint8_t n) //modified from Wire library, TFT && Nokia LCD only uses MSBFIRST
{
      uint8_t i;

      for (i = 0; i < 8; i++)  {    
            digitalWrite(ddin, !!(n & (1 << (7 - i))));
                  
            digitalWrite(dclk, HIGH);
            digitalWrite(dclk, LOW);            
      }
}

void writecmd(uint8_t m){
  digitalWrite(DC,   LOW);
  digitalWrite(SCE,  LOW);
  shift(DIN, CLK, m);
  digitalWrite(SCE, HIGH);
}

void writedata(uint8_t d){
  digitalWrite(DC,   HIGH);
  digitalWrite(SCE, LOW);
  shift(DIN, CLK, d);
  digitalWrite(SCE, HIGH);
}


void setAdd(uint8_t n, uint8_t x){
  writecmd(setx | n);
  writecmd(sety | x);
}


void print_txt(char *s){ //making the characters 8 columns wide, we have 128 columns 
  char c;
  setAdd(1, 2); //Moving the displayed values a few rows down to not mess anything up.
  while(*s != '\0'){
    c = *s;
    for(int f = 0; f < 5; f++){
        writedata(NL[c - 0x20][f]);
    }
    writedata(0x00);
    *s++;
  }
}

 void HardWareRest(){
  digitalWrite(RES, LOW);
  delayMicroseconds(1);
  digitalWrite(RES, HIGH);
 }

void CLRSC(){
  writecmd(setx | 0x00);
  writecmd(sety | 0x00);
  int i;
  for(i = 0; i < 504; i++)
  {
    writedata(0x00);
  }
}
void initFunct(){
  digitalWrite(RES, HIGH);
  digitalWrite(SCE, HIGH);
  
  HardWareRest();
  
  writecmd(ext);
  writecmd(mux48);
  writecmd(vop | 0x25); 
  writecmd(based);
  writecmd(nomr);
}
