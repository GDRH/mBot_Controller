int mesaj;

void setup() {
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  if (Serial.available() > 0)
    {
      mesaj = Serial.read();

      switch(mesaj)
        {
          case 97:
            digitalWrite(13, LOW);
            digitalWrite(12, LOW);
            Serial.println  (" Received 'a' ");
            break;
          case 98:
            digitalWrite(12, HIGH);
            Serial.println(" Received 'b' ");
            break;
          case 99:
            digitalWrite(13, HIGH);
            Serial.println(" Received 'c' ");
            break;
          case 100:
            digitalWrite(12, HIGH);
            digitalWrite(13, HIGH);
            Serial.println(" Received 'd' ");
            break;
        }
    }

}
