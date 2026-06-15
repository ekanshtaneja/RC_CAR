// Tug-of-War Bot (Forward Only)
// Receiver CH1 -> Arduino D2
// IBT-2 #1 (Left motors):  RPWM -> D5
// IBT-2 #2 (Right motors): RPWM -> D9
// LPWM tied to GND, R_EN + L_EN tied to 5V

int ch1Pin = 2;     // Receiver Channel 1 signal
int leftPWM = 5;    // Left side motors forward
int rightPWM = 9;   // Right side motors forward

int ch1Value = 0;

void setup() {
  pinMode(ch1Pin, INPUT);
  pinMode(leftPWM, OUTPUT);
  pinMode(rightPWM, OUTPUT);

  // Start with motors off
  analogWrite(leftPWM, 0);
  analogWrite(rightPWM, 0);
}

void loop() {
  // Read PWM signal from receiver (1000-2000 µs typical)
  ch1Value = pulseIn(ch1Pin, HIGH, 25000); // timeout 25ms

  if (ch1Value > 1500) {  
    // Stick forward → run motors
    int speed = map(ch1Value, 1500, 2000, 0, 255); // scale to PWM
    analogWrite(leftPWM, speed);
    analogWrite(rightPWM, speed);
  } 
  else {
    // Stick center/back → stop motors
    analogWrite(leftPWM, 0);
    analogWrite(rightPWM, 0);
  }
}
