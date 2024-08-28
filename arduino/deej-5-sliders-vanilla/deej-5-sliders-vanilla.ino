const int NUM_SLIDERS = 5;
const int analogInputs[NUM_SLIDERS] = {A0, A1, A2, A3, A4};
const int switchInputs[NUM_SLIDERS * 2] = {D4, D9, D3, D8, D2, D7, D1, D6, D0, D5};
const int ledOutputs[NUM_SLIDERS] = {A7, D10, D11, D12, D13};

int analogSliderValues[NUM_SLIDERS];
char switchValues[NUM_SLIDERS];
bool ledValues[NUM_SLIDERS];

void setup() { 
  ledInit();
  for (int i = 0; i < NUM_SLIDERS * 2; i++) {
    pinMode(switchInputs[i], INPUT_PULLUP);
  }
  for (int i = 0; i < NUM_SLIDERS; i++) {
    pinMode(analogInputs[i], INPUT);
  }

  Serial.begin(9600);
}

void loop() {
  updateSliderValues();
  updateSwitchValues();
  updateLED();
  sendValues(); // Actually send data (all the time)
  // printSliderValues(); // For debug
  delay(10);
}

void updateSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
     analogSliderValues[i] = analogRead(analogInputs[i]);
  }
}

void sendValues() {
  String builtString = String("");

  //add slider values to output string
  for (int i = 0; i < NUM_SLIDERS; i++) {
    builtString += String((int)analogSliderValues[i]);
    builtString += String("|");
  }

  //add switch values to output string
  for (int i = 0; i < NUM_SLIDERS; i++) {
    builtstring += String("S");
    builtstring += String((char)switchValues[i]);
    
    if (i < NUM_SLIDERS - 1) {
      builtstring += String("|");
    }
  }
  
  Serial.println(builtString);
}

void printSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogSliderValues[i]) + String(" mV");
    Serial.write(printedString.c_str());

    if (i < NUM_SLIDERS - 1) {
      Serial.write(" | ");
    } else {
      Serial.write("\n");
    }
  }
}

//initializes the LEDs and flashes them as a test
void ledInit() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    pinMode(ledOutputs[i], OUTPUT);
    digitalWrite(ledOutputs[i], HIGH);
    sleep(100);
    digitalWrite(ledOutputs[i], LOW);
    sleep(100);
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < NUM_SLIDERS; j++) {
      digitalWrite(ledOutputs[j], HIGH);
    }
    sleep(100);
    for (int j = 0; j < NUM_SLIDERS; j++) {
      digitalWrite(ledOutputs[j], LOW);
    }
    sleep(100);
  }
}

void updateSwitchValues() {
  for (int i = 0; i < NUM_SLIDERS * 2; i += 2) {
    if (digitalRead(switchInputs[i]) == LOW && digitalRead(switchInputs[i+1]) == HIGH) {
      switchValues[i] = 1;
      ledValues[i] = false;
    }
    else if (digitalRead(switchInputs[i]) == HIGH && digitalRead(switchInputs[i+1]) == LOW) {
      switchValues[i] = 2;
      ledValues[i] = false;
    }
    else {
      switchValues[i] = 0;
      ledValues[i] = true;
    }
  }
}

void updateLED() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    digitalWrite(ledOutputs[i], ledValues[i])
  }
}
