#include <Keypad.h>
#include <Servo.h>

// Constants
const byte ROWS = 4;
const byte COLS = 4;

const int servoPin = 10;
const int buzzerPin = 11;
const int greenLed = 52;
const int redLed = 53;

const int shortBeepDuration = 200;
const int longBeepDuration = 500;

// Password setup
const char password[] = "1234"; // 4 digits + null terminator
char enteredPassword[5] = "";
byte enteredLength = 0;

// Keypad setup
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Servo object
Servo servoLock;

void setup() {
  Serial.begin(9600);
  servoLock.attach(servoPin);
  setupPins();
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    delay(50); // Simple debounce
    if (key == keypad.getKey()) { // Confirm stable press
      handleKeyPress(key);
    }
  }
}

// ---- Helper Functions ----

void setupPins() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
}

void handleKeyPress(char key) {
  if (key >= '0' && key <= '9') { // Only accept numbers
    if (enteredLength < 4) {
      enteredPassword[enteredLength++] = key;
      enteredPassword[enteredLength] = '\0'; // Null terminate
      Serial.println(enteredPassword);
    }
  }
  else if (key == '#') {
    verifyPassword();
  }
  else if (key == '*') {
    resetEnteredPassword();
  }
}

void verifyPassword() {
  Serial.println("Password entered.");
  if (strcmp(enteredPassword, password) == 0) {
    handleCorrectPassword();
  } else {
    handleWrongPassword();
  }
}

void handleCorrectPassword() {
  Serial.println("Access granted!");
  digitalWrite(greenLed, HIGH);
  buzz(shortBeepDuration);
  buzz(shortBeepDuration);
  digitalWrite(greenLed, LOW);
  resetEnteredPassword();
}

void handleWrongPassword() {
  Serial.println("Access denied!");
  digitalWrite(redLed, HIGH);
  buzz(longBeepDuration);
  digitalWrite(redLed, LOW);
  resetEnteredPassword();
}

void resetEnteredPassword() {
  enteredLength = 0;
  enteredPassword[0] = '\0';
  Serial.println("Password cleared.");
}

void buzz(int duration) {
  digitalWrite(buzzerPin, HIGH);
  delay(duration);
  digitalWrite(buzzerPin, LOW);
  delay(duration);
}
