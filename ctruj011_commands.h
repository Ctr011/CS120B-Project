#ifndef COMMANDS_H
#define COMMANDS_H


enum instructions{ //from data sheet
  funct =   bit(5), 
  based = funct,
  ext   = funct | bit(0), 
  bias  = bit(4), 
  disp  = bit(3),
  nomr  = disp |  bit(2), 
  mux48 = bias | bit(1) | bit(2), 
  vop   = bit(7), 
  sety  = bit(6), 
  setx  = bit(7), 
};

/*

enum instructions{
  funct =   0b00100000, 
  based = funct,
  ext   = funct |  0b00000001,
  bias  =  0b00010000, 
  disp  = 0b00000100,
  nomr  = disp |  0b00000010,
  mux48 = bias | 0b00000010 | 0b00000100,
  vop   =  0b10000000, 
  sety  =   0b01000000 
  setx  = 0b10000000 
};

*/
#endif
