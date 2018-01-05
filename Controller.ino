/*
  *Programmer: Cole Davis 
  *Date: 12-23-2017
  *Purpose: Spin four motors appropriate directions with RF Radios, one motor driver, and a breadboard
*/



//Arduino's input pin from rc receiver
const int channel1_pin = 12;
const int channel2_pin = 7; 


/*=====================
        CONSTANTS 
 ======================*/
//Input pins on L298N (change direction and add PWM)
const int inp1_pin = 3;
const int inp2_pin = 9;
const int inp3_pin = 11;
const int inp4_pin = 10;

//SPEED constants (PWM duty cycle out of 255)
const int SPEED_LOW = 100;
const int SPEED_MID = 160;
const int SPEED_HIGH = 225; 

//Serial Range Constants (number recieved from reciever) These constants may need adjustment if there's too much or not enough sensitivity on the controller
const int SERIAL_LOW = 17950;
const int SERIAL_MID_MIN = 18205;
const int SERIAL_MID_MAX = 18595;
const int SERIAL_HIGH = 18850;  


/*=====================
       VARIABLES 
 ======================*/
//Channel vals
int channel1_val = 0;
int channel2_val = 0;

//Bools that are set true when transmitter joysticks are in a certain position
bool North = false;
bool East = false;
bool South = false;
bool West = false;

//Speed variable that will be set to SPEED_X constant (under what condition? Should I have a "Supersonic" mode using one of the aux buttons?"
//I think it would be nice to make a function that takes in the raw serial value and performs calculations that return a number within the range 
//of SPEED_LOW and SPEED_HIGH so BERTHA would have very specific speed control.
int velocity;






void setup() {
  //Sets serial printing rate
  Serial.begin(9600);  

  /*=====================
    PINMODE ASSIGNMENT
   ======================*/
  //Arduino takes input from reciever on these pins
  pinMode(channel1_pin, INPUT);
  pinMode(channel2_pin, INPUT);

  //Used for PWM and Wheel direction/movement
  pinMode(inp1_pin, OUTPUT);
  pinMode(inp2_pin, OUTPUT);
  pinMode(inp3_pin, OUTPUT);
  pinMode(inp4_pin, OUTPUT);
  

  /*=====================
      PIN INITIAL STATES
   ======================*/
  //Motors start with no movement
  analogWrite(inp1_pin, 0);
  analogWrite(inp2_pin, 0);
  analogWrite(inp3_pin, 0);
  analogWrite(inp4_pin, 0);
}



void loop() {
  /*==========================
    GET RECEIVER SERIAL INPUT
  ============================*/
  channel1_val = pulseIn(channel1_pin, INPUT);
  channel2_val = pulseIn(channel2_pin, INPUT); 
  Serial.print("U-D: ");
  Serial.print(channel2_val);
  Serial.println();
  Serial.print("L-R: ");
  Serial.print(channel1_val);
  Serial.println();
  Serial.println();


  /*==========================================
        DERIVE DIRECTION FROM SERIAL INPUT
   ===========================================*/
  if(channel2_val < SERIAL_MID_MIN && channel2_val > 0)
    North = true;
  else
    North = false;
    
  if(channel1_val < SERIAL_MID_MIN && channel1_val > 0)
    East = true;
  else
    East = false;
    
  if(channel2_val > SERIAL_MID_MAX)
    South = true;
  else 
    South = false;

  if(channel1_val > SERIAL_MID_MAX)
    West = true;
  else
    West = false;

   
  /*=====================
      MOVE THE MOTORS 
   ======================*/
   if(North && East){
    Serial.print("NORTHEAST");
    Serial.println();
    //Left Tires
    analogWrite(inp1_pin, SPEED_LOW); 
    analogWrite(inp2_pin, 0);   
    
    //Right Tires
    analogWrite(inp3_pin, SPEED_HIGH); 
    analogWrite(inp4_pin, 0);         
   }
   
   else if(North && West){
    Serial.print("NORTHWEST");
    Serial.println();
    //Left Tires
    analogWrite(inp1_pin, SPEED_HIGH); 
    analogWrite(inp2_pin, 0);   
    
    //Right Tires
    analogWrite(inp3_pin, SPEED_LOW); 
    analogWrite(inp4_pin, 0);
   }

   else if(South && West){
    Serial.print("SOUTHWEST");
    Serial.println();
    //Left Tires
    analogWrite(inp1_pin, 0); 
    analogWrite(inp2_pin, SPEED_HIGH);   
    
    //Right Tires
    analogWrite(inp3_pin, 0); 
    analogWrite(inp4_pin, SPEED_LOW);
   }

   else if(South && East){
    Serial.print("SOUTHEAST");
    Serial.println();
    //Left Tires
    analogWrite(inp1_pin, 0); 
    analogWrite(inp2_pin, SPEED_LOW);   
    
    //Right Tires
    analogWrite(inp3_pin, 0); 
    analogWrite(inp4_pin, SPEED_HIGH);
   }

   else if(North){
    Serial.print("NORTH");
    Serial.println();
    
    //Left Tires
    analogWrite(inp1_pin, SPEED_HIGH); 
    analogWrite(inp2_pin, 0);   
    
    //Right Tires
    analogWrite(inp3_pin, SPEED_HIGH); 
    analogWrite(inp4_pin, 0);
   }

   else if(East){
    Serial.print("EAST");   
    Serial.println();
//
//    //Left Tires
//    analogWrite(inp1_pin, SPEED_HIGH); 
//    analogWrite(inp2_pin, 0);   
//    
//    //Right Tires
//    analogWrite(inp3_pin, 0); 
//    analogWrite(inp4_pin, 0);
   }

   else if(South){
    Serial.print("SOUTH");
    Serial.println();
    
    //Left Tires
    analogWrite(inp1_pin, 0); 
    analogWrite(inp2_pin, SPEED_HIGH);   
    
    //Right Tires
    analogWrite(inp3_pin, 0); 
    analogWrite(inp4_pin, SPEED_HIGH);
   }

   else if(West){
    Serial.print("WEST");
    Serial.println();

//    //Left Tires
//    analogWrite(inp1_pin, 0); 
//    analogWrite(inp2_pin, SPEED_HIGH);   
//    
//    //Right Tires
//    analogWrite(inp3_pin, 0); 
//    analogWrite(inp4_pin, 0);
   }

   else{
    Serial.print("STOPPED");
    Serial.println();

    analogWrite(inp1_pin, 0);
    analogWrite(inp2_pin, 0);
    analogWrite(inp3_pin, 0);
    analogWrite(inp4_pin, 0);
   }
}
