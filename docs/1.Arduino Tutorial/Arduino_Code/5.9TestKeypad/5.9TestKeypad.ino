#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

// Connect keypad ROW0, ROW1, ROW2, ROW3 to these Arduino pins:
byte rowPins[ROWS] = {2, 3, 4, 7};

// Connect keypad COL0, COL1, COL2, COL3 to these Arduino pins:
byte colPins[COLS] = {8, 12, 13, A2};

// Define the keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Create the Keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.print("Pressed key: ");
    Serial.println(key);
  }
}
