//Motor Connections
//Change this if you wish to use another diagram
#define EnA 10
#define EnB 5
#define In1 8
#define In2 9
#define In3 6
#define In4 7
#define delay_short 200
 
 
void setup()
{
  // All motor control pins are outputs
  Serial.begin(9600);
  pinMode(EnA, OUTPUT);
  pinMode(EnB, OUTPUT);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
}

void goStraight()   //run both motors in the same direction
{
  // turn on motor A
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  // set speed to 150 out 255
  analogWrite(EnA, 200);
  // turn on motor B
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  // set speed to 150 out 255
  analogWrite(EnB, 200);
}

void offMotor()
{
  // now turn off motors
  digitalWrite(In1, LOW);
  Serial.print("In1: OFF");
  digitalWrite(In2, LOW);  
  Serial.print("In2: OFF");
  digitalWrite(In3, LOW);
  Serial.print("In3: OFF");
  digitalWrite(In4, LOW);
  Serial.print("In4: OFF\n");
}

void goRight()   //run right motor forward, and left motor backward
{
  // turn on motor A
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  // set speed to 150 out 255
  analogWrite(EnA, 200);
  // turn on motor B
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  // set speed to 150 out 255
  analogWrite(EnB, 200);
}

void goLeft()   //run right motor forward, and left motor backward
{
  // turn on motor A
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  // set speed to 150 out 255
  analogWrite(EnA, 200);
  // turn on motor B
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  // set speed to 150 out 255
  analogWrite(EnB, 200);
}

void goReverse()
{
  //Turn on motor A reverse
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  //Turn on Motor B reverse
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
}

void loop()
{
  goReverse();
  Serial.print("right\n");
  delay(1000);
  offMotor();
  Serial.print("off\n");
  delay(500);
}
