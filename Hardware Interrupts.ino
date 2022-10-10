
void EncoderRotate1()
{ 
  // cli();
  // if(digitalRead(encoderButton1) == LOW)
  // {
  //   //Serial.println("Button Press ISR");
  // }
  encoderAcurrentState1 = digitalRead(encoderA1);

  if((encoderApreviousState1 == LOW) && (encoderAcurrentState1 == HIGH))
  {
      if(digitalRead(encoderB1) == HIGH)
      {
        routineDelay = routineDelay + 10;
      } 
      else
      {
        if(routineDelay > 100)
        {
          routineDelay = routineDelay - 10;
        }
      }

      // Serial.println(routineDelay);
  } 

  encoderApreviousState1 = encoderAcurrentState1;
//  delay(10);
    // sei();
  updateLCD = HIGH;
}

void EncoderRotate2()
{
  encoderAcurrentState2 = digitalRead(encoderA2);
  if((encoderApreviousState2 == LOW) && (encoderAcurrentState2 == HIGH)) 
  { 
    if(digitalRead(encoderB2) == LOW)
    {
      if(jugglerConfig == 1)
      {
        angleOffset1 = angleOffset1 + stepAngle;
      }

      if(jugglerConfig == 2)
      {
        velocityOffset1 = velocityOffset1 + 1;
      }

      if(jugglerConfig == 3)
      {
        angleOffset2 = angleOffset2 + stepAngle;
      }

      if(jugglerConfig == 4)
      {
        velocityOffset2 = velocityOffset2 + 1;
      }

      if(jugglerConfig == 5)
      {
        jugglerConfigSubMode5 = jugglerConfigSubMode5 +1;
        
        if(jugglerConfigSubMode5 > 5)
        {
          jugglerConfigSubMode5 = 1;
        }
      }

      if(jugglerConfig == 6)
      {       
        if(flightTime < 999)
        {
          flightTime = flightTime + 1;
        }
      }

      if(jugglerConfig == 7)
      {       
        if(flightDistance < 462)
        {
          flightDistance = flightDistance + 1;
        }
      }

      if(jugglerConfig == 8)
      {
        jugglerConfigSubMode8 = jugglerConfigSubMode8 +1;
        
        if(jugglerConfigSubMode8 > 2)
        {
          jugglerConfigSubMode8 = 1;
        }
      }

      if(jugglerConfig == 9)
      {
        if(juggleCount < 99)
        {
          juggleCount = juggleCount + 1;
        }
      }
    }
    else
    {
      if(jugglerConfig == 1)
      {
        angleOffset1 = angleOffset1 - stepAngle;
      }

      if(jugglerConfig == 2)
      {
        velocityOffset1 = velocityOffset1 - 1;
      }

      if(jugglerConfig == 3)
      {
        angleOffset2 = angleOffset2 - stepAngle;
      }

      if(jugglerConfig == 4)
      {
        velocityOffset2 = velocityOffset2 - 1;
      }

      if(jugglerConfig == 5)
      {
        jugglerConfigSubMode5 = jugglerConfigSubMode5 -1;
        
        if(jugglerConfigSubMode5 <= 0)
        {
          jugglerConfigSubMode5 = 5;
        }
      }

      if(jugglerConfig == 6)
      {       
        if(flightTime > 1)
        {
          flightTime = flightTime - 1;
        }
      }

      if(jugglerConfig == 7)
      {       
        if(flightDistance > 1)
        {
          flightDistance = flightDistance - 1;
        }
      }

      if(jugglerConfig == 8)
      {
        jugglerConfigSubMode8 = jugglerConfigSubMode8 - 1;
        
        if(jugglerConfigSubMode8 < 1)
        {
          jugglerConfigSubMode8 = 2;
        }
      }

      if(jugglerConfig == 9)
      {
        if(juggleCount > -1)
        {
          juggleCount = juggleCount - 1;
        }
      }
    }
  }
  encoderApreviousState2 = encoderAcurrentState2;
  updateLCD = HIGH;
}

void EncoderButton1()
{
  if(juggle == true)
  {
    juggle = false; // Stop Juggling
    EncoderButton1Interrupts = false;
    detachInterrupt(digitalPinToInterrupt(encoderButton1));
    // Serial.println("Stop");
    // delay(100);
  }
  else
  {
    juggle = true; // Start Juggling
    EncoderButton1Interrupts = false;
    detachInterrupt(digitalPinToInterrupt(encoderButton1));
    settleTime = millis() + 300;
    // Serial.println("Start");
    // delay(100);
  }
  
}

void  Estop()
{
  Serial.println("Stop");
  juggle = false;
  steps1 = 0;
  steps2 = 0;
  digitalWrite(enable1,disable);
  digitalWrite(enable2,disable);
  stopMotors = HIGH;
  detachInterrupt(digitalPinToInterrupt(encoderButton1));
  updateLCD = HIGH;
  //lcd.setCursor(2,5);
  //lcd.print("Motors Disabled");
}