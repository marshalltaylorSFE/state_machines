//Define the states of the machine
#define LED_OFF 0
#define LED_ON_WAIT 1
#define LED_ON 2
#define LED_OFF_WAIT 3

//This is the memory element that contains the state variable
uint8_t fsm_state = LED_OFF;

//This holds the number of milliseconds that have been counted
uint16_t msCounts = 0;


void setup()
{
  pinMode(13, OUTPUT);  // initialize digital pin 13 as an output.
}

// the loop function runs over and over again forever
void loop()
{
  //state machine
  switch (fsm_state)
  {
    case LED_OFF:
      //Statements to execute every time LED_OFF is reached
      digitalWrite(13, LOW);
      fsm_state = LED_ON_WAIT;
      break;
    case LED_ON_WAIT:
      //Statements to execute every time LED_OFF_WAIT is reached
      if(msCounts >= 1000)
      {
        fsm_state = LED_ON;
        msCounts = 0;
      }
      break;
    case LED_ON:
      //Statements to execute every time LED_ON is reached
      digitalWrite(13, HIGH);
      fsm_state = LED_OFF_WAIT;
      break;
    case LED_OFF_WAIT:
      //Statements to execute every time LED_ON_WAIT is reached
      if(msCounts >= 1000)
      {
        fsm_state = LED_OFF;
        msCounts = 0;
      }
      break;
    default:
      break;
  }


  //Time keeping:
  delay(1);              // wait for a millisecond
  if(msCounts < 0xFFFF)  // Don't let the msCounts overflow
  {
    msCounts++;
  }
}
