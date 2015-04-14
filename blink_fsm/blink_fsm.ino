//Define the states of the machine
#define LED_OFF 0
#define LED_ON 1

//Here is the state variable
uint8_t fsm_state = LED_OFF;


void setup() {
  pinMode(13, OUTPUT);  // initialize digital pin 13 as an output.
}


void loop(){
  //state machine
  switch (fsm_state)
  {
    case LED_OFF:  //Statements to execute every time LED_OFF is reached
      digitalWrite(13, LOW);
      fsm_state = LED_ON;
      break;
    case LED_ON:   //Statements to execute every time LED_ON is reached
      digitalWrite(13, HIGH);
      fsm_state = LED_OFF;
      break;
    default:
      break;
  }

  delay(1000);              // wait for a second
}
