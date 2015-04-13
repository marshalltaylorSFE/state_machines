#define LED_OFF 0
#define LED_ON 1

uint8_t fsm_state = LED_OFF;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
}

// the loop function runs over and over again forever
void loop()
{
  //state machine
  uint8_t next_fsm_state = fsm_state;  //Next state defaults to current state

  switch (fsm_state)
  {
    case LED_OFF:
    //Statements to execute every time LED_OFF is reached
      digitalWrite(13, LOW);
      next_fsm_state = LED_ON;
      break;
    case LED_ON:
      //Statements to execute every time LED_ON is reached
      digitalWrite(13, HIGH);
      next_fsm_state = LED_OFF;
      break;
    default:
      break;
  }
  fsm_state = next_fsm_state;

  delay(1000);              // wait for a second
}
