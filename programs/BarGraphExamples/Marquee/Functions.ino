void funcUp(byte &pos) {
  funcCycle(++pos);
}

void funcDown(byte &pos) {
  funcCycle(--pos);
}

void funcUpDown(byte &pos) {
  static byte d = 1;
  pos += d;
  d =  (pos >= 11) ? -1 : ((pos <= 2) ? 1 : d);
}

inline void funcCycle(byte &pos) {
  pos =  (pos > 11) ? 2 : ((pos < 2) ? 11 : pos);
}


