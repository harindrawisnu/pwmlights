/*
 * Simple PWM lights control using PulseIn
 * By : Harindra W Pradhana
 * Feature :
 * - 2 channel PWM input
 * - 2 channel lights (secondary & primary)
 * - 2 channel turn lights (left & right)
 */

// PIN configuration
#define MAIN_SIGNAL A0 // PWM input pin for main light
#define TURN_SIGNAL A1 // PWM input pin for turn light
#define PRIMARY 2 // output pin for primary light
#define SECONDARY 3 // output pin for secondary light
#define RIGHT 4 // output pin for right turn light
#define LEFT 5 // output pin for left turn light
#define THR1 1250 // first PWM threshold
#define THR2 1750 // second PWM threshold
#define BLINKING 600 // turn light blinking each 1000 milliseconds or 1 seconds

int ch1,ch2; // your PWM input value for main light & turn light
unsigned long time1; // timer for blinking turn light
bool state = false; // blinking state

void setup() {
  Serial.begin(9600);
  pinMode(MAIN_SIGNAL, INPUT);
  pinMode(TURN_SIGNAL, INPUT);
  pinMode(PRIMARY, OUTPUT);
  pinMode(SECONDARY, OUTPUT);
  pinMode(RIGHT, OUTPUT);
  pinMode(LEFT, OUTPUT);

  // turning off all pin
  digitalWrite(PRIMARY, LOW);
  digitalWrite(SECONDARY, LOW);
  digitalWrite(RIGHT, LOW);
  digitalWrite(LEFT, LOW);

  // setting initial time
  time1 = millis();
}

void loop() {
  // blinking state check
  unsigned long time2 = millis();
  if (time2>time1)
  {
    unsigned long delta = time2-time1; // count the time differences
    if (delta>BLINKING)
    {
      state=!state; // blink the turn light
      time1=time2; // reset the timer
    }
  }
  else time1=time2; // reset the timer in case the millis reset

  // reading PWM, limit timeout to 25 miliseconds, 1 seconds seems to be too long
  ch1 = pulseIn(MAIN_SIGNAL, HIGH, 25000);
  delay(100);
  ch2 = pulseIn(TURN_SIGNAL, HIGH, 25000);
  delay(100);

  Serial.write("CH1 : ");
  Serial.print(ch1);
  Serial.write(" ; CH2 : ");
  Serial.println(ch2);
  // main light code here
  if (ch1>THR2) 
  {
    // turning on all light on high signal
    digitalWrite(PRIMARY, HIGH);
    digitalWrite(SECONDARY, HIGH);
    // blinking both turn signal
    if (state==true) digitalWrite(RIGHT, HIGH);
    else digitalWrite(RIGHT, LOW);
    if (state==true) digitalWrite(LEFT, HIGH);
    else digitalWrite(LEFT, LOW);
  }
  else if (ch1>THR1)
  {
    // turning on only secondary light on center signal
    digitalWrite(SECONDARY, HIGH);
    digitalWrite(PRIMARY, LOW);
  }
  else
  {
    // turning off all light on low signal
    digitalWrite(PRIMARY, LOW);
    digitalWrite(SECONDARY, LOW);
  }

  // turn light code here
  if (ch2>THR2) 
  {
    // blinking right light on high signal
    if (state==true) digitalWrite(RIGHT, HIGH);
    else digitalWrite(RIGHT, LOW);
    digitalWrite(LEFT, LOW);
  }
  else if (ch2>THR1)
  {
    // turning off all turn lights on center signal unless we activate the high beam
    if (ch1<THR2)
    {
      digitalWrite(RIGHT, LOW);
      digitalWrite(LEFT, LOW);
    }
  }
  else
  {
    // blinking left light on low signal
    digitalWrite(RIGHT, LOW);
    if (state==true) digitalWrite(LEFT, HIGH);
    else digitalWrite(LEFT, LOW);
  }
}
