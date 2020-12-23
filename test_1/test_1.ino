/******************************************************************************
  QRD1114_Proximity_Example.ino
  Example sketch for SparkFun's QRD1114 Reflectance Proximity Sensor
  (https://www.sparkfun.com/products/246)
  Jim Lindblom @ SparkFun Electronics
  May 2, 2016

  Connect a QRD1114, 330 resistor and 10k resistor as follows:

  QRD1114 Pin ---- Arduino ---- Resistors
    1              A0      10k Pull-up to 5V
    2              GND
    3                      330 Resistor to 5V
    4              GND

  As an object comes closer to the QRD1114, the voltage on A0 should go down.

  Development environment specifics:
  Arduino 1.6.7
******************************************************************************/
#define IR_sensitivity 2 //White detected below this value, black detected above thi value

int bigTurnDirection = 2; //Specifies direction to turn if middle sensors cannot be used. 0 - go_straight; 1 - turns right; 2 - turns left;

//delay long enought blackline re-detect the b
#define shortDelay 75

#define motorSpeedFast 250
#define motorSpeedSlow 200

const int IR_L_1 = A0; // Sensor output voltage
const int IR_L_2 = A1; // Sensor output voltage
const int IR_L_3 = A2; // Sensor output voltage
const int IR_L_4 = A3; // Sensor output voltage
const int IR_L_5 = A4; // Sensor output voltage
int IR_L_output[5] = {IR_L_1, IR_L_2, IR_L_3, IR_L_4, IR_L_5}; //Convinient access to output pins

//Motor pin variables
#define EnA 5
#define EnB 10
#define In1 8
#define In2 9
#define In3 6
#define In4 7
#define delay_short 200

bool IR_state[5] = {true, true, true, true, true};
bool IR_previous_state[5] = {true, true, true, true, true};

bool alternator = false; //Variable for checking left and right alternate state when needed. true = move right; false = move left;

int movementState = 1; //State of previous movement; 0 is straight; 1 is reverse; 2 is left; 3 is right;
bool oppositeDirectionOnChecker = false;


void setup()
{
  Serial.begin(9600);
  pinMode(IR_L_1, INPUT);
  pinMode(IR_L_2, INPUT);
  pinMode(IR_L_3, INPUT);
  pinMode(IR_L_4, INPUT);
  pinMode(IR_L_5, INPUT);

  // All motor control pins are outputs
  pinMode(EnA, OUTPUT);
  pinMode(EnB, OUTPUT);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);

}

float IR_read(int IR_number) // Reads IR sensor in analog and returns after scaling the reading to 0-5V range
{
  //read appropriate analog val
  int IR_analog = analogRead(IR_L_output[IR_number]);
  //convert to digital
  float IR_V = (float)IR_analog * 5.0 / 1023.0;
  //return digital reading
  return (IR_V);
}

void IR_update()
{
  //if any IR sensor is on, update its state
  for (int i = 0; i < 5; i++)
    if (IR_read(i) > IR_sensitivity)
    {
      IR_state[i] = true;
    }
    else
    {
      IR_state[i] = false;
    }
}

void goStraight()   //run both motors in the same direction
{
  // turn on motor A
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  // set speed to 150 out 255
  analogWrite(EnA, motorSpeedFast);
  // turn on motor B
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  // set speed to 150 out 255
  analogWrite(EnB, motorSpeedFast);
  movementState = 0;
  Serial.println("Straight");
}

void offMotor()
{
  delay(5);
  // now turn off motors
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
  Serial.println("OFF motor");
}

void goLeft()   //run right motor forward, and left motor backward
{
  // turn on motor A
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  // set speed to 150 out 255
  analogWrite(EnA, motorSpeedFast);
  // turn on motor B
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  // set speed to 150 out 255
  analogWrite(EnB, motorSpeedSlow);
  movementState = 3;
  Serial.println("Left");
}


void goLeftNoRotation()   //run right motor forward, and left motor backward
{
  // turn on motor A
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  // set speed to 150 out 255
  analogWrite(EnA, motorSpeedFast);
  // turn on motor B
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
  // set speed to 150 out 255
  analogWrite(EnB, motorSpeedSlow);
  movementState = 3;
  Serial.println("Left - No rotation");
}

void goRight()   //run right motor forward, and left motor backward
{
  // turn on motor A
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  // set speed to 150 out 255
  analogWrite(EnA, motorSpeedSlow);
  // turn on motor B
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  // set speed to 150 out 255
  analogWrite(EnB, motorSpeedFast);
  movementState = 2;
  Serial.println("Right");
}

void goRightNoRotation()   //run right motor forward, and left motor backward
{
  // turn on motor A
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  // set speed to 150 out 255
  analogWrite(EnA, motorSpeedSlow);
  // turn on motor B
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  // set speed to 150 out 255
  analogWrite(EnB, motorSpeedFast);
  movementState = 2;
  Serial.println("Right - No rotation");
}

void goReverse()
{
  //Turn on motor A reverse
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  //Turn on Motor B reverse
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  movementState = 1;
  Serial.println("Reverse");
}

void goOppositeDirection()
  {
    if(oppositeDirectionOnChecker == 0)
    {
      if(movementState == 0)
      {
        goReverse();
      }
      else if(movementState == 1)
      {
        goStraight();
      }
      else if(movementState == 2)
      {
        goRight();
      }
      else if(movementState == 3)
      {
        goLeft();
      }
      oppositeDirectionOnChecker == 1;
    }
  }

