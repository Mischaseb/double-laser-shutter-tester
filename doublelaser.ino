long Start;   // this is the time in microseconds that the shutter opens (the arduino runs a microsecond clock in the background always - it is reasonably accurate for this purpose)
long Stop;    // this is the time in microseconds that the shutter closes
long Start2;   // this is the time in microseconds that the shutter opens (the arduino runs a microsecond clock in the background always - it is reasonably accurate for this purpose)
long Stop2;    // this is the time in microseconds that the shutter closes
int Fired = 0;  // this is a flag indicating when the shutter has been fired completely.  when fired =1, the shutter has been fired, and the computer needs to display the information related to the exposure time.
int Risingflag = 0;  // this is a flag that i set in my interrupt routine, Rising flag is set to = 1 when the voltage INCREASES in the interrupt
int Fallingflag = 0;  // this is a flag that i set in the interrupt routine, Fallingflag is set to =1 when the voltage DECREASES in the interrupt
int Risingflag2 = 0;  // this is a flag that i set in my interrupt routine, Rising flag is set to = 1 when the voltage INCREASES in the interrupt
int Fallingflag2 = 0;  // this is a flag that i set in the interrupt routine, Fallingflag is set to =1 when the voltage DECREASES in the interrupt



void setup() {                                                  //This part of the program is run exactly once on boot

  Serial.begin(9600);                                          //opens a serial connection.
  attachInterrupt(digitalPinToInterrupt(2), CLOCK, CHANGE);    //run the function CLOCK, every time the voltage on pin 2 changes.
  attachInterrupt(digitalPinToInterrupt(3), CLOCK2, CHANGE);
}

void loop() {

  if(Risingflag ==1){
    Start = micros();
    Risingflag = 0;
  }

  if(Fallingflag ==1){
    Stop = micros();
    Fallingflag = 0;
  }

  if(Risingflag2 ==1){
    Start2 = micros();
    Risingflag2 = 0;
  }

  if(Fallingflag2 ==1){
    Stop2 = micros();
    Fallingflag2 = 0;
    Fired = 1;
  }
  if(Fired ==1){
    Serial.print("Start: ");
    Serial.println(Start);
    Serial.print("Stop: ");
    Serial.println(Stop);
    Serial.print("Start2: ");
    Serial.println(Start2);
    Serial.print("Stop2: ");
    Serial.println(Stop2);
    long Speed1 = (Stop - Start);
    long Speed2 = (Stop2 - Start2);
    long Curtain1 = (Start2 - Start);
    long Curtain2 = (Stop2 - Stop);
    float SS1 = (float)Speed1/1000;
    float S1 = 1/(SS1/1000);
    float SS2 = (float)Speed2/1000;
    float S2 = 1/(SS2/1000);
    float C1S = (float)Curtain1/1000;
    float C2S = (float)Curtain2/1000;
    Serial.print("Speed1 (ms): ");
    Serial.println(SS1);
    Serial.print("Speed1 (s): 1/");
    Serial.println(S1);    
    Serial.print("Speed2 (ms): ");
    Serial.println(SS2);
    Serial.print("Speed2 (s): 1/");
    Serial.println(S2);
    Serial.print("Opening Curtain Speed (ms): ");
    Serial.println(C1S);
    Serial.print("Closing Curtain Speed (ms): ");
    Serial.println(C2S);
    Serial.println();
    Start = 0;
    Stop = 0;
    Start2 = 0;
    Stop2 = 0;
    Fired = 0;
    
  }
}

void CLOCK(){                     //this is the interrupt function, which is called everytime the voltage on pin 2 changes, no matter where in the main program loop that the computer is currently in
  if(digitalRead(2) == HIGH){
    Risingflag = 1;                // if the voltage on pin 2 is high, set the Risingflag to 1 : this will trigger the function called Rising from the main loop, which will set a start time
  }
  if(digitalRead(2) == LOW){        // . if the voltage on pin 2 is low, set the Fallingflag to 1 : this will trigger the function called Falling from the main loop, which will set the stop time, and also set the Fired flag to 1.
    Fallingflag =1;
  }
}

void CLOCK2(){                     //this is the interrupt function, which is called everytime the voltage on pin 2 changes, no matter where in the main program loop that the computer is currently in
  if(digitalRead(3) == HIGH){
    Risingflag2 = 1;                // if the voltage on pin 2 is high, set the Risingflag to 1 : this will trigger the function called Rising from the main loop, which will set a start time
  }
  if(digitalRead(3) == LOW){        // . if the voltage on pin 2 is low, set the Fallingflag to 1 : this will trigger the function called Falling from the main loop, which will set the stop time, and also set the Fired flag to 1.
    Fallingflag2 =1;
  }
}
