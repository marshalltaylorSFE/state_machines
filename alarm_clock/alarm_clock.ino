//Timer FSM numbers
uint16_t msCounts = 0;
uint16_t sCounts = 0;

#define LED_OFF 0
#define LED_ON_WAIT 1
#define LED_ON 2
#define LED_OFF_WAIT 3
uint8_t timer_fsm_state = LED_OFF;

//Alarm FSM numbers
#define ALARM_SECONDS 15
#define SNOOZE_SECONDS 5
uint8_t alarmActive = 0;
uint16_t nextAlarmTime = 65535;

#define ALARM_IDLE 0
#define ALARM_RINGING 1
#define ALARM_SNOOZING 2
uint8_t alarm_fsm_state = ALARM_IDLE;



// the setup function runs once when you press reset or power the board
void setup()
{
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  pinMode(7, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  nextAlarmTime = ALARM_SECONDS;
}

// the loop function runs over and over again forever
void loop()
{
  //timer state machine
  switch (timer_fsm_state)
  {
    case LED_OFF:
      //Statements to execute every time LED_OFF is reached
      digitalWrite(13, LOW);
      timer_fsm_state = LED_ON_WAIT;
      break;
    case LED_ON_WAIT:
      //Statements to execute every time LED_OFF_WAIT is reached
      if(msCounts >= 1000)
      {
        timer_fsm_state = LED_ON;
        msCounts = 0;
      }
      break;
    case LED_ON:
      //Statements to execute every time LED_ON is reached
      if(alarmActive == 1)
      {
        digitalWrite(13, HIGH);
      }
      timer_fsm_state = LED_OFF_WAIT;
      break;
    case LED_OFF_WAIT:
      //Statements to execute every time LED_ON_WAIT is reached
      if(msCounts >= 1000)
      {
        timer_fsm_state = LED_OFF;
        msCounts = 0;
        if( sCounts < 0xFFFF )
        {
          sCounts++;
        }
      }
      break;
    default:
      break;
  }

  uint8_t buttonValue = digitalRead(7);
  uint8_t switchValue = digitalRead(9);

  //alarm state machine
  switch (alarm_fsm_state)
  {
    case ALARM_IDLE:
      if((sCounts >= nextAlarmTime)&&(switchValue == 0))
      {
        //Goto next state
        alarm_fsm_state = ALARM_RINGING;
        alarmActive = 1;
      }
      break;
    case ALARM_RINGING:
      if(buttonValue == 0)
      {
        nextAlarmTime = sCounts + SNOOZE_SECONDS;
        alarm_fsm_state = ALARM_SNOOZING;
        alarmActive = 0;
      }
      if(digitalRead(9) == 1)//If switch went off, goto idle instead
      {
        alarm_fsm_state = ALARM_IDLE;  // this overwrites the snooze button option
        alarmActive = 0;
      }
      break;
    case ALARM_SNOOZING:
      if(sCounts >= nextAlarmTime)
      {
        //Goto next state
        alarm_fsm_state = ALARM_RINGING;
        alarmActive = 1;
      }
      if(switchValue == 0)
      {
        //Goto alarm idle
        alarm_fsm_state = ALARM_IDLE;
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
