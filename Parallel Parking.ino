//Back sensor
#define trigPin1 2
#define echoPin1 3

//Right sensor
#define trigPin2 34 
#define echoPin2 36 

// Motors Speed 
#define S 100

// Motor A

#define enA 9
#define in1 7
#define in2 6

// Motor B

#define enB 8
#define in3 4
#define in4 5

//Buzzer 
#define buzzer 10

int distance;
void setup() {
 //ultra sonic pins
  pinMode(trigPin1,OUTPUT);
  pinMode(echoPin1,INPUT);
  pinMode(trigPin2,OUTPUT);
  pinMode(echoPin2,INPUT);

// Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(buzzer, OUTPUT);
  Serial.begin(9600); // Starts the serial communication

}

//Ultrasonic function
int UFun(int triger , int echo){ 
   long duration ;
   int distance;
        digitalWrite(triger,LOW);
        delayMicroseconds(2);
        digitalWrite(triger, HIGH);
        delayMicroseconds(10);
        digitalWrite(triger,LOW);
    
        duration = pulseIn(echo,HIGH);
        distance = duration/2 /29.1 ;
  return distance; 
  
}
void Stop(){

  // Turnning the motors off
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
}

void MoveForward(){
 {
   // Stop before moving forward to give the right sensor time to search for a parking spot
    Stop();
    delay(5000);
    // Moving forward controls
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enA, S);
    analogWrite(enB, S);
  }

}
void MoveBack() {
  //Move back controls
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enA, S);
    analogWrite(enB, S);
}

void MoveLeft(){

//move left controls
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, S);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, S);
}

void MoveRight(){

//move right controls
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, S);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, S);

}
void loop() {
  delay(2000);
  distance = UFun(trigPin2,echoPin2);
  if(distance<=5){ // if their is a parking space
  //parking controls then exit the loop when the parking is completed 
    MoveBack();
    delay(800);
    Stop();
    delay(1000);
    MoveLeft();
    delay(2000);
    Stop();
    delay(1000);
    while(UFun(trigPin1,echoPin1)>15){
      if(UFun(trigPin1,echoPin1)<25){
          tone(buzzer,450);
          delay(25);
          noTone(buzzer);
          delay(25);
      }
       if(UFun(trigPin1,echoPin1)<20){
          tone(buzzer,450);
          delay(5);
          noTone(buzzer);
          delay(5);
          tone(buzzer,450);
          delay(5);
          noTone(buzzer);
          delay(5);
      }
          delay(100);
          MoveBack();
          delay(100);
          Stop();

    }
    delay(900);
    Stop();
    delay(1000);
    MoveRight();
    delay(1000);
    Stop();
    exit(0);
  }
  else{
  // move forward for 500ms then stop for 1 second to give the sensor sometime to check for a parking spot
    MoveForward();
    delay(500);
    Stop();
    delay(1000);
  }
  delay(5000);

// printing to the serial monitor for debugging
  Serial.print("Right: ");
  Serial.println(distance);

}
