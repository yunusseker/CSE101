const int ledPin = 13;
const int externalLedPin = 8; 
const int buttonPin = 2;

int buttonPressCount = 0;

void setup() {
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
    pinMode(externalLedPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
    if (Serial.available() > 0) {
        char command = Serial.read();
        executeCommand(command);
    }

    checkButtonPress();
}

void executeCommand(char command) {
    switch (command) {
        case '1':
            digitalWrite(ledPin, HIGH);
            break;
        case '2':
            digitalWrite(ledPin, LOW);
            break;
        case '3':
            flashLed();
            break;
        case '4':
            computeFactorial();
            break;
        case '5':
            buttonPressCount++;
            Serial.print("Button Press Count: ");
            Serial.println(buttonPressCount);
            computeFactorial();
            break;
        case '6':
            turnOnExternalLed();
            break;
    }
}


void flashLed() {
    for (int i = 0; i < 5; ++i) {
        digitalWrite(ledPin, HIGH);
        delay(500);
        digitalWrite(ledPin, LOW);
        delay(500);
    }
}

void computeFactorial() {
    int number = Serial.parseInt();
    int factorial = 1;
    for (int i = 1; i <= number; ++i) {
        factorial *= i;
    }
    Serial.print("Factorial: ");
    Serial.println(factorial);
}

void checkButtonPress() {
    static int lastButtonState = HIGH;
    int buttonState = digitalRead(buttonPin);

    if (buttonState == LOW && lastButtonState == HIGH) {
        buttonPressCount++;
        Serial.print("Button Press Count: ");
        Serial.println(buttonPressCount);
        computeFactorial();
    }

    lastButtonState = buttonState;
}

void turnOnExternalLed() {
    digitalWrite(externalLedPin, HIGH);
    Serial.println("External LED turned on");
}
