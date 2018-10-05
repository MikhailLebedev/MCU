byte arr[6] = {40, 80, 40, 80, 40, 240};

byte arr1[26] = {1, 0, 0, 1, 0, 0, 1,   0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0};
byte arr2[26] = {0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0,   1, 0, 0, 1, 0, 0, 1,   0, 0, 0, 0, 0, 0};
byte arr3[26] = {0, 0, 0, 0, 0, 0, 0,   0, 0, 1, 1, 0, 0,   0, 0, 0, 0, 0, 0, 0,   0, 0, 1, 1, 0, 0};

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  for (byte i = 0; i < 26; ++i) {
    digitalWrite(2, arr1[i]);
    digitalWrite(3, arr2[i]);
    digitalWrite(4, arr3[i]);
    delay(40);
  }
}
