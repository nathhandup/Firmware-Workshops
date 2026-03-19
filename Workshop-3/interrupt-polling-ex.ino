/*
const int buttonPin = 17; 

void setup() {
  Serial.begin(115200);
  
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.println("ESP32 Button Test Ready");
}

void loop() {
  // Read the button state
  int buttonState = digitalRead(buttonPin);

  // Button pressed (LOW because of pull-up)
  if (buttonState == LOW) {
    Serial.println("Pressed!");
  } else {
    Serial.println("Not pressed.");
  }
  delay(200);
}



*/





const int buttonPin = 17;
int x = 0;

// Volatile means it's expected to change by multiple threads, interrupts or external hardware.
volatile bool buttonPressed = false;

// Loads onto internal RAM rather than flash memory. Avoids clashing
// Used on functions that must execute rapidly, like: interrupt handlers!
void IRAM_ATTR handleButtonInterrupt() {
  buttonPressed = true;
}

void setup() {
  Serial.begin(115200);

  pinMode(buttonPin, INPUT_PULLUP);

  // Attach function to button pin.
  // "Falling" keyword means when the input goes from HIGH logic down to LOW, the interrupt is triggered.
  // "Rising" is the opposite.
  attachInterrupt(digitalPinToInterrupt(buttonPin), handleButtonInterrupt, FALLING);

  // generate rand
  x = esp_random();
  if(x < 0) {
    x = -x;
  }

  Serial.println("Interrupt button ready");
}

void loop() {
  if (buttonPressed) {
    Serial.println("Button pressed!");
    Serial.println("Now, we wait...");
    delay(1000);
    Serial.println("Done waiting.");
    buttonPressed = false;
    delay(1);
  } 
  Serial.println("Calculating ... Value of x: ");
  Serial.print(x);
  Serial.println("");

  // collatz algorithm
  if (x % 2 == 0) {
    x /= 2;
  } else {
    x *= 3;
    x += 1;
  }

  delay(500);
}
