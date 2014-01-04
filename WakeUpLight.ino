const int LED = 9;
const int BTN = 7;

// state of buttton
int val = 0;
int oldVal = 0;
int state = 0;
int hasChanged = 0;
int i = 0;

void setup() {
	pinMode(LED, OUTPUT);
	pinMode(BTN, INPUT);

	Serial.begin(9600);
}


void loop() {
	listenForBtnPress();

	if (state == 1) {
		turnLedOn();
	}
	else {
		turnLedOff();
	}
}

// Turn LED immediately
// off
void turnLedOff() {
	analogWrite(LED, 0);
}

// Turn LED on, slowly or immediately
void turnLedOn() {
	if (hasChanged == 1) {
		fadeLedIn();
	}
	else {
		analogWrite(LED, 255);
	}
}

// Slowly Fade LED in,
// listen for another button press
// to turn LED off
void fadeLedIn() {
	Serial.println("Fade in");
	for (i = 0; i <= 255; i++) {
		// Turn of light & exit
		// loop is button is pressed
		listenForBtnPress();
		if (state == 0) {
			turnLedOff();
			break;
		}
		analogWrite(LED, i);
		delay(30);
	}
}

// Listens for button press.
// sets global vars:
// val, oldVal, state & hasChanged
//
// TODO: refactor this, fix all the sie effects
void listenForBtnPress() {
	val = digitalRead(BTN);

	//Check if the input is HIGH (Button pressed)
	if ((val == HIGH) && (oldVal == LOW)) {
		Serial.println("Button pressed");
		state = 1 - state;
		hasChanged = 1;
		delay(10);
	}
	else {
		hasChanged = 0;
	}

	oldVal = val;
}
