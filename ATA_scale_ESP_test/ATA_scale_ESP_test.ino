
long last = 0;
volatile long val = 0;
volatile bool ready = false;

void onDataReady()
{
	if (!digitalRead(2))
	{
		ready = false;
		long d = 0;
		for (int i = 0; i < 24; i++)
		{
			digitalWrite(0, HIGH);
			digitalWrite(0, LOW);
			if (digitalRead(2)) d++;
			d <<= 1;
		}
		digitalWrite(0, HIGH);
		digitalWrite(0, LOW);
		
		if (d & 0x00800000) d |= 0xFF000000;
		val = d;
		ready = true;
	}
}

void setup()
{
	pinMode(0, OUTPUT);
	pinMode(2, INPUT_PULLUP);
	digitalWrite(0, LOW);
	
	Serial.begin(115200);
	Serial.println();
	Serial.println("ready");
	
	last = millis();
	
	attachInterrupt(2, onDataReady, FALLING);
	
}

void loop()
{	
	if (ready)
	{
		ready = false;
		Serial.print(millis() - last);
		Serial.print("\t: ");
		last = millis();
		Serial.println(val);
		
	}
}

