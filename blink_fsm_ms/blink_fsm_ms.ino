#define LED_OFF 0
#define LED_ON 1

uint8_t fsm_state = LED_OFF;
uint16_t msCounts = 0;


void setup() {
  pinMode(13, OUTPUT);  // initialize digital pin 13 as an output.
}


void loop()
{
  //state machine
  fsm_state;  //Next state defaults to current state

  switch (fsm_state)
  {
    case LED_OFF:
      //Statements to execute every time LED_OFF is reached
      //Statements to execute when it's time to move to the next state
      if(msCounts >= 1000)
      {
        digitalWrite(13, HIGH);  //Process the next state's function
        fsm_state = LED_ON;
        msCounts = 0;
      }
      break;
    case LED_ON:
      //Statements to execute every time LED_ON is reached
      //Statements to execute when it's time to move to the next state
      if(msCounts >= 1000)
      {
        digitalWrite(13, LOW);  //Process the next state's function
        fsm_state = LED_OFF;
        msCounts = 0;
      }
      break;
    default:
      break;
  }

  delay(1);              // wait for a millisecond
  if(msCounts < 0xFFFF)  // Don't let the msCounts overflow
  {
    msCounts++;
  }
}
