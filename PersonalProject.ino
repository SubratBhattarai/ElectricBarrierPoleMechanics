#include <Servo.h> // Importing servo library

Servo myservo;
const int servoPin = 8; // Servo Address
const int echoPin = 11;   // For echo of sound
const int triggerPin = 12;   // For triggering sound
const float speedOfSound = 342; // 342 m/s
int buzzer = 5; // Buzzer PIN
int pin1 = 10; // Red LED
int pin2 = 6; // Yellow LED
int pin3 = 9; // Green LED

// Declaring Functions
float measuringDistance(); 
void servoMotors(float);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Servo Assigns
  myservo.attach(servoPin);
  myservo.write(90); // To center the postions of servo


  // Digital Input/ Output Assigns
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly: 
  // Calling Function with return value
  float avg = measuringDistance();
  servoMotors(avg);
}

float measuringDistance(){
  long duration = 0;
  float distanceBetweenObject = 0;
  float sum = 0;
  float avg = 0;

  digitalWrite(triggerPin, LOW);
  digitalWrite(triggerPin, HIGH);
  digitalWrite(triggerPin, LOW);
  
  duration = pulseIn(echoPin, HIGH, 150000); // Time taken

 for(int i = 0; i < 100; i++){
    distanceBetweenObject = ((speedOfSound * duration)/2e4); // Time taken to go to the objects. Since, echo returns the value - we divide it my 2 to get single direction. 2e4 = 2x10**4
    sum += distanceBetweenObject;
  }
  avg = sum/100;
  Serial.println(avg);
  delay(500);

  return avg;
}

void servoMotors(float avg){
  if(avg < 50){ // This is in CM. For bigger machines we use Meters.
    digitalWrite(pin3, LOW); // If Green is on. Turn off
    digitalWrite(pin1, HIGH); // Turn on RED LED
    myservo.write(180); // Rotate 180 deg
    tone(buzzer, 50); // Buzz at 50hz
  }  
  else{
    digitalWrite(pin1, LOW); // Turn of Red LED
    digitalWrite(pin2, HIGH); // Turn on Yellow LED
    delay(300); // Delay
    digitalWrite(pin2, LOW); // Turn off Yellow LED.. Keeps on blinking
    digitalWrite(pin3, HIGH); // Turn on Green LED
    myservo.write(0); 
    noTone(buzzer); // Remove Buzzer Sound
  }
}
