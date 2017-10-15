 
/* define integer 'mesaj' */
int mesaj;

/* setup the connection */
void setup() {
  /* setting speed of connection */
  Serial.begin(9600);

  /* */
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

/* executing commands */
void loop() {

  /* if the robot is connected */
  if (Serial.available() > 0)
  {
      /* read the ASCII code */
      mesaj = Serial.read();

      /* switch the command by the ASCII code */
      switch(mesaj)
      {
          /* if ASCII code is 97 (a) */ 
          case 97:
            /* switches off both leds*/
            digitalWrite(13, LOW);
            digitalWrite(12, LOW);

            /* print the executed command */
            Serial.println  (" Received 'a' ");
            break;
            
          /* if ASCII code is 98 (b) */
          case 98:
            /* lights up one led */
            digitalWrite(12, HIGH);

            /* print the executed command */
            Serial.println(" Received 'b' ");
            break;
            
          /* if ASCII code is 99 (c) */
          case 99:
            /*lights up the other led*/
            digitalWrite(13, HIGH);

            /* print the executed command */
            Serial.println(" Received 'c' ");
            break;
          /* if ASCII code is 100 (d) */
          case 100:
            /* lights up both leds */
            digitalWrite(12, HIGH);
            digitalWrite(13, HIGH);

            /* print the executed command */
            Serial.println(" Received 'd' ");
            break;
        }
    }

}
