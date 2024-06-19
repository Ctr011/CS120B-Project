/*
 * RNG IMPLEMENTATION!!!
 */

#include <Arduino_AVRSTL.h>
#include <String>
#include <stdio.h>
using namespace std;

String code;
String A[10] = {"0000", "1111", "2222", "3333", "4444", "5555", "6666", "7777", "8888", "9999"};
int ct = 0;
String noMore[10]; 
unsigned long cc[4]; 
int xx = 0;
unsigned long seed = 926432123;
unsigned long  a;
unsigned long  m;
unsigned long  q;
unsigned long r;
unsigned long hi;
unsigned long lo;
unsigned long test;
unsigned long g;

void noLonger(String c, int co){
  if(co < 100){
  noMore[co] = c;}
}

bool check(){
  for(int i = 0; i < 10; i++){
    if(noMore[i] == code || A[i] == code){
      return false; 
    }}
  
  return true;
  }

 unsigned long rnd(unsigned long s){
  seed = s;

  a = 16807;
  m = 2147483647;
  q  = m / a;
  r  = m % a;
  hi = seed / q;
  lo = seed - q * hi;
  return test = a*lo - r*hi;
  }

/*
 void hmm(int n){
  int g; 
  Serial.print("1");
  for(int i = 0; i < 4; i++){
    g = rnd(a * i + m * (i+1) + (seed*n+1));
    if(g > 0){
      seed = g;
    }
    else { seed = g + m;}
    cc.at(i) = (seed % 10);
  }

  }
*/

void coin(){
  for(int i = 0; i < 4; i++){
    if(i == 0) {code = String(cc[i]);}
    else{code += String(cc[i]);}
  }
  //Serial.print("Da Code: ");
  if(xx == 8){
  Serial.println(code); }
  Serial.println(xx);
  xx++;
}
  
