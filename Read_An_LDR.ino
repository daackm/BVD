#define lightSensor A5

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int  lightLevel = analogRead(lightSensor);
  Serial.println(lightLevel);
  delay(1000);
}
