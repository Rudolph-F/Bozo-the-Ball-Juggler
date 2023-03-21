#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>
#include <EEPROM.h>

const int en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
const int i2c_addr = 0x3F;//0x27

LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

volatile bool stepState1 = LOW;  // Current state of step pin
volatile bool stepState2 = LOW;  // current state of step pin

bool up1 = HIGH;
bool up2 = HIGH;

bool down1 = LOW;
bool down2 = LOW;

bool enable = HIGH;
bool disable = LOW;

bool zero1 = HIGH;
bool zero2 = HIGH;

bool launch1 = HIGH;
bool launch2 = LOW;

bool updateLCD = HIGH;

volatile bool accel1 = LOW;
volatile bool accel2 = LOW;

volatile bool move1 = LOW;
volatile bool move2 = LOW;

bool startUp = HIGH;
bool routineStartUp = HIGH;

bool juggle = false;
bool EncoderButton1Interrupts = true;
bool doubleBall = false;

int adjustMode = 1; // 1-> adjustAngle1  2 -> adjustVelocity1  3-> adjustAngle2  4 -> adjustVelocity2 
int jugglerConfig = 5; // 1-> Select Juggle mode 2 -> Set Flight time 3 -> set Flight distance 4-> Auto/Manual
int jugglerConfigSubMode5 = 1; 
int jugglerConfigSubMode8 = 2; 
int ballPosition = 1;

int juggleCount = 1;

volatile bool encoderAcurrentState1 = 0;
volatile bool encoderApreviousState1 = encoderAcurrentState1;

volatile bool encoderAcurrentState2 = 0;
volatile bool encoderApreviousState2 = encoderAcurrentState2;

bool shortPress1 = LOW;
bool longPress1 = LOW;

bool shortPress2 = LOW;
bool longPress2 = LOW;

bool stopMotors = LOW;

bool juggleInf = LOW;
long settleTime = 0;
int routineDelay = 500;

// #define step1 PG5 //D4 Port G pins 0 - 7
// #define step2 PH5 //D8 Port H pins 8 - 13

#define dir1 5
#define dir2 9

#define enable1 6  // Low to enable stepper motor drivers
#define enable2 10 // Low to enable stepper motor drivers

#define limit1 7
#define limit2 11

#define button 14
#define encoderButton1 19 // Start/Stop Encoder
#define encoderA1 12  //Output A of Start/Stop Encoder
#define encoderB1 2   //Output B of Start/Stop Encoder

#define encoderButton2 A0 // Select Encoder
#define encoderA2 17   //Output A of Select Encoder
#define encoderB2 18  // Output B of Select Encoder

#define eStop 3

#define MOTOR1_INTERRUPTS_ON    TIMSK3 |=  (1 << OCIE3A); 
#define MOTOR1_INTERRUPTS_OFF   TIMSK3 &= ~(1 << OCIE3A);

#define MOTOR2_INTERRUPTS_ON    TIMSK4 |=  (1 << OCIE4A);
#define MOTOR2_INTERRUPTS_OFF   TIMSK4 &= ~(1 << OCIE4A);

int launchVelocity1 = 140;
int launchVelocity2 = 140;

volatile int desiredVelocity1 = launchVelocity1; // Velocity of motor 1
volatile int desiredVelocity2 = launchVelocity2; // Velocity of motor 2

int unloadVelocity1 = 189;
int unloadVelocity2 = 188;
bool adjustUnloadVelocity1 = LOW;
bool adjustUnloadVelocity2 = LOW;


double unloadAngle1 = 97.9875;
double unloadAngle2 = 97.9875;
bool adjustUnloadAngle1 = LOW;
bool adjustUnloadAngle2 = LOW;

volatile float currentVelocity1 = 800; 
volatile float currentVelocity2 = 800;


int stepDelay;
int microStep = 16;
int stepsPerRev = 200;

// int stepsToZero1 =0;
// int stepsToZero2 = 0;

double desiredAngle1;
double desiredAngle2;

volatile double angleOffset1 = 0;
volatile double angleOffset2 = 0;

volatile double horz1AngleOffset1 = 0;
volatile double horz1AngleOffset2 = 0;

volatile double horz2AngleOffset1 = 0;
volatile double horz2AngleOffset2 = 0;

volatile double vert2AngleOffset1 = 0;
volatile double vert2AngleOffset2 = 0;

volatile double vertLAngleOffset1 = 0;
volatile double vertRAngleOffset2 = 0;

volatile double velocityOffset1 = 0;
volatile double velocityOffset2 = 0;

