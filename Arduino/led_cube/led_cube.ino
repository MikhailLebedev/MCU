#define LATCH 7 // ST_CP
#define CLOCK 8 // SH_CP
#define DATA 9 // DS
#define SIZE 4
#define H HIGH
#define L LOW

int layer[SIZE] = {2, 3, 4, 5};
byte state[SIZE][SIZE][SIZE];
//==================================
//============= MAIN ===============
void setup() {
  //устанавливаем режим OUTPUT
  pinMode(LATCH, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  for (int i = 0; i < 4; ++i) {
    pinMode(layer[i], OUTPUT);
  }
  layers_off();
  cols_off();
  test();
}

void loop() {
  plane(5);
  rain();
  flicker(300, 20);
}
//============ END MAIN ============
//==================================
//======== SPECIAL FUNCTIONS =======
void layers_off(void) {
  for (byte i = 0; i < 4; ++i) {
    digitalWrite(layer[i], L);
  }
}

void layers_on(void) {
  for (byte i = 0; i < 4; ++i) {
    digitalWrite(layer[i], H);
  }
}

void cols_off(void) {
  digitalWrite(LATCH, L);
  unsigned short int reg = 0;
  byte high = highByte(reg);
  byte low = lowByte(reg);
  shiftOut(DATA, CLOCK, MSBFIRST, high);
  shiftOut(DATA, CLOCK, MSBFIRST, low);
  digitalWrite(LATCH, H);
}

void cols_on(void) {
  digitalWrite(LATCH, L);
  unsigned short int reg = 0xffff;
  byte high = highByte(reg);
  byte low = lowByte(reg);
  shiftOut(DATA, CLOCK, MSBFIRST, high);
  shiftOut(DATA, CLOCK, MSBFIRST, low);
  digitalWrite(LATCH, H);
}

void cols_set(unsigned short int reg) {
  digitalWrite(LATCH, L);
  byte high = highByte(reg);
  byte low = lowByte(reg);
  shiftOut(DATA, CLOCK, MSBFIRST, high);
  shiftOut(DATA, CLOCK, MSBFIRST, low);
  digitalWrite(LATCH, H);
}

unsigned short int reg(byte n) {
  unsigned short int reg = 0;
  for (byte i = 0; i < SIZE; ++i) {
    for (byte j = 0; j < SIZE; ++j) {
      reg <<= 1;
      reg |= state[n][i][j];
    }
  }
  return reg;
}

void show(unsigned long tm) {
  unsigned long start_tm = millis();
  while (millis() - start_tm < tm) {
    for (byte i = 0; i < SIZE; ++i) {
      cols_set(reg(i));
      //cols_on();
      digitalWrite(layer[i], H);
      delay(3);
      digitalWrite(layer[i], L);
    }
  }
}
void set_low() {
  for (byte i = 0; i < SIZE; ++i) {
    for (byte j = 0; j < SIZE; ++j) {
      for (byte k = 0; k < SIZE; ++k) {
        state[i][j][k] = 0;
      }
    }
  }
}


void layer_on(byte n) {
  for (byte i = 0; i < SIZE; ++i) {
    for (byte j = 0; j < SIZE; ++j) {
      state[n][i][j] = 1;
    }
  }
}

void layer_off(byte n) {
  for (byte i = 0; i < SIZE; ++i) {
    for (byte j = 0; j < SIZE; ++j) {
      state[n][i][j] = 0;
    }
  }
}




void x_on(byte n) {
  for (byte i = 0; i < SIZE; ++i) {
    for (byte j = 0; j < SIZE; ++j) {
      state[i][n][j] = 1;
    }
  }
}

void x_off(byte n) {
  for (byte i = 0; i < SIZE; ++i) {
    for (byte j = 0; j < SIZE; ++j) {
      state[i][n][j] = 0;
    }
  }
}




void y_on(byte n) {
  for (byte i = 0; i < SIZE; ++i) {
    for (byte j = 0; j < SIZE; ++j) {
      state[j][i][n] = 1;
    }
  }
}

void y_off(byte n) {
  for (byte i = 0; i < SIZE; ++i) {
    for (byte j = 0; j < SIZE; ++j) {
      state[j][i][n] = 0;
    }
  }
}
//===== END SPECIAL FUNCTIONS =======
//===================================
//=========== MODS ==================
void flicker(int n, int t) {
  byte x, y, z;
  byte amt = 3;
  byte arr[amt][3];
  for (byte i = 0; i < amt - 1; ++i) {
    arr[i][0] = random(0, SIZE);
    arr[i][1] = random(0, SIZE);
    arr[i][2] = random(0, SIZE);
    state[arr[i][0]][arr[i][1]][arr[i][2]] = 1;
    show(t);
  }
  for (int i = 2; i < n; ++i) {
    arr[i % amt][0] = random(0, SIZE);
    arr[i % amt][1] = random(0, SIZE);
    arr[i % amt][2] = random(0, SIZE);
    state[arr[i % amt][0]][arr[i % amt][1]][arr[i % amt][2]] = 1;
    show(t);
    state[arr[(i + 1) % amt][0]][arr[(i + 1) % amt][1]][arr[(i + 1) % amt][2]] = 0;
  }
  set_low();
}




void rain() {
  for (byte i = 0; i < SIZE; ++i) {
    for (byte j = 0; j < SIZE; ++j) {
      state[SIZE - 1][i][j] = 1;
    }
  }
  show(1500);
  byte count = SIZE * SIZE;
  byte rnd;
  byte x, y;
  while (count > 0) {
    rnd = random(0, SIZE * SIZE);
    x = rnd / SIZE;
    y = rnd % SIZE;
    if (state[SIZE - 1][x][y] == 0) {
      continue;
    } else {
      --count;
      for (byte i = SIZE - 1; i > 0; --i) {
        state[i][x][y] = 0;
        state[i - 1][x][y] = 1;
        show(30 + i * 10);
      }
    }
  }
  for (byte i = 0; i < SIZE; ++i) {
    for (byte j = 0; j < SIZE; ++j) {
      state[0][i][j] = 0;
    }
  }
}



void test(void) {
  cols_on();
  layers_on();
  delay(5000);
  layers_off();
  cols_off();
}


void plane(byte n) {
  for (byte k = 0; k < n; ++k) {
    for (int i = 3; i >= 0; --i) {
      layer_on(i);
      show(70);
      layer_off(i);
    }
    for (byte i = 0; i < 4; ++i) {
      layer_on(i);
      show(70);
      layer_off(i);
    }

    for (int i = 3; i >= 0; --i) {
      x_on(i);
      show(70);
      x_off(i);
    }
    for (byte i = 0; i < 4; ++i) {
      x_on(i);
      show(70);
      x_off(i);
    }

    for (int i = 3; i >= 0; --i) {
      y_on(i);
      show(70);
      y_off(i);
    }
    for (byte i = 0; i < 4; ++i) {
      y_on(i);
      show(70);
      y_off(i);
    }
  }
}


void stamp(byte n) {
  for (byte k = 0; k < n; ++k) {
    delay(50);
    layer_on(3);
    show(50);
    for (int i = 2; i >= 0; --i) {
      layer_on(i);
      show(50);
      layer_off(i + 1);
      show(50);
    }
    layer_off(0);
    delay(50);
    layer_on(0);
    show(50);
    for (byte i = 1; i < 4; ++i) {
      layer_on(i);
      show(50);
      layer_off(i - 1);
      show(50);
    }
    layer_off(3);
  }
}
//========= END MODS =================
