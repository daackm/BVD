
int i;

void setup() 
 {
 }

void loop() {
  digitalWrite(2,HIGH);
  for (i=1; i<=4; i++)
    {
      digitalWrite(7,HIGH);
      digitalWrite(8,LOW);
      delay(200);
      digitalWrite(7,LOW);
      digitalWrite(8,HIGH);
      delay(200);
    }
  digitalWrite(2,LOW);
  for (i=1; i<=4; i++)
    {
      digitalWrite(7,HIGH);
      digitalWrite(8,LOW);
      delay(200);
      digitalWrite(7,LOW);
      digitalWrite(8,HIGH);
      delay(200);
    }
}
