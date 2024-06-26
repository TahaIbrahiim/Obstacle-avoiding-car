#include <Servo.h> 
Servo Myservo;
#define ENB 3
#define ENA 2


#define trigPin 9           // Trig Pin Of HC-SR04
#define echoPin 8        // Echo Pin Of HC-SR04
#define MLa 4                   //left motor 1st pin
#define MLb 5                  //left motor 2nd pin
#define MRa 6               //right motor 1st pin
#define MRb 7               //right motor 2nd pin
long duration;
int Speed = 136;
long t;
int distance = 100;
int distanceLeft=0, distanceRight=0;


void setup() {
  Serial.begin(9600);
  pinMode(MLa, OUTPUT);     // Set Motor Pins As O/P
  pinMode(MLb, OUTPUT);
  pinMode(MRa, OUTPUT);
  pinMode(MRb, OUTPUT);
  pinMode(trigPin, OUTPUT);       // Set Trig Pin As O/P To Transmit Waves
  pinMode(echoPin, INPUT);        //Set Echo Pin As I/P To Receive Reflected Waves
  Myservo.attach(10);

  
}
void loop() 
{

  
  
 
   if (distance <= 20) {
    stopCar();
    delay(150);
    Backward();
    delay(100);
    stopCar();
    delay(150);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distanceRight > distanceLeft) {
      turnRight();
      delay(250);
      stopCar();
      
      
    } 
    else if (distanceRight < distanceLeft){
      turnLeft();
      delay(250);
      stopCar();
    }
    else{moveForward();}
    
  } else {
    moveForward();
  }
  distance = calculate_distance();
  delay(25);
}

int lookRight() {
 
  Myservo.write(40);
  delay(200);
  distance = calculate_distance();
  delay(100);
  Myservo.write(90);
  return distance;
}

int lookLeft() {


  Myservo.write(150);
  delay(200);
  int distance = calculate_distance();
  delay(100);
  Myservo.write(90);
  return distance;
  delay(100);
}




int calculate_distance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  t = pulseIn(echoPin, HIGH);
  return 0.5 * t * 0.0343; // Calculate the distance (D = 0.5T * S)
}

void moveForward() {
  // Move both motors forward
  digitalWrite(MRb, HIGH);
  digitalWrite(MRa, LOW);
  analogWrite(ENA, Speed);

  digitalWrite(MLb, HIGH);
  digitalWrite(MLa, LOW);
  analogWrite(ENB, Speed+50);
}

void Backward() {
  // Move both motors forward
  digitalWrite(MRb, LOW);
  digitalWrite(MRa, HIGH);
  analogWrite(ENA, Speed);

  digitalWrite(MLb, LOW);
  digitalWrite(MLa, HIGH);
  analogWrite(ENB, Speed+50);
}


void stopCar() {
  // Stop both motors
  digitalWrite(MRb, LOW);
  digitalWrite(MRa, LOW);
  analogWrite(ENA, 0);

  digitalWrite(MLb, LOW);
  digitalWrite(MLa, LOW);
  analogWrite(ENB, 0);
}

void turnRight() {
  // Turn right by moving left motor forward and stopping right motor
  digitalWrite(MRb, HIGH);
  digitalWrite(MRa, LOW);
  analogWrite(ENA, Speed);

  digitalWrite(MLb, LOW);
  digitalWrite(MLa, LOW);
  analogWrite(ENB, 0);
}

void turnLeft() {
  // Turn left by moving right motor forward and stopping left motor
  digitalWrite(MRb, LOW);
  digitalWrite(MRa, LOW);
  analogWrite(ENA, 0);

  digitalWrite(MLb, HIGH);
  digitalWrite(MLa, LOW);
  analogWrite(ENB,Speed+50);
}
