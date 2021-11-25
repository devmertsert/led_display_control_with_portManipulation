/*
           12  11  10   9   8   7
            |   |   |   |   |   |
      _________________________________
     |      _     _     _     _        | 
     |     |_|   |_|   |_|   |_|       |
     |     |_| . |_| . |_| . |_| .     |
     |_________________________________|
     
            |   |   |   |   |   |
            1   2   3   4   5   6


     Digit: 1     2     3     4
            ^     ^     ^     ^
            |     |     |     |
            |     |     |     |
      _________________________________
     |      _     _     _     _        |
     |     |_|   |_|   |_|   |_|       |
     |     |_| . |_| . |_| . |_| .     |
     |_________________________________|
*/


/*
                   A
                   ^
                   |
                 _____
                |     |
          F <-- |     | --> B
                |_____| _______> G
                |     |
          E <-- |     | --> C
                |_____|
                   |
                   |
                   v
                   
                   D     
*/


/*
 * Connections:
  ___________________________________
 | digit pins:                       |
 |   (Arduino)     (Led Display)     |
 |   ----------------------------    |
 |      11      =      6  (Digit 4)  |
 |      10      =      8  (Digit 3)  |
 |      9       =      9  (Digit 2)  |
 |      8       =      12 (Digit 1)  |
 |                                   |
 | segment pins:                     |
 |   (Arduino)    (Led Display)      |
 |   ----------------------------    |
 |      7      =       5  (G)        |
 |      6      =       10 (F)        |
 |      5      =       1  (E)        |
 |      4      =       2  (D)        |
 |      3      =       4  (C)        |
 |      2      =       7  (B)        |
 |      1      =       11 (A)        |
  __________________________________ |
*/

// !!!!!!    If you don't know that what is PortManipulation or how can you use it visit   https://www.arduino.cc/en/Reference/PortManipulation   !!!!!!

byte digits[] = {B00000001, B00000010, B00000100, B00001000};
//               Digit 1  , Digit 2  , Digit 3  , Digit 4

byte numbers[]  = {B10000000, B11110010, B01001000, B01100000, B00110010, B00100100, B00000100, B11110000, B00000000, B00100000};
//                    0          1          2          3          4          5          6          7          8          9

void setup() {
  Serial.begin(9600);
  DDRD = B11111110;
  DDRB = B00001111;
  
}

void loop() {
  wrNum(2018);
  
}


void wrNum(int number) {
  /* 
    Here, we parse the number and add a array e.g.
    number = 2018

    steps[0]  steps[1]  steps[2]  steps[3]
       2         1         0         8    
  */
  int steps[] = {-1, -1, -1, -1};
  int i = 3;
  while(number > 0) {
    steps[i] = number % 10;
    i--;
    number /= 10;
  }

  /*
    for the numbers that we got it, turn on leds one by one
    if steps[j] == -1 then turn off digit for step j
  */
  for(int j = 0; j < 4; j++) {
    if(steps[j] != -1) {
      PORTB = digits[j];
      PORTD = numbers[steps[j]];
      delay(5);
    }
    else {
      PORTB = B00000000;
      delay(5);
    }
  }
}