volatile double horz1VelocityOffset1 = 0;
volatile double horz1VelocityOffset2 = 0;

volatile double horz2VelocityOffset1 = 0;
volatile double horz2VelocityOffset2 = 0;

volatile double vert2VelocityOffset1 = 0;
volatile double vert2VelocityOffset2 = 0;

volatile double vertLVelocityOffset1 = 0;
volatile double vertRVelocityOffset2 = 0;

volatile double currentAngle1;
volatile double currentAngle2;

double launchAngle1 = 100.0125; 
double launchAngle2 = 100.0125; 

double catchAngel1 = launchAngle1;
double catchAngel2 = launchAngle2;

double loadAngle = 79.9875+1.8;

double zeroAngle1 = 57.825; //57.825; // Angle of arm 1 when limit switch is pressed
double zeroAngle2 = 58.6125; //58.6125; //Angle of arm 2 when limit switch is pressed
bool adjustZeroAngle1 = LOW;
bool adjustZeroAngle2  = LOW;

volatile signed int steps1; // use volatile for variables changed in other functions 
volatile signed int steps2; // such as interrupt service routines

// volatile int stepCount1 = 0;
// volatile int stepCount2 = 0;

volatile int decelSteps1 = 0;
volatile int decelSteps2 = 0;
int decelSteps = 25;
bool adjustDecelSteps = LOW;

volatile unsigned long tic = 0;

// ------ Trajectory Variables ---------------
double Time = 0.5; //s
int flightTime = 350; //ms
double Dx = 0.36; //m
int flightDistance = 300;
double Dy = 0; //m
double g = 9.81; // m/s^2
volatile double stepAngle = 0.1125; //°
double armLength = 0.2; //m
double TimePtick = 0.000001;
double trajectoryResults[4];
volatile int velocityArray2[1000];
volatile int velocityArray1[1000];

//-------Functions to be used----------------
ISR(TIMER3_COMPA_vect);
ISR(TIMER4_COMPA_vect); 
void zero();
void routine();
void steps_direction();
void trajectory();
void velocityArray();
void moveSteppers();
void EncoderRotate1();
void EncoderRotate2();
void EncoderButton1();
void Estop();
void setIndicator();
void unload1();
void unload2();
void setLCD();
void setIndicator();
void ReadEEPROM();
void WriteEEPROM();
void parameterAdjustment();

int GoForWrite = HIGH;

