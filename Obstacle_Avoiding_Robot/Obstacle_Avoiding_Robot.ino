int buzzer = 10;
int smokeA0 = A0;
// Your threshold value
int sensorThres = 400;

// Ultra sonic 
// constants won't change
const int TRIG_PIN   = 3; // Arduino pin connected to Ultrasonic Sensor's TRIG pin
const int ECHO_PIN   = 2; // Arduino pin connected to Ultrasonic Sensor's ECHO pin
const int BUZZER_PIN = 8; // Arduino pin connected to Piezo Buzzer's pin
const int DISTANCE_THRESHOLD = 20; // centimeters
// variables will change:
float duration_us, distance_cm;

//LDR 
int LDRIN = 7;
int LDROUT = 9;

void setup() {
  //Smoke sensor Pin Config
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  
  //Ultra sonic sensor pin config
  pinMode(TRIG_PIN, OUTPUT);   // set arduino pin to output mode
  pinMode(ECHO_PIN, INPUT);    // set arduino pin to input mode
  pinMode(BUZZER_PIN, OUTPUT); // set arduino pin to output mode

  //LDR Pin Config
  pinMode(LDRIN,INPUT);
  pinMode(LDROUT,OUTPUT);

  Serial.begin (9600);         // initialize serial port
}

void loop() {
  int analogSensor = analogRead(smokeA0);
  Serial.print("Pin A0: ");
  Serial.println(analogSensor);

  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    tone(buzzer, 1000, 200);
  }
  else
  {
    noTone(buzzer);
  }//Smoke sensor end

  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);
  // calculate the distance
  distance_cm = 0.017 * duration_us;

//Ultrasonic Sensor sense the Distance
    if(distance_cm < DISTANCE_THRESHOLD)
    digitalWrite(BUZZER_PIN, HIGH); // turn on Piezo Buzzer
  else
    digitalWrite(BUZZER_PIN, LOW);  // turn off Piezo Buzzer

  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  int temp=digitalRead(LDRIN );      //assign value of LDR sensor to a temporary variable
  Serial.println("Intensity="); //print on serial monitor using ""
  Serial.println(temp);         //display output on serial monitor
  if(temp==HIGH) 
  {              //HIGH means,light got blocked
  digitalWrite(9,HIGH); //if light is not present,LED on
  }
  else
  {
  digitalWrite(9,LOW);         //if light is present,LED off
  }
 
  delay(300);
}
