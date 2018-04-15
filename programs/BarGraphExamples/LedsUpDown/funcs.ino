int funcUp(int pos){
  pos+= 1;
  return funcCycle(pos);
}

int funcDown(int pos){
  pos+= -1;
  return funcCycle(pos);
}

int funcUpDown(int pos){
  static short d = 1;
  pos += d;
  if(pos >= 11) d = -1;
  if(pos <= 2) d = 1;
  return pos;
}

inline int funcCycle(int pos){
  if(pos > 11) pos = 2;
  if(pos < 2) pos = 12;
  return pos;
}

