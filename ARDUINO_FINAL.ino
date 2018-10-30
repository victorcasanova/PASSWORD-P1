#include <Keypad.h>

char* secretCode = "7516";
int pos = 0;
int right = 0;

const byte rows = 4;
const byte cols = 3;
char keys[rows][cols] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[rows] = {5, 6, 7, 8};
byte colPins[cols] = {2, 3, 4};

Keypad keypad = Keypad(makeKeymap(keys),
                       rowPins, colPins,
                       rows, cols);


int bluePin = 12;
int redPin = 11;
int greenPin = 10;


void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  setLocked(0);
  Serial.begin(9600);
}

void loop()
{
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
    if (key == '*' || key == '#') {
      pos = 0;
      right = 0;
      setLocked(0);
      Serial.println("Door locked");
    }else if (key == secretCode[pos]) {
      pos++;
      right++;
    } else {
      pos++;
    }

    if (pos == 4) {
      if (right == pos) {
        setLocked(2);
      } else {
        setLocked(1);
      }
    }
    delay(50);
  }
  Serial.println(pos);
}

void setLocked(int state) {
  if (state == 0) {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
    Serial.println("Door waiting");
  } else if (state == 1) {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    Serial.println("Door alarm");
  }  else {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
    Serial.println("Door opened!");
  }
}
