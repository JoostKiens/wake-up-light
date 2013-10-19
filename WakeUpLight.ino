const int LED = 9;
const int BTN = 7;

// state of buttton
int val = 0;
int oldVal = 0;
int state = 0;
int hasChanged = 0;
int i = 0;

void setup()
{
	pinMode(LED, OUTPUT);
	pinMode(BTN, INPUT);

	Serial.begin(9600);
}

void loop()
{
	val = digitalRead(BTN);

	//Check if the input is HIGH (Button pressed)
	if ((val == HIGH) && (oldVal == LOW))
	{
		Serial.println("Button pressed");
		state = 1 - state;
		hasChanged = 1;
		delay(10);
	}
	else{
		hasChanged = 0;
	}

	oldVal = val;

	if (state == 1)
	{
		fadeIn();
	}
	else
	{
		analogWrite(LED, 0); 
	}
}

void fadeIn()
{
	if (hasChanged == 1)
	{
		Serial.println("Fade in");
		for (i = 0; i <= 255; i++)
		{
			analogWrite(LED, i);
			// this should be asynchronous
			// so we can turn off the light
			// even when it is still fading in
			delay(10);
		}
	}
	else
	{
		analogWrite(LED, 255); 
	}
}