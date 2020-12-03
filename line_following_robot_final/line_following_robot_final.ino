//Motor variables
#define EnA 10
#define EnB 5
#define In1 8
#define In2 9
#define In3 6
#define In4 7
#define delay_short 200

//IR variables
const int IR_L_1 = A0; // Sensor output voltage
const int IR_L_2 = A1; // Sensor output voltage
const int IR_L_3 = A2; // Sensor output voltage
const int IR_L_4 = A3; // Sensor output voltage
const int IR_L_5 = A4; // Sensor output voltage

 
 
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
  
  //All IR sensor pins only recive input from the sensor
  //IR_L_# stands for #th sensor from the left(robot facing away from user)
  pinMode(IR_L_1, INPUT);
  pinMode(IR_L_2, INPUT);
  pinMode(IR_L_3, INPUT);
  pinMode(IR_L_4, INPUT);
  pinMode(IR_L_5, INPUT);
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
