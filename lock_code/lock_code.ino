#include <Keypad.h>
#include <Servo.h> 

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

int servoPin = 10;
Servo Servo1; 
String password = "1234";
String enteredPassword;

int buzzerPin = 11;

int greenLed = 52;
int redLed = 53;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//Create an object of keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  Servo1.attach(servoPin);
  pinMode(buzzerPin, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
}
  
void loop(){
  char key = keypad.getKey();// Read the key
  


  // Print if key pressed
  if ((key) && enteredPassword.length() < 4 && (key != '#') && (key != '*')) {
    enteredPassword += key;
    Serial.println(enteredPassword);
  }
  


  // Check password correctness
  if (key == '#') {
    Serial.println("Pass entered");

    if (enteredPassword == password) {
      Serial.println("Lock opened!");
      digitalWrite(greenLed, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(200);
      digitalWrite(buzzerPin, LOW);
      delay(200);
      digitalWrite(buzzerPin, HIGH);
      delay(200);
      digitalWrite(buzzerPin, LOW);
      digitalWrite(greenLed, LOW);
      enteredPassword = "";
    }
    else {
      Serial.println("Incorrect password!");
      digitalWrite(buzzerPin, HIGH);
      digitalWrite(redLed, HIGH);
      delay(500);
      digitalWrite(buzzerPin, LOW);
      digitalWrite(redLed, LOW);
      Serial.println("Try again");
      enteredPassword = "";
    }
  }


  // Clear password
  if (key == '*') {
    enteredPassword = "";
    Serial.println("Password cleared");
  }



  // Servo1.write(0); Use later, servo is currently broken

}