void setup()
{
  DDRG = B00100000; // Set digital pin 4 to output
  DDRH = B00100000; // Set digital pin 8 to output
  // pinMode(4,OUTPUT);
  pinMode(dir1,OUTPUT);
  pinMode(enable1,OUTPUT);
  // pinMode(8,OUTPUT);
  pinMode(dir2,OUTPUT);
  pinMode(enable2,OUTPUT);
  pinMode(limit1,INPUT_PULLUP);
  pinMode(limit2,INPUT_PULLUP);
  pinMode(button,INPUT_PULLUP); 
  pinMode(encoderButton1,INPUT_PULLUP);
  pinMode(encoderA1,INPUT_PULLUP);
  pinMode(encoderB1,INPUT_PULLUP); 
  pinMode(encoderButton2,INPUT_PULLUP);
  pinMode(encoderA2,INPUT_PULLUP);
  pinMode(encoderB2,INPUT_PULLUP); 
  pinMode(eStop,INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(encoderB1), EncoderRotate1, CHANGE );
  attachInterrupt(digitalPinToInterrupt(encoderB2), EncoderRotate2, CHANGE );
  attachInterrupt(digitalPinToInterrupt(encoderButton1), EncoderButton1, LOW );
  attachInterrupt(digitalPinToInterrupt(eStop), Estop, FALLING );

  digitalWrite(enable1,disable);
  digitalWrite(enable2,disable);

  // PRR1 = B00100000; //Enable timers 3 and 4
  cli(); // Stop interrupts
 
  //----------Timer 3 Setup-----------------------------------------------------  set it to normal mode
  TCCR3A = 0; //PWM register make it zero
  TCCR3B = 0;  // Reset entire timer regester
  TCCR3C = 0;
  TCCR3B |= B00001010; // Set CS32 to 1 to get a prescaler of 8  B00000010 and enable CTC
  TIMSK3 |= B00000010; // Enable compare match A OCR3A
  OCR3A = 2000; //Number of times the timer must tick 0.5µs to pass 
 
  // --------Timer 4 setup ------------------------------------------------------- set it to normal mode
  TCCR4A = 0; //PWM register make it zero
  TCCR4B = 0; // Reset entire timer regester
  TCCR4C = 0;
  TCCR4B |= B00001010; // Set CS42 to 1 to get a prescaler of 8 and enable CTC
  TIMSK4 |= B00000010; // Enable compare match A OCIE4A 
  OCR4A = 2000; //Number of times the timer must tick 0.5 µs
  
  sei(); // Enable interrupts
  
  Serial.begin(115200);
  lcd.begin(20,4);

  if(digitalRead(encoderButton2) == LOW) //if select encoder is pressed 
  {
    parameterAdjustment(); //Call to adjust motor angle offsets
    juggle = false;
  }  
  else
  {
    //WriteEEPROM(); // Call this if the code is upladed for the first time to write 0 to all the necessary EEPROM adresses ONLY DO THIS ONCE
    ReadEEPROM(); // Read saved values from the EEPROM 

    lcd.setCursor(1,0);
    lcd.print("Hello Time to meet");
    lcd.setBacklight(1);
    delay(1500); 

    lcd.setCursor(3,1);
    lcd.write("Bozo The Ball");
    lcd.setCursor(7,2);
    lcd.write("Juggler");

    lcd.setCursor(0,3);
    lcd.write("  (Press any key)");
    while(digitalRead(encoderButton1) == HIGH && digitalRead(encoderButton2) == HIGH);
    juggle = false;
    lcd.clear();

    lcd.setCursor(0,2);
    lcd.write("Press limit switch 1");
    while(digitalRead(limit1) == HIGH);

    lcd.clear();
    lcd.setCursor(0,2);
    lcd.write("Press limit switch 2");
    while(digitalRead(limit2) == HIGH);
    lcd.clear();
    while(digitalRead(limit2) == LOW);    
  }


  lcd.setCursor(4,1);
  lcd.print("Finding Zero");
  lcd.setCursor(6,2);
  lcd.print("Positions");

  digitalWrite(enable1,enable);
  digitalWrite(enable2,enable);

  zero();
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Zero Positions");
  lcd.setCursor(8,1);
  lcd.print("Found");
  delay(500);

  lcd.setCursor(3,3);
  lcd.print("Please Confirm");

  while(digitalRead(encoderButton1) == HIGH && digitalRead(encoderButton2) == HIGH);

  OCR3A = 1500;
  OCR4A = 1500;
  desiredVelocity1 = 1000;
  desiredVelocity2 = 1000;
  desiredAngle1 = 100; 
  desiredAngle2 = 100;
  decelSteps1 = 30;
  decelSteps2 = 30;
  accel1 = HIGH;
  accel2 = HIGH;

  moveSteppers();

  juggle = false;
  lcd.clear();
  trajectory(0.5,0.359); //(Flight time, x distance) 116 µs to execute
  //OCR4A = trajectoryResults[0];
  //launchAngle1 = trajectoryResults[1];
  //digitalWrite(enable2,disable);
  
  Serial.println(horz2AngleOffset1,4);
  Serial.println(vertRVelocityOffset2,4);
  setLCD();
}

