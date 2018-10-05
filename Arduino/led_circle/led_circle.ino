#define LATCH 13 // ST_CP
#define CLOCK 12 // SH_CP
#define DATA 11 // DS

#define H HIGH
#define L LOW

#define SIZE 4
#define RAY 12
#define LAY 2
#define CIR 4

#define LEN 8

int layer[] = {2, 3, 4, 5, 6, 7, 8, 9};
byte state[LAY][CIR][RAY];
//byte state[LAY][RAY][LEV];
//==================================
//============= MAIN ===============
void setup() {
  //устанавливаем режим OUTPUT
  pinMode(LATCH, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  for (int i = 0; i < LEN; ++i) {
    pinMode(layer[i], OUTPUT);
  }
  layers_off();
  cols_off();
  test(5000);
  //show(2000);
}

void loop() {
  flicker(300, 20);
  propeller(5);
  strobe();
  
  rain();
  center();
  abcd(5); 

  load();
  spiral();
  butterfly(5);
 
  load2(5);
}
//============ END MAIN ============
//==================================
//======== SPECIAL FUNCTIONS =======
void layers_off(void) {
  for (byte i = 0; i < LEN; ++i) {
    digitalWrite(layer[i], L);
  }
}

void layers_on(void) {
  for (byte i = 0; i < LEN; ++i) {
    digitalWrite(layer[i], H);
  }
}

void cols_off(void) {
  digitalWrite(LATCH, L);
  unsigned short int reg = 0xf000;
  byte high = highByte(reg);
  byte low = lowByte(reg);
  shiftOut(DATA, CLOCK, MSBFIRST, high);
  shiftOut(DATA, CLOCK, MSBFIRST, low);
  digitalWrite(LATCH, H);
}

void cols_on(void) {
  digitalWrite(LATCH, L);
  unsigned short int reg = 0x0fff;
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
  byte i = n / CIR;
  byte j = n % CIR;
  for (int k = RAY - 1; k >= 0; --k) {
    reg <<= 1;
    reg |= state[i][j][k];
  }
  return reg;
}

void show(unsigned long tm) {
  unsigned long start_tm = millis();
  while (millis() - start_tm < tm) {
    for (byte i = 0; i < LEN; ++i) {
      cols_set(reg(i));
      //cols_set(0x00f0);
      digitalWrite(layer[i], H);
      delay(2);
      digitalWrite(layer[i], L);
    }
  }
}
void set_low() {
  for (byte i = 0; i < LAY; ++i) {
    for (byte j = 0; j < CIR; ++j) {
      for (byte k = 0; k < RAY; ++k) {
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

void test(int t) {
  cols_on();
  layers_on();
  delay(t);
  layers_off();
  cols_off();
}
//===== END SPECIAL FUNCTIONS =======
//===================================
//=========== MODS ==================
/*
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
*/
//========= END MODS =================

//========= CIRCLE ===================
void load3(void) {
  for (byte i = 0; i < LAY; ++i) {
    for (byte k = 0; k < RAY; ++k) {
      for (byte j = 0; j < CIR; ++j) {
        state[i][j][k] = 1;
      }
      show(100);
      for (byte j = 0; j < CIR; ++j) {
        state[i][j][k] = 0;
      }
    }
  }
}

void load(void) {
  for (byte k = 0; k < RAY; ++k) {
    for (byte j = 0; j < CIR; ++j) {
      state[0][j][k] = 1;
      state[1][j][RAY - k - 1] = 1;
    }
    show(100);
  }
  for (byte k = 0; k < RAY; ++k) {
    for (byte j = 0; j < CIR; ++j) {
      state[1][j][k] = 0;
      state[0][j][RAY - k - 1] = 0;
    }
    show(100);
  }
}


void load2(byte n) {
  for (byte z = 0; z < n; ++z) {
    for (byte k = 0; k < RAY; ++k) {
      for (byte j = 0; j < CIR; ++j) {
        state[z % 2][j][k] = 1;
        state[(z + 1) % 2][j][k] = 0;
      }
      show(100);
    }
  }

  for (byte k = 0; k < RAY; ++k) {
    for (byte j = 0; j < CIR; ++j) {
      state[(n + 1) % 2][j][k] = 0;
    }
    show(100);
  }
}

void butterfly(byte n) {
  byte k, i;
  k = 2;
  i = 0;
  for (byte j = 0; j < CIR; ++j) {
    state[i][j][k] = 1;
  }
  k = 9;
  i = 0;
  for (byte j = 0; j < CIR; ++j) {
    state[i][j][k] = 1;
  }
  k = 3;
  i = 1;
  for (byte j = 0; j < CIR; ++j) {
    state[i][j][k] = 1;
  }
  k = 8;
  i = 1;
  for (byte j = 0; j < CIR; ++j) {
    state[i][j][k] = 1;
  }
  show(150);
  for (byte z = 0; z < n; ++z) {
    k = 1;
    i = 0;
    for (byte j = 0; j < CIR; ++j) {
      state[i][j][k] = 1;
    }
    k = 10;
    i = 0;
    for (byte j = 0; j < CIR; ++j) {
      state[i][j][k] = 1;
    }
    k = 4;
    i = 1;
    for (byte j = 0; j < CIR; ++j) {
      state[i][j][k] = 1;
    }
    k = 7;
    i = 1;
    for (byte j = 0; j < CIR; ++j) {
      state[i][j][k] = 1;
    }
    show(150);
    k = 0;
    i = 0;
    for (byte j = 0; j < CIR; ++j) {
      state[i][j][k] = 1;
    }
    k = 11;
    i = 0;
    for (byte j = 0; j < CIR; ++j) {
      state[i][j][k] = 1;
    }
    k = 5;
    i = 1;
    for (byte j = 0; j < CIR; ++j) {
      state[i][j][k] = 1;
    }
    k = 6;
    i = 1;
    for (byte j = 0; j < CIR; ++j) {
      state[i][j][k] = 1;
    }
    show(150);
    k = 0;
    i = 0;
    for (byte j = 0; j < CIR; ++j) {
      state[i][j][k] = 0;
    }
    k = 11;
    i = 0;
    for (byte j = 0; j < CIR; ++j) {
      state[i][j][k] = 0;
    }
    k = 5;
    i = 1;
    for (byte j = 0; j < CIR; ++j) {
      state[i][j][k] = 0;
    }
    k = 6;
    i = 1;
    for (byte j = 0; j < CIR; ++j) {
      state[i][j][k] = 0;
    }
    show(150);
    k = 1;
    i = 0;
    for (byte j = 0; j < CIR; ++j) {
      state[i][j][k] = 0;
    }
    k = 10;
    i = 0;
    for (byte j = 0; j < CIR; ++j) {
      state[i][j][k] = 0;
    }
    k = 4;
    i = 1;
    for (byte j = 0; j < CIR; ++j) {
      state[i][j][k] = 0;
    }
    k = 7;
    i = 1;
    for (byte j = 0; j < CIR; ++j) {
      state[i][j][k] = 0;
    }
    show(150);
  }
  k = 2;
  i = 0;
  for (byte j = 0; j < CIR; ++j) {
    state[i][j][k] = 0;
  }
  k = 9;
  i = 0;
  for (byte j = 0; j < CIR; ++j) {
    state[i][j][k] = 0;
  }
  k = 3;
  i = 1;
  for (byte j = 0; j < CIR; ++j) {
    state[i][j][k] = 0;
  }
  k = 8;
  i = 1;
  for (byte j = 0; j < CIR; ++j) {
    state[i][j][k] = 0;
  }
}

void spiral(void) {
  byte i;
  i = 0;
  for (int j = CIR - 1; j >= 0; --j) {
    for (int k = RAY - 1; k >= 0; --k) {
      state[i][j][k] = 1;
      show(50);
    }
  }
  for (int j = CIR - 1; j >= 0; --j) {
    for (int k = RAY - 1; k >= 0; --k) {
      state[i][j][k] = 0;
      show(50);
    }
  }
  i = 1;
  for (byte j = 0; j < CIR; ++j) {
    for (int k = RAY - 1; k >= 0; --k) {
      state[i][j][k] = 1;
      show(50);
    }
  }
  for (byte j = 0; j < CIR; ++j) {
    for (int k = RAY - 1; k >= 0; --k) {
      state[i][j][k] = 0;
      show(50);
    }
  }
}

void abcd(byte n) {
  for (byte z = 0; z < n; ++z) {
    for (byte k = 0; k < RAY; ++k) {
      state[0][(k + 0) % RAY][0] = 1;
      state[0][(k + 1) % RAY][11] = 1;
      state[0][(k + 1) % RAY][10] = 1;
      state[0][(k + 2) % RAY][10] = 1;
      state[0][(k + 3) % RAY][10] = 1;

      state[0][(k + 0) % RAY][3] = 1;
      state[0][(k + 1) % RAY][2] = 1;
      state[0][(k + 1) % RAY][1] = 1;
      state[0][(k + 2) % RAY][1] = 1;
      state[0][(k + 3) % RAY][1] = 1;

      state[0][(k + 0) % RAY][6] = 1;
      state[0][(k + 1) % RAY][5] = 1;
      state[0][(k + 1) % RAY][4] = 1;
      state[0][(k + 2) % RAY][4] = 1;
      state[0][(k + 3) % RAY][4] = 1;

      state[0][(k + 0) % RAY][9] = 1;
      state[0][(k + 1) % RAY][8] = 1;
      state[0][(k + 1) % RAY][7] = 1;
      state[0][(k + 2) % RAY][7] = 1;
      state[0][(k + 3) % RAY][7] = 1;

      show(50);

      state[0][(k + 0) % RAY][0] = 0;
      state[0][(k + 1) % RAY][11] = 0;
      state[0][(k + 1) % RAY][10] = 0;
      state[0][(k + 2) % RAY][10] = 0;
      state[0][(k + 3) % RAY][10] = 0;

      state[0][(k + 0) % RAY][3] = 0;
      state[0][(k + 1) % RAY][2] = 0;
      state[0][(k + 1) % RAY][1] = 0;
      state[0][(k + 2) % RAY][1] = 0;
      state[0][(k + 3) % RAY][1] = 0;

      state[0][(k + 0) % RAY][6] = 0;
      state[0][(k + 1) % RAY][5] = 0;
      state[0][(k + 1) % RAY][4] = 0;
      state[0][(k + 2) % RAY][4] = 0;
      state[0][(k + 3) % RAY][4] = 0;

      state[0][(k + 0) % RAY][9] = 0;
      state[0][(k + 1) % RAY][8] = 0;
      state[0][(k + 1) % RAY][7] = 0;
      state[0][(k + 2) % RAY][7] = 0;
      state[0][(k + 3) % RAY][7] = 0;
    }
  }
}

void svas(byte n) {
  for (byte z = 0; z < n; ++z) {
    for (byte k = 0; k < RAY; ++k) {
      state[0][0][(0  + k) % RAY] = 1;
      state[0][1][(11 + k) % RAY] = 1;
      state[0][1][(10 + k) % RAY] = 1;
      state[0][2][(10 + k) % RAY] = 1;
      state[0][3][(10 + k) % RAY] = 1;

      state[0][0][(3 + k) % RAY] = 1;
      state[0][1][(2 + k) % RAY] = 1;
      state[0][1][(1 + k) % RAY] = 1;
      state[0][2][(1 + k) % RAY] = 1;
      state[0][3][(1 + k) % RAY] = 1;

      state[0][0][(6 + k) % RAY] = 1;
      state[0][1][(5 + k) % RAY] = 1;
      state[0][1][(4 + k) % RAY] = 1;
      state[0][2][(4 + k) % RAY] = 1;
      state[0][3][(4 + k) % RAY] = 1;

      state[0][0][(9 + k) % RAY] = 1;
      state[0][1][(8 + k) % RAY] = 1;
      state[0][1][(7 + k) % RAY] = 1;
      state[0][2][(7 + k) % RAY] = 1;
      state[0][3][(7 + k) % RAY] = 1;

      show(200);

      state[0][0][(0  + k) % RAY] = 0;
      state[0][1][(11 + k) % RAY] = 0;
      state[0][1][(10 + k) % RAY] = 0;
      state[0][2][(10 + k) % RAY] = 0;
      state[0][3][(10 + k) % RAY] = 0;

      state[0][0][(3 + k) % RAY] = 0;
      state[0][1][(2 + k) % RAY] = 0;
      state[0][1][(1 + k) % RAY] = 0;
      state[0][2][(1 + k) % RAY] = 0;
      state[0][3][(1 + k) % RAY] = 0;

      state[0][0][(6 + k) % RAY] = 0;
      state[0][1][(5 + k) % RAY] = 0;
      state[0][1][(4 + k) % RAY] = 0;
      state[0][2][(4 + k) % RAY] = 0;
      state[0][3][(4 + k) % RAY] = 0;

      state[0][0][(9 + k) % RAY] = 0;
      state[0][1][(8 + k) % RAY] = 0;
      state[0][1][(7 + k) % RAY] = 0;
      state[0][2][(7 + k) % RAY] = 0;
      state[0][3][(7 + k) % RAY] = 0;
    }
  }
}

void heart(void) {

}

void rain() {
  for (byte i = 0; i < LAY; ++i) {
    for (byte j = 0; j < RAY; ++j) {
      state[i][3][j] = 1;
    }
  }
  show(1500);
  byte count = LAY * RAY;
  byte rnd;
  byte x, y;
  while (count > 0) {
    rnd = random(0, LAY * RAY);
    x = rnd / RAY;
    y = rnd % RAY;
    if (state[x][3][y] == 0) {
      continue;
    } else {
      --count;
      for (byte i = CIR - 1; i > 0; --i) {
        state[x][i][y] = 0;
        state[x][i - 1][y] = 1;
        show(40 + i * 10);
      }
    }
  }
  show(1500);
  for (byte i = 0; i < LAY; ++i) {
    for (byte j = 0; j < RAY; ++j) {
      state[i][0][j] = 0;
    }
  }
}

void center(void) {
  for (byte i = 0; i < LAY; ++i) {
    for (byte j = 0; j < RAY; ++j) {
      state[i][0][j] = 1;
    }
  }

  for (byte k = 0; k < CIR - 1; ++k) {
    for (byte i = 0; i < LAY; ++i) {
      for (byte j = 0; j < RAY; ++j) {
        state[i][k][j] = 0;
        state[i][k + 1][j] = 1;
      }
    }
    show(100);
  }
  for (byte i = 0; i < LAY; ++i) {
    for (byte j = 0; j < RAY; ++j) {
      state[i][3][j] = 0;
    }
  }
}

void strobe(void) {
  for (int i = CIR - 1; i >= 0; --i) {
    for (byte j = 0; j < RAY; ++j) {
      state[0][i][j] = 1;
      state[1][i][j] = 1;
    }
    for (byte k = 0; k < CIR - i + 5; ++k) {
      show(200 - (CIR - i - 1) * 50);
      delay(200 - (CIR - i - 1) * 50);
    }
  }
  for (int i = CIR; i >= 0; --i) {
    for (byte j = 0; j < RAY; ++j) {
      state[0][i][j] = 0;
      state[1][i][j] = 0;
    }
  }
}
void propeller(byte n) {
  for (byte i = 0; i < CIR; ++i) {
    for (byte j = 0; j < 3; ++j) {
      state[0][i][j] = 1;
    }
    for (byte j = 6; j < 9; ++j) {
      state[0][i][j] = 1;
    }
  }
  show(150);
  for (byte k = 0; k < n * 6; ++k) {
    for (byte i = 0; i < CIR; ++i) {
      if ((k % 6) >= 0 && (k % 6) < 3) {
        state[1][i][(k + 3) % RAY] = 1;
        state[1][i][(k + 9) % RAY] = 1;
        state[0][i][(k + 0) % RAY] = 0;
        state[0][i][(k + 6) % RAY] = 0;
      } else {
        state[0][i][(k + 3) % RAY] = 1;
        state[0][i][(k + 9) % RAY] = 1;
        state[1][i][(k + 0) % RAY] = 0;
        state[1][i][(k + 6) % RAY] = 0;
      }
    }
    show(150);
  }
  for (int i = CIR; i >= 0; --i) {
    for (byte j = 0; j < RAY; ++j) {
      state[0][i][j] = 0;
      state[1][i][j] = 0;
    }
  }
}

void flicker(int n, int t) {
  byte x, y, z;
  byte amt = 3;
  byte arr[amt][3];
  for (byte i = 0; i < amt - 1; ++i) {
    arr[i][0] = random(0, LAY);
    arr[i][1] = random(0, CIR);
    arr[i][2] = random(0, RAY);
    state[arr[i][0]][arr[i][1]][arr[i][2]] = 1;
    show(t);
  }
  for (int i = 2; i < n; ++i) {
    arr[i % amt][0] = random(0, LAY);
    arr[i % amt][1] = random(0, CIR);
    arr[i % amt][2] = random(0, RAY);
    state[arr[i % amt][0]][arr[i % amt][1]][arr[i % amt][2]] = 1;
    show(t);
    state[arr[(i + 1) % amt][0]][arr[(i + 1) % amt][1]][arr[(i + 1) % amt][2]] = 0;
  }
  set_low();
}

