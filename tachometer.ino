// Defines
#define PIN 2  // pins D2 and D3 are available for interrupt on the Nano

// Global variables
volatile unsigned long start_time, end_time, duration, rpm;


void setup() {
  pinMode(PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN), isr, CHANGE);  // create an interrupt whenever the pin changes
  Serial.begin(19200);
}


void loop() {
  rpm = 60000000 / duration;  // 1/duration, * 60 seconds per minute, * 1000000 us per second
  if(duration > 1000000 || rpm > 10000) rpm = 0;  // reject unresonable numbers
  Serial.println(rpm);
  delay(500);
}


void isr() {
  if (digitalRead(PIN) == 0) return;  // 
  end_time = micros();               // take note of the current time. this is the end of the rotation
  duration = end_time - start_time;  // calculate the duration of the rotation
  start_time = end_time;             // get ready for the next rotaion
}