void whiteLineAlgorithm()
{
  while(IR_state[0] == false || IR_state[4] == false)
  {
    goReverse();
  }
  offMotor();
  if(IR_state[0] == true)
  {
    while(IR_state[2] == false)
    {
      IR_update();
      goRight();
    }
  }
  else if(IR_state[4] = true)
  {
    while(IR_state[2] == false)
    {
      IR_update();
      goLeft();
    }
  }
  else
  {
    offMotor();
  }
}

void bigTurn()
{
  
  if(bigTurnDirection == 0)
  {        
    goStraight();
    IR_update();
  }
  else if(bigTurnDirection == 1)
  {
    while(IR_state[2] != true)
    {
      goRight();
      IR_update();
    }
    while(IR_state[1] != 0)
    {
      goStraight();
      IR_update();
    }
    while(IR_state[2] != true)
    {
      goLeft();
      IR_update();
    }
  }
  else if(bigTurnDirection == 2)
  {
    while(IR_state[2] != true)
    {
      goLeft();
      IR_update();
    }
    while(IR_state[3] != 0)
    {
      goStraight();
      IR_update();
    }
    while(IR_state[2] != true)
    {
      goRight();
      IR_update();
    }  
  }  
}
void edgeSensorChecker() //saves instruction for the preffered direction to move in, incase of not being able to use the middle sensors. 0 goes straight; 1 go right; 2 go left;
  {
    if(IR_state[0] == true || IR_state[4] == true)
    {
      if(IR_state[0]== true && IR_state[4] == false)
      {
        bigTurnDirection = 2;
        Serial.println("Big turn direction chaged- Left");
      }
      else if(IR_state[0] == false && IR_state[4] == true)
      {
        bigTurnDirection = 1;
        Serial.println("Big turn direction changed- Right");
      }
      else if(IR_state[0] == true && IR_state[4] == true)
      {
        bigTurnDirection = 0;    
        Serial.println("Big turn direction changed - Straight");
      }
    }
    else
    {
      Serial.print(" Big turn direction - No change. Direction - ");
      Serial.println(bigTurnDirection);
    }
  }

void movement_algo()
{
  // * could increase effciency by adding a state variable for if any change occurs in IR state
  // Other algo could work perhaps using just one sensor to move along the line and switching to whichever side seems more convinient
  // maybe try seperate rotate and turn variables
  // You could create completely seperate loop for separate states
  if (IR_state[2] == true) //if middle sensor is on
  {
    goStraight();
  }
  else
  {
    if (IR_state[1] == true && IR_state[3] == true)
    {
      goStraight();
    }
    else if (IR_state[1] == false && IR_state[3] == true)
    {
      goRight();
    }
    else if (IR_state[1] == true && IR_state[3] == false)
    {
      goLeft();
    }
    else //goes straight for a bit to check if it can find the black line for some time and only goes to bigTurn() if unsucessful
    {
      unsigned long start_time = millis();
      int time_current = 0;
      goStraight();
      while(time_current <= 150)
      {
        IR_update();
        if(IR_state[1] == true || IR_state[2] == true || IR_state[3] == true)
        {
          break;
        }
        time_current = millis()- start_time;
      }
      
      start_time = millis();
      time_current = 0;
      goReverse();
      while(time_current <= 200)
      {
        IR_update();
        if(IR_state[1] == true || IR_state[2] == true || IR_state[3] == true)
        {
          break;
        }
        time_current = millis()- start_time;
      }
      if(IR_state[1] == false && IR_state[2] == false && IR_state[3] == false)
      {
        scanSurroundings();
        bigTurn(); //to handle accute angles when necessary
      }
    }
  }
}

void scanSurroundings() //Returns directions available. Moves to the right and then to the left by short, fixed ammounts to detect lines on the right and on the left to make more accurate local decisions to avoid unnecessary big turns.
{
  bool rightOn = false;
  bool leftOn = false;
  //spin right, detect right
  unsigned long start_time = millis();
  int time_current = 0;
  while(time_current <= 450)
    {
      goRight();
      IR_update();
      //record right
      if(IR_state[3] == true)
      {
        rightOn = true;
        break;
      }
      time_current = millis()- start_time;
    }
    offMotor();
  //spin left, detect left
  start_time = millis();
  time_current = 0;
  while(time_current <= 600)//Left motor rotates quite a bit more that the right on
  {
    goLeft();
    IR_update();
    //record left
    if(IR_state[1] == true)
    {
      leftOn = true;
      break;
    }
    time_current = millis()- start_time;
  }
  start_time = millis();
  time_current = 0;
  while(time_current <= 450)
  {
    goRight();
    time_current = millis()- start_time;
  }
  offMotor();
  if(leftOn == true && rightOn == false)
  {
    bigTurnDirection = 2;
  }
  if(leftOn == false && rightOn == true)
  {
    bigTurnDirection = 1;
  }
  if(leftOn == true && rightOn == true)
  {
    bigTurnDirection = 0;
  }
  //return what options for motion are available
}

void loop()
{
  for (int i = 0; i < 5; i++)
  {
    Serial.print(IR_state[i]);
  }
  Serial.println();

  IR_update();
  edgeSensorChecker();
  movement_algo();

  Serial.println();
  //TD create simulation to see if IR sensor cause required movements
}
