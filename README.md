## State Machines:  Blink.ino learns how to snooze

I'm a big fan of state machines.  Almost every arduino sketch usually ends up at least with one intentional state machine, and a bunch of non-intentional state machines as well.  Here, I'll introduce the concept of state machines apply a state machine to a microcontroller's "Hello world!", the blink routine.  After that I'll explore some more complicated state machines.

### Expected background
* C/C++ branch statements
* Basic arduino IDE operation


### What is a state machine
A 'state' is the condition of a thing, at a specific time.  Something that can accomplish tasks that utilizes states at its core is a state machine.  Also known as a Finite State Machine (FSM) meaning that we know all possible states of the thing.

That's some academic mumbo-jumbo though.  A state machine is just a piece of memory that holds *some value* until some time source comes along and tells it to adopt *some new value* based on what it was, and whatever else the designer wanted.  It's a thing with some per-determined set of states, a memory element that holds the current state, and a time element that causes the state machine to move.  I like to call it 'ticking'.

A classic example of a state machine is a counter.  An incrementing for loop for example, or a 74x4040 12 bit binary counter for the hardware folks.  Each time the machine is poked, either by the clock or loop, the state of the memory changes to a new state equaling the old state plus one.  The finite set of states it can exist is the numbers it can count.

Let's take at some diagrams!

