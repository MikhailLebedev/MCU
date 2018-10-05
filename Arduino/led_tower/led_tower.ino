
#define CLOCK_1 9 // SH_CP
#define LATCH_1 8 // ST_CP
#define DATA_1 7 // DS

#define CLOCK_3 6 // SH_CP
#define LATCH_3 5 // ST_CP
#define DATA_3 4 // DS

#define CLOCK_2 3 // SH_CP
#define LATCH_2 2 // ST_CP
#define DATA_2 1 // DS


#define CLOCK 9 // SH_CP
#define LATCH 8 // ST_CP
#define DATA 7 // DS

#define LAY 11
#define COL 8
#define PINS 9

#define H HIGH
#define L LOW

char congrats[256] = "TO NASTYA FROM COLLEAGUE 08.03.2018 ;)";
//char pin[256] = "ad48183275961b45eeb9b7213bc4347f";



byte pins[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

byte state[LAY][COL];

//==================================
//============= MAIN ===============
void setup() {
  pinMode(LATCH, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  off();
  set_high();
  show(2000);
  set_low();
  off();
}

void loop() {
  up_down();
  
  strip();
  disks();
  cols();

  chess();
  flicker(500, 20);
  tetris();

  swirl();
  rain();
  one();

}

void disks() {
  for (byte i = 1; i < LAY; i += 2) {
    if ((i - 1) % 4 == 0) {
      for (byte j = 0; j < 4; ++j) {
        state[i][j] = 1;
      }
    } else {
      for (byte j = 4; j < 8; ++j) {
        state[i][j] = 1;
      }
    }
  }
  show(1000);
  for (byte k = 0; k < 100; ++k) {
    for (byte i = 1; i < LAY; i += 2) {
      if ((i - 1) % 4 == 0) {
        state[i][(0 + k) % COL] = 0;
        state[i][(4 + k) % COL] = 1;
      } else {
        state[i][(7 + COL - k % COL) % COL] = 0;
        state[i][(3 + COL - k % COL) % COL] = 1;
      }
    }
    show(100);
  }
  set_low();
}

void cols() {
  for (byte k = 0; k < 10; ++k) {
    for (byte i = 0; i < COL; ++i) {
      for (byte j = 0; j < LAY; ++j) {
        state[j][i] = 1;
      }
      show(100);
    }
    for (byte i = 0; i < COL; ++i) {
      for (byte j = 0; j < LAY; ++j) {
        state[j][i] = 0;
      }
      show(100);
    }
  }
}

void strip() {
  for (byte j = 0; j < 2; ++j) {
    state[0][j] = 1;
    show(100);
  }
  for (byte i = 1; i < LAY; ++i) {
    for (byte j = 0; j < 2; ++j) {
      state[i][(j + i * 2) % COL] = 1;
      state[i - 1][(j + i * 2) % COL] = 1;
      show(100);
    }
  }
  for (byte j = 0; j < 2; ++j) {
    state[LAY - 1][(j + LAY * 2) % COL] = 1;
    show(100);
  }

  
  for (byte j = 0; j < 2; ++j) {
    state[0][j + 4] = 1;
    show(100);
  }
  for ( byte i = 1; i < LAY; ++i) {
    for (byte j = 0; j < 2; ++j) {
      state[i][(j + i * 2 + 4) % COL] = 1;
      state[i - 1][(j + i * 2 + 4) % COL] = 1;
      show(100);
    }
  }
  for (byte j = 0; j < 2; ++j) {
    state[LAY - 1][(j + LAY * 2 + 4) % COL] = 0;
    show(100);
  }


  for (byte j = 0; j < 2; ++j) {
    state[0][j] = 0;
    show(100);
  }
  for ( byte i = 1; i < LAY; ++i) {
    for (byte j = 0; j < 2; ++j) {
      state[i][(j + i * 2) % COL] = 0;
      state[i - 1][(j + i * 2) % COL] = 0;
      show(100);
    }
  }
  for (byte j = 0; j < 2; ++j) {
    state[LAY - 1][(j + LAY * 2) % COL] = 0;
    show(100);
  }

  
  for ( byte i = 1; i < LAY; ++i) {
    for (byte j = 0; j < 2; ++j) {
      state[i][(j + i * 2 + 4) % COL] = 0;
      state[i - 1][(j + i * 2 + 4) % COL] = 0;
      show(100);
    }
  }
  for (byte j = 0; j < 2; ++j) {
    state[LAY - 1][(j + LAY * 2 + 4) % COL] = 0;
    show(100);
  }
  set_low();
}

void chess() {
  for (byte k = 0; k < 30; ++k) {
    if (k % 2 == 0) {
      for (byte i = 0; i < LAY; ++i) {
        for (byte j = 0; j < COL; ++j) {
          if (i % 4 == 0 || i % 4 == 1) {
            if (j % 4 == 0 || j % 4 == 1) {
              state[i][j] = 1;
            } else {
              state[i][j] = 0;
            }
          } else {
            if (j % 4 == 0 || j % 4 == 1) {
              state[i][j] = 0;
            } else {
              state[i][j] = 1;
            }
          }
        }
      }
    } else {
      for (byte i = 0; i < LAY; ++i) {
        for (byte j = 0; j < COL; ++j) {
          if (i % 4 == 0 || i % 4 == 1) {
            if (j % 4 == 0 || j % 4 == 1) {
              state[i][j] = 0;
            } else {
              state[i][j] = 1;
            }
          } else {
            if (j % 4 == 0 || j % 4 == 1) {
              state[i][j] = 1;
            } else {
              state[i][j] = 0;
            }
          }
        }
      }
    }
    show(500);
  }
  set_low();
  off();
}

void flicker(int n, int t) {
  byte amt = 3;
  byte arr[amt][2];
  for (byte i = 0; i < amt - 1; ++i) {
    arr[i][0] = random(0, LAY);
    arr[i][1] = random(0, COL);
    state[arr[i][0]][arr[i][1]] = 1;
    show(t);
  }
  for (int i = 2; i < n; ++i) {
    arr[i % amt][0] = random(0, LAY);
    arr[i % amt][1] = random(0, COL);
    state[arr[i % amt][0]][arr[i % amt][1]] = 1;
    show(t);
    state[arr[(i + 1) % amt][0]][arr[(i + 1) % amt][1]] = 0;
  }
  set_low();
}

void tetris(void) {
  for (byte i = 0; i < COL; ++i) {
    state[LAY - 1][i] = 1;
  }
  byte count = COL * (LAY - 1);
  byte rnd;
  byte flag;
  show(100);
  while (count > 0) {
    rnd = random(0, COL);
    if (state[LAY - 2][rnd] == 1) {
      continue;
    } else {
      --count;
      state[LAY - 2][rnd] = 1;
      show(100);
      for (byte i = LAY - 2; i > 0; --i) {
        if (state[i - 1][rnd] == 1) {
          break;
        }
        state[i][rnd] = 0;
        state[i - 1][rnd] = 1;
        show(30 + i * 10);
      }
      /*
        flag = 1;
        for (byte i = 0; i < COL; ++i) {
        if (state[0][i] == 0) {
          flag = 0;
          break;
        }
        }
        if (flag) {
        for (byte i = 0; i < LAY - 2; ++i) {
          for (byte j = 0; j < COL; ++j) {
            state[i][j] = state[i + 1][j];
          }
        }
        }
      */
    }
  }
  set_low();
  off();
}

void rain(void) {
  for (byte i = 0; i < COL; ++i) {
    state[LAY - 2][i] = 1;
  }
  byte count = COL;
  byte rnd;
  while (count > 0) {
    rnd = random(0, COL);
    if (state[LAY - 2][rnd] == 0) {
      continue;
    } else {
      --count;
      for (byte i = LAY - 2; i > 0; --i) {
        state[i][rnd] = 0;
        state[i - 1][rnd] = 1;
        show(30 + i * 10);
      }
    }
  }
  for (byte i = 0; i < COL; ++i) {
    state[0][i] = 0;
  }
}

void one(void) {
  for (byte i = 0; i < LAY; ++i) {
    for (byte j = 0; j < COL; ++j) {
      state[i][j] = 1;
      show(50);
    }
  }
  for (byte i = 0; i < LAY; ++i) {
    for (byte j = 0; j < COL; ++j) {
      state[LAY - 1 - i ][j] = 0;
      show(20);
    }
  }
  for (byte i = 0; i < LAY; ++i) {
    for (byte j = 0; j < COL; ++j) {
      state[i][j] = 1;
      show(20);
    }
  }
  for (byte i = 0; i < LAY; ++i) {
    for (byte j = 0; j < COL; ++j) {
      state[LAY - 1 - i ][j] = 0;
      show(50);
    }
  }
}

void swirl(void) {
  for (byte n = 0; n < 10; ++n) {
    for (byte i = 0; i < COL; ++i) {
      for (byte j = 0; j < LAY; ++j) {
        state[j][i] = 1;
      }
      show(150 - 10 * n);
      for (byte j = 0; j < LAY; ++j) {
        state[j][i] = 0;
      }
    }
  }
  for (byte n = 0; n < 10; ++n) {
    for (byte i = 0; i < COL; ++i) {
      for (byte j = 0; j < LAY; ++j) {
        state[j][i] = 1;
        state[j][(i + COL / 2) % COL] = 1;
      }
      show(150 - 10 * n);
      for (byte j = 0; j < LAY; ++j) {
        state[j][i] = 0;
        state[j][(i + COL / 2) % COL] = 0;
      }
    }
  }
  set_high();
  show(2000);
  set_low();
}

void up_down(void) {
  for (byte n = 0; n < 10; ++n) {
    for (byte i = 0; i < LAY; ++i) {
      for (byte j = 0; j < COL; ++j) {
        state[i][j] = 1;
      }
      show(70);
      for (byte j = 0; j < COL; ++j) {
        state[i][j] = 0;
      }
    }

    for (byte i = 0; i < LAY; ++i) {
      for (byte j = 0; j < COL; ++j) {
        state[LAY - 1 - i ][j] = 1;
      }
      show(70);
      for (byte j = 0; j < COL; ++j) {
        state[LAY - 1 - i][j] = 0;
      }
    }
  }



  for (byte n = 0; n < 10; ++n) {

    for (byte i = 0; i < LAY; ++i) {
      for (byte j = 0; j < COL; ++j) {
        state[i][j] = 1;
      }
      show(70);
    }

    for (byte i = 0; i < LAY; ++i) {
      for (byte j = 0; j < COL; ++j) {
        state[i][j] = 0;
      }
      show(70);
    }

    for (byte i = 0; i < LAY; ++i) {
      for (byte j = 0; j < COL; ++j) {
        state[LAY - 1 - i][j] = 1;
      }
      show(70);
    }
    for (byte i = 0; i < LAY; ++i) {
      for (byte j = 0; j < COL; ++j) {
        state[LAY - 1 - i][j] = 0;
      }
      show(70);
    }
  }
}
//============ END MAIN ============
//==================================
//======== SPECIAL FUNCTIONS =======
void off(void) {
  byte reg = 0x00;
  digitalWrite(LATCH, L);
  shiftOut(DATA, CLOCK, MSBFIRST, reg);
  shiftOut(DATA, CLOCK, MSBFIRST, reg);
  shiftOut(DATA, CLOCK, MSBFIRST, reg);
  digitalWrite(LATCH, H);
}

void on(void) {
  byte reg = 0xff;
  digitalWrite(LATCH, L);
  shiftOut(DATA, CLOCK, MSBFIRST, reg);
  shiftOut(DATA, CLOCK, MSBFIRST, reg);
  shiftOut(DATA, CLOCK, MSBFIRST, reg);
  digitalWrite(LATCH, H);
}

byte reg(byte n) {
  byte reg = -1;
  for (int k = 0; k < COL; ++k) {
    reg <<= 1;
    reg |= state[n][k];
  }
  return reg;
}

void show(unsigned long tm) {
  unsigned long start_tm = millis();
  unsigned short int reg_0 = 0;
  byte reg_1, reg_2, reg_3;
  while (millis() - start_tm < tm) {
    for (byte i = 0; i < 11; ++i) {
      reg_1 = reg(i);
      reg_0 = 0x0001;
      reg_0 <<= i;
      reg_3 = highByte(reg_0);
      reg_2 = lowByte(reg_0);

      digitalWrite(LATCH, L);
      shiftOut(DATA, CLOCK, MSBFIRST, reg_2);
      shiftOut(DATA, CLOCK, MSBFIRST, reg_3);
      shiftOut(DATA, CLOCK, MSBFIRST, reg_1);
      digitalWrite(LATCH, H);
      delay(1);
    }
  }
}

void set_low() {
  for (byte i = 0; i < LAY; ++i) {
    for (byte j = 0; j < COL; ++j) {
      state[i][j] = 0;
    }
  }
}

void set_high() {
  for (byte i = 0; i < LAY; ++i) {
    for (byte j = 0; j < COL; ++j) {
      state[i][j] = 1;
    }
  }
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
/*
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
*/
