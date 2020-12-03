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
const int IR_L_1 = A0; // Sensor output voltage
const int IR_L_2 = A1; // Sensor output voltage
const int IR_L_3 = A2; // Sensor output voltage
const int IR_L_4 = A3; // Sensor output voltage
const int IR_L_5 = A4; // Sensor output voltage
int IR_L_output[5] = {IR_L_1, IR_L_2, IR_L_3, IR_L_4, IR_L_5}; //Convinient access to output pins

//Motor variables
#define EnA 10
#define EnB 5
#define In1 8
#define In2 9
#define In3 6
#define In4 7
#define delay_short 200

bool IR_state[5] = {true, true, true, true, true};
bool IR_previous_state[5] = {true, true, true, true, true};
int revState=false;
unsigned long revStartTime = 0;
int revTime = 0;

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

float IR_read(int IR_number)
{
  //read appropriate analog val
  int IR_analog = analogRead(IR_L_output[IR_number]);
  //convert to digital
  float IR_V = (float)IR_analog * 5.0 / 1023.0;
  //return digital reading
  return(IR_V);
}

void IR_update()
{
  //if any IR sensor is on, update its state
  for(int i=0; i<5; i++)
  if(IR_read(i) > 0.5)
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

void movement_algo()
{
  // * could increase effciency by adding a state variable for if any change occurs in IR state
  if(IR_state[2] == true)
  {
    goStraight();
    Serial.println("Straight");
    if(revState == true)
    {
      revState = false;
    }
  }
  else if(IR_state[4] == true)
  {
    goLeft();
    Serial.println("Left");
    if(revState == true)
    {
      revState = false;
    }    
  }
  else if(IR_state[0] == true)
  {
    goRight();
    Serial.println("Right");
    if(revState == true)
    {
      revState = false;
    }
  }
  else
  {
    goReverse();
    Serial.println("Reverse");
    if(revState == false)
      {
        revState = true;
        revStartTime = millis();
        Serial.print("millis() that resets revStartTime");
        Serial.println(millis());
        Serial.print("revStartTime reseted");
        Serial.println(revStartTime);
      }
    if(revState == true)
    {
      revTime = millis() - revStartTime;
      Serial.print("millis()");
      Serial.println(millis());
      Serial.print("revStartTime");
      Serial.println(revStartTime);
      Serial.print("RevTime");
      Serial.println(revTime);
      if(revTime > 300)
      {
        goStraight();
        if(revTime>650)
        {
          revState == false;
        }
      }
    }
  }
}


void loop() 
{
  for(int i=0; i<5; i++)
  {
    Serial.print(IR_state[i]);
  }
  Serial.println();
  
  IR_update();
  movement_algo();
  
  //TD create simulation to see if IR sensor cause required movements
}