-> [![alt text](https://cdn.sparkfun.com/assets/home_page_posts/1/8/0/1/counter_logic.png)](https://cdn.sparkfun.com/assets/home_page_posts/1/8/0/1/counter_logic.png) <-

->[![alt text](https://cdn.sparkfun.com/assets/home_page_posts/1/8/0/1/Counter_sm.png)](https://cdn.sparkfun.com/assets/home_page_posts/1/8/0/1/Counter_sm.png)<-


#### Moore State Machine
So there's this guy, Edward Moore, who writes a paper in 1956 (__Gedanken-experiments on Sequential Machines__).  He says the output is dependent only on the state, and the next state is dependen on the current state (or output), and the input.

-> [![alt text](https://cdn.sparkfun.com/assets/home_page_posts/1/8/0/1/moore1.png)](https://cdn.sparkfun.com/assets/home_page_posts/1/8/0/1/moore1.png) <-

#### Mealy State Machine
Then there's this other guy, George Mealy.  He wrote a paper one year earlier than Moore entitled __A Method for Synthesizing Sequential Circuits__ where he goes into great depths about creating state machines from mathematical functions, and describes those state machine's output's in terms of their inputs.

-> [![alt text](https://cdn.sparkfun.com/assets/home_page_posts/1/8/0/1/mealy1.png)](https://cdn.sparkfun.com/assets/home_page_posts/1/8/0/1/mealy1.png) <-

-> [![alt text](https://cdn.sparkfun.com/assets/home_page_posts/1/8/0/1/mealy2.png)](https://cdn.sparkfun.com/assets/home_page_posts/1/8/0/1/mealy2.png) <-

#### Abstract Diagram
I find that when programming up state machines in C, the distinction between Moore or Mealy isn't as important.  I kind of mix the two.  Some states have a static value, while other times the transition between states is the information.  I put the static outputs under the state name and the conditions/events that happen on state transition by the arrows.  The diagram is an abstract representation of the program.  When designing a state machine, it's OK if the diagram isn't quite right the first time.  For me, drawing the machine proves what I do and do not know yet.  It can always be refined later when the bugs come out.

-> [![alt text](https://cdn.sparkfun.com/assets/home_page_posts/1/8/0/1/state_diagram_form.png)](https://cdn.sparkfun.com/assets/home_page_posts/1/8/0/1/state_diagram_form.png) <-

-> [![alt text](https://cdn.sparkfun.com/assets/home_page_posts/1/8/0/1/implicit_state.png)](https://cdn.sparkfun.com/assets/home_page_posts/1/8/0/1/implicit_state.png) <-

-> [![alt text](https://cdn.sparkfun.com/assets/home_page_posts/1/8/0/1/explicit_state.png)](https://cdn.sparkfun.com/assets/home_page_posts/1/8/0/1/explicit_state.png) <-

### The blink.ino Sketch
#### blink_fsm.ino
I'll start by re-writing the familiar blink.ino sketch with the behavior and syntax of a state machine, using a switch-case.  The example is to light the LED for 1 second, turn it off for 1 second, and repeat.  Here there are two states, LED_ON and LED_OFF

-> [![alt text](https://cdn.sparkfun.com/assets/home_page_posts/1/8/0/1/blink_fsm_1.png)](https://cdn.sparkfun.com/assets/home_page_posts/1/8/0/1/blink_fsm_1.png) <-

In each state, the LED value is shown under the line.  The arrows are each labeled TRUE because no matter what, move to the next state.  This state machine doesn't have any inputs.  Every second, we'll evaulate the state machine.  If the state is 1, the output is 1 and move to the state 0.  Here's the C implementation:

Full source file (github): [blink_fsm.ino](https://github.com/marshalltaylorSFE/state_machines/raw/master/blink_fsm/blink_fsm.ino)

```

```

The memory element of the state machine is a variable named 'fsm_state'.  The states are LED_ON and LED_OFF as #defined.  The state machine works by comparing the state variable fsm_state with the two #defined states.  If the state matches, its code is executed and the state machine is moved to the other state.

note:  the extra code associated with the processing of the state machine will cause the cycle time to be greater than a second!  It will run a little slow.  This could be interrupt driven for better accuracy.


#### blink_fsm_ms.ino
Next I want to speed up the state machine's 'tick'.  I prevent the states from progressing until some timer has expired.  The timer counts every ms, so I'll wait 1000 ticks a second.  When it expires, I'll write the new state to the LED and change states.  The motivation to this is being able to have the processor do something else while the state machine is waiting.

-> [![alt text](https://cdn.sparkfun.com/assets/home_page_posts/1/8/0/1/blink_fsm_ms.png)](https://cdn.sparkfun.com/assets/home_page_posts/1/8/0/1/blink_fsm_ms.png) <-

The C implementation

Full source file (github): [blink_fsm_ms.ino](https://github.com/marshalltaylorSFE/state_machines/raw/master/blink_fsm_ms/blink_fsm_ms.ino)

```

```

The state machine works but I'm not terribly happy about how it came out.  Notice that it's easy to run a branch of code on the conditions of exit from a state, but not during the enterance of the state.  This makes the setting of the LED happen at the end of LED_OFF state, and visa versa.  It's counter-intuitive to me and I think it can be made clearer by adding two more states, each that only wait.

#### blink_fsm_final

-> [![alt text](https://cdn.sparkfun.com/assets/home_page_posts/1/8/0/1/blink_fsm_final.png)](https://cdn.sparkfun.com/assets/home_page_posts/1/8/0/1/blink_fsm_final.png) <-

Here, the states LED_ON and LED_OFF write to the LED, clear the counter, and move on.  The counter is modified to 999 to account for the extra state, though we're getting farther off time the faster we run the clock.  The ratio of state-machine-processing-time to delay(1)-execution-time is getting higher as the speed increases, and the percentage error goes up with it.

Full source file (github): [blink_fsm_final.ino](https://github.com/marshalltaylorSFE/state_machines/raw/master/blink_fsm_final/blink_fsm_final.ino)

```

```

**Pro Tip:**  Run the msCounts incrementer with a 1 ms timer Interrupt Service Routine (ISR) instead.  Meanwhile, loop the FSM as fast as possible.  This will correct timing.  Keep in mind that if the code execution time between ISR calls (the state machine processing time) is longer than the ISR call interval, the program will most likely lock up.

### "Yeah, so what?  The LED was blinking to begin with!"

State machines are not always appropriate, but they're good for doing specific tasks.  
Consider an alarm clock.  What would its behavioral model look like?  The alarm clock has several state it can exist in and a couple of inputs that can be used to control it.

**States**
* Pleasantly keeping time
* Vengefully alarming
* Eagerly awaing the end of the snooze cycle so it can wake you up again

**Inputs**
* Arm switch
* Snooze button

There are a few more, like time set and alarm set inputs, but this example limits to just the alarm operations.

Described as a state machine:

-> [![alt text](https://cdn.sparkfun.com/assets/home_page_posts/1/8/0/1/alarm_clock.png)](https://cdn.sparkfun.com/assets/home_page_posts/1/8/0/1/alarm_clock.png) <-

(caption)

In the C implementation, the blink_fsm_final.ino is used to keep track of time.  The 'alarm time' is set to 15 second from reboot (actually about 20 with error) and the snooze cycle is set for a respective 5 seconds.

**Button and switch connections**
* Connect a normally open button between pin 7 and ground of an arduino.  This will serve as "SNOOZE".
* Connect a SPST switch between pin 9 and ground.  This will serve as "ARM".

Close the "ARM" switch and load the program

Full source file (github): [alarm_clock.ino](https://github.com/marshalltaylorSFE/state_machines/raw/master/alarm_clock/alarm_clock.ino)

```

```
To connect the two state machines, an input to the blink_fsm is added.  This input prevents the LED from being set if the alarm_fsm is not in the alarm state.

The modified state of the blink state machine

-> [![alt text](https://cdn.sparkfun.com/assets/home_page_posts/1/8/0/1/alarm_clock_blink_mod.png)](https://cdn.sparkfun.com/assets/home_page_posts/1/8/0/1/alarm_clock_blink_mod.png) <-

### More Examples

Software serial module

OpenGL render engine

Toaster

### Conclusion
In my experience, any coder who can diagram a program before writing it will succeed at the program.  I've written one too many programs that end up as a wad of nested 'if' statements.  When I do, I evidently need to add one little thing that horribly breaks the program and I'm forced to re-evaluate my life choices.  The outcome is that I would rather not write anything rather than write painful code, and the time is better spent *thinking* about how to do it.  Using tools like state machine diagrams, flowcharts, class diagrams, and unit tests have allowed me to write more complex yet maintainable code


Stay tuned for  more posts about microcontroller programming, synthesizing and controlling audio, and experiments with vacuum tubes.

Peace.