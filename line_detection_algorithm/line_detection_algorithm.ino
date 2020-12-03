const int IR_L_1 = A0; // Sensor output voltage
const int IR_L_2 = A1; // Sensor output voltage
const int IR_L_3 = A2; // Sensor output voltage
const int IR_L_4 = A3; // Sensor output voltage
const int IR_L_5 = A4; // Sensor output voltage
int IR_L_output[5] = {IR_L_1, IR_L_2, IR_L_3, IR_L_4, IR_L_5}; //Convinient access to output pins

bool IR_state[5] = {true, true, true, true, true};

void setup()
{
  Serial.begin(9600);
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

void loop()
{

  Serial.println(IR_state[1]);
  Serial.println();
  IR_update();
  
}