void loop()
{

  if(digitalRead(encoderButton1) == HIGH && EncoderButton1Interrupts == false) // Reinitatte interrupts on Start/Stop
  {
      EncoderButton1Interrupts = true;
      attachInterrupt(digitalPinToInterrupt(encoderButton1), EncoderButton1, LOW );
      delay(100);
      // Serial.println("Reinstated Interrupts");
  }

  while(stopMotors == HIGH && updateLCD == LOW) /// This will excecute once the motors are disabled
  {
    if(digitalRead(encoderButton1) == LOW && digitalRead(encoderButton2) == LOW) // Will renable the motors
    {
      GoForWrite = HIGH;
      stopMotors = LOW;
      digitalWrite(enable1,enable);
      digitalWrite(enable2,enable);
      zero1 = HIGH;
      zero2 = HIGH;
      lcd.clear();
      lcd.setCursor(3,1);
      lcd.print("Motors Enabled");

      while(digitalRead(encoderButton1) == LOW || digitalRead(encoderButton2) == LOW);
      delay(1000);
      zero(); 
      currentVelocity1 = 1000;
      currentVelocity2 = 1000;
      OCR3A = currentVelocity1;
      OCR4A = currentVelocity2;
      desiredVelocity1 = 1000;
      desiredVelocity2 = 1000;
      desiredAngle1 = 100; 
      desiredAngle2 = 100;
      decelSteps1 = 30;
      decelSteps2 = 30;
      accel1 = HIGH;
      accel2 = HIGH;

      moveSteppers();
      updateLCD = HIGH;
      attachInterrupt(digitalPinToInterrupt(encoderButton1), EncoderButton1, LOW );
      // attachInterrupt(digitalPinToInterrupt(eStop), Estop, FALLING );
      lcd.clear();
    }

    if(digitalRead(eStop) == LOW) // Used to write to EERPOM can oonly work when motos are disabled
    {
      long Tic = millis();
      while(digitalRead(eStop) == LOW && (millis() - Tic) < 520)
      {      
        if((millis() - Tic) > 500)
        {
          if(GoForWrite == HIGH)
          {
            Serial.println("EEPROM Write");
            GoForWrite = LOW;

            lcd.clear();
            lcd.setCursor(2,1);
            lcd.print("Saving To EEPROM");
            WriteEEPROM(); // Fucntion called that writes to EEPROM
            delay(1000);
          }
          while(digitalRead(eStop) == LOW);
          void setLCD();
        }
      }
    }
  }

  if((millis() - settleTime) > routineDelay && juggle == true  && digitalRead(encoderButton1) == HIGH) // Calls the routine function dpending on the juggling mode Manual/Auto
  {
    if(jugglerConfigSubMode5 == 1 && doubleBall == true)
    {
      routineStartUp = HIGH;
      launch1 = HIGH;
      launch2 = LOW;
      unload2();
      doubleBall = false;
    }

    if(jugglerConfigSubMode5 > 1)
    {
      doubleBall = true; // Two balls in the system
    }

    if(juggleCount > 0)
    {
      routine();
      settleTime = millis();
      juggleCount = juggleCount - 1;
    }
   
    if(jugglerConfigSubMode8 == 2)
    {
      juggleCount = 1;
      juggle = false;
    }

    if(juggleCount == 0)
    {
      juggle = false;
    }

    if(juggleInf == HIGH)
    {
      routine();
      settleTime = millis();
      // juggle = true;
      juggleCount = -1;
    }
  }

 if(digitalRead(encoderButton1) == LOW && digitalRead(encoderButton2) == HIGH) // Start or Stop Juggling Routine or unload
 {
    longPress1 = LOW;
    shortPress1 = LOW;
    long Tic = millis();
    while(digitalRead(encoderButton1) == LOW && (millis() - Tic) < 310)
    {
      if((millis() - Tic) > 300)
      {
        longPress1 = HIGH;
        shortPress1 = LOW;
      }
    }

    if(longPress1 == HIGH)
    {
      juggle = false;
      
      if(doubleBall == false)
      {
        if(ballPosition == 1)
        {
          lcd.clear();
          lcd.setCursor(2,1);
          lcd.print("Unloading Motor1");
          unload1();
        }
        else
        {
          lcd.clear();
          lcd.setCursor(2,1);
          lcd.print("Unloading Motor2");
          unload2();
        }
      }
      else
      {
        lcd.clear();
        lcd.setCursor(2,1);
        lcd.print("Unloading Motor1");
        unload1();

        delay(300);

        lcd.setCursor(2,2);
        lcd.print("Unloading Motor2");
        unload2();
      }

      lcd.clear();
      updateLCD = HIGH;
    }   
 }


  if(digitalRead(encoderButton2) == LOW) // Select parameter to change
  {                                      // Single Press increment
    longPress2 = LOW;                    // Long press decrement parameter to change
    shortPress2 = LOW;
    long Tic = millis();
    while(digitalRead(encoderButton2) == LOW && (millis() - Tic) < 310)
    {
      if((millis() - Tic) > 300)
      {
          longPress2 = HIGH;
          shortPress2 = LOW;
      }
    }

    if(shortPress2 == HIGH || longPress2 == LOW)
    {
      //Serial.println("Short Press");
      shortPress2 = HIGH;
    }

    if(longPress2 == HIGH)
    {
      jugglerConfig = jugglerConfig - 1;

      if(jugglerConfig < 1)
      {
        jugglerConfig = 9;
      }

      if(jugglerConfigSubMode8 == 2 && jugglerConfig == 9)
      {
        jugglerConfig = 8;
      }
    }

    if(shortPress2 == HIGH)
    {
      jugglerConfig = jugglerConfig + 1;

      if(jugglerConfig > 9)
      {
        jugglerConfig = 1;
      }

      if(jugglerConfigSubMode8 == 2 && jugglerConfig == 9)
      {
        jugglerConfig = 1;
      }
    }
    setIndicator(); //Set indicator to new value to be changed

    while(digitalRead(encoderButton2) == LOW)
    {
      delay(100);
    }
    updateLCD = HIGH;
   
  }
  

  if(updateLCD == HIGH) // Call LCD function to update it
  {
    setLCD();
  } 
}
