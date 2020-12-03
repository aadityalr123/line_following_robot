

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

void setup() 
{
  Serial.begin(9600);
  pinMode(IR_L_1, INPUT);
  
  pinMode(IR_L_2, INPUT);
  
  pinMode(IR_L_3, INPUT);
  
  pinMode(IR_L_4, INPUT);
  
  pinMode(IR_L_5, INPUT);
}

void loop() 
{
  // Read in the ADC and convert it to a voltage:
  int analog_IR_L_1 = analogRead(IR_L_1);
  float V_IR_L_1 = (float)analog_IR_L_1 * 5.0 / 1023.0;
  Serial.println(V_IR_L_1);
  
    // Read in the ADC and convert it to a voltage:
  int analog_IR_L_2 = analogRead(IR_L_2);
  float V_IR_L_2 = (float)analog_IR_L_2 * 5.0 / 1023.0;
  Serial.println(V_IR_L_2);
  
  int analog_IR_L_3 = analogRead(IR_L_3);
  float V_IR_L_3 = (float)analog_IR_L_3 * 5.0 / 1023.0;
  Serial.println(V_IR_L_3);
  
  int analog_IR_L_4 = analogRead(IR_L_4);
  float V_IR_L_4 = (float)analog_IR_L_4 * 5.0 / 1023.0;
  Serial.println(V_IR_L_4);
  
  int analog_IR_L_5 = analogRead(IR_L_5);
  float V_IR_L_5 = (float)analog_IR_L_5 * 5.0 / 1023.0;
  Serial.println(V_IR_L_5);
  
  Serial.println();  
  
  delay(100);
}


