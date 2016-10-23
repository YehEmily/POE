/* NAMES: Erica Lee & Emily Yeh
 * ASSIGNMENT: Lab 1
 */

/*************************************************************
  VARIABLES
**************************************************************/

const int buttonPin = 2;              // set button pin at pin 8

unsigned long lastDebounceTime = 0;   // the last time the output pin was toggled
unsigned long debounceDelay = 100;     // the debounce time; increase if the output flickers

unsigned long previousMillis = 0;
const long interval = 500;

int buttonPushCounter = 0;
int buttonState = 0;
int lastButtonState = LOW;

int val = 0;
int potPin = A0;

/*************************************************************
  SETUP
**************************************************************/

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // button pin is input
  
  attachInterrupt(digitalPinToInterrupt(buttonPin), toggle, RISING);
  
  pinMode(potPin, INPUT);     // potPin (A0) is input
  pinMode(9, OUTPUT);         // LED 1
  pinMode(10, OUTPUT);        // LED 2
  pinMode(11, OUTPUT);        // LED 3
  pinMode(12, OUTPUT);        // LED 4
  pinMode(13, OUTPUT);        // LED 5
  
  Serial.begin(9600);         // begin communication with arduino
}

/*************************************************************
  LED PATTERNS
**************************************************************/

void toggle() {
  buttonState = digitalRead(buttonPin);
  lastButtonState = !lastButtonState;
  if (buttonState == HIGH) {
    buttonPushCounter++;
  }
}

void flash() {
  Serial.println("flashing");
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);

  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
}

void all_on() {
  Serial.println("all on");
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
}

void bouncing() {
  Serial.println("bouncing");
  for (int i = 9; i <= 13; i ++) {
    digitalWrite(i, HIGH);
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      digitalWrite(i, LOW);
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        continue;
      } else {
        i--;
      }
    } else {
      i--;
    }
  }
}

void every_other() {
  Serial.println("every other");
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
    
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      digitalWrite(9, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(13, HIGH);
    }
  }
}

void converge() {
  Serial.println("converge");
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);

  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
    
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);

      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        digitalWrite(9, HIGH);
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
        digitalWrite(12, LOW);
        digitalWrite(13, HIGH);
      }
    }
  }
}

void all_off() {
  Serial.println("all off");
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
}

/*************************************************************
  MAIN LOOP
**************************************************************/

void loop() {
//  val = analogRead(potPin);               // Set frequency to reading from potentiometer
  buttonState = digitalRead(buttonPin);     // Read whether the button is pushed or not
  Serial.println(buttonState);

//  if ((buttonState == HIGH) && (buttonState != lastButtonState)) {            // If pushed, do this
//    buttonPushCounter ++;                       // Increase buttonPushCounter
//  }

  if (buttonPushCounter == 1) {
    all_on();
  }
  if (buttonPushCounter == 2) {
    every_other();
  }
  if (buttonPushCounter == 3) {
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);                // Janky fix for lights staying HIGH when they should not be
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    bouncing();
  }
  if (buttonPushCounter == 4) {
    flash();
  }
  if (buttonPushCounter == 5) {
    converge();
  }
  if (buttonPushCounter > 5) {
    buttonPushCounter = 0;
    all_off();
  }
  lastButtonState = buttonState;
  //  delay(debounceDelay);
}

