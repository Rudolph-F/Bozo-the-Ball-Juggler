
void EncoderRotate1() // Rotation of Start/Stop encoder
{ 
  encoderAcurrentState1 = digitalRead(encoderA1);

  if((encoderApreviousState1 == LOW) && (encoderAcurrentState1 == HIGH))
  {
      if(digitalRead(encoderB1) == HIGH)
      {
        routineDelay = routineDelay + 10;
      } 
      else
      {
        if(routineDelay > 10)
        {
          routineDelay = routineDelay - 10;
        }
      }
      // Serial.println(routineDelay);
  } 

  encoderApreviousState1 = encoderAcurrentState1;
  updateLCD = HIGH;
}

void EncoderRotate2() //Rotation of Select encoder
{
  encoderAcurrentState2 = digitalRead(encoderA2);
  angleOffset1 = 0;
  velocityOffset1 = 0;
  angleOffset2 = 0;
  velocityOffset2 = 0;

  if((encoderApreviousState2 == LOW) && (encoderAcurrentState2 == HIGH)) 
  { 
    if(digitalRead(encoderB2) == LOW)
    {

      if(jugglerConfig == 0)
      {
        if(adjustZeroAngle1 == HIGH && adjustZeroAngle2 == LOW)
        {
          digitalWrite(dir1,down1);
          delay(1);
          zeroAngle1 = zeroAngle1 + stepAngle; 
          steps1 = 1; 
        }

        if(adjustZeroAngle2 == HIGH && adjustZeroAngle1 == LOW)
        {
          digitalWrite(dir2,down2);
          delay(1);
          zeroAngle2 = zeroAngle2 + stepAngle; 
          steps2 = 1; 
        }

        if(adjustDecelSteps == HIGH)
        {
          decelSteps = decelSteps + 1;
        }

        if(adjustUnloadAngle1 == HIGH && unloadAngle1 < 160)
        {
          unloadAngle1 = unloadAngle1 + stepAngle;
        }

        if(adjustUnloadVelocity1 == HIGH)
        {
          unloadVelocity1 = unloadVelocity1 + 1;
        }

        if(adjustUnloadAngle2 == HIGH && unloadAngle2 < 160)
        {
          unloadAngle2 = unloadAngle2 + stepAngle;
        }

        if(adjustUnloadVelocity2 == HIGH)
        {
          unloadVelocity2 = unloadVelocity2 + 1;
        }

        updateLCD = HIGH;
      }

      if(jugglerConfig == 1) //adjustAngle1
      {
        angleOffset1 = angleOffset1 + stepAngle;
      }

      if(jugglerConfig == 2) //adjustVelocity1
      {
        velocityOffset1 = velocityOffset1 + 1;
      }

      if(jugglerConfig == 3)
      {
        angleOffset2 = angleOffset2 + stepAngle; // adjustAngle2
      }

      if(jugglerConfig == 4) // adjustVelocity2
      {
        velocityOffset2 = velocityOffset2 + 1;
      }

      if(jugglerConfig == 5) // adjustAngle2
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
      if(jugglerConfig == 0)
      {
        if(adjustZeroAngle1 == HIGH && adjustZeroAngle2 == LOW)
        {
          digitalWrite(dir1,up1);
          delay(1);
          zeroAngle1 = zeroAngle1 - stepAngle; 
          steps1 = 1; 
        }

        if(adjustZeroAngle2 == HIGH && adjustZeroAngle1 == LOW)
        {
          digitalWrite(dir2,up2);
          delay(1);
          zeroAngle2 = zeroAngle2 - stepAngle; 
          steps2 = 1; 
        }

        if(adjustDecelSteps == HIGH  && decelSteps > 0)
        {
          decelSteps = decelSteps - 1;
        }

        if(adjustUnloadAngle1 == HIGH  && unloadAngle1 > zeroAngle1)
        {
          unloadAngle1 = unloadAngle1 - stepAngle;
        }

        if(adjustUnloadVelocity1 == HIGH && unloadVelocity1 > 1)
        {
          unloadVelocity1 = unloadVelocity1 - 1;
        }

        if(adjustUnloadAngle2 == HIGH  && unloadAngle2 > zeroAngle2)
        {
          unloadAngle2 = unloadAngle2 - stepAngle;
        }

        if(adjustUnloadVelocity2 == HIGH && unloadVelocity2 > 1)
        {
          unloadVelocity2 = unloadVelocity2 - 1;
        }

          updateLCD = HIGH;
                 
      }

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

  if(jugglerConfigSubMode5 == 1) // Add offset angle and velcotiy to respective routines
  {
    horz1AngleOffset1 = horz1AngleOffset1 + angleOffset1;
    horz1VelocityOffset1 = horz1VelocityOffset1 + velocityOffset1;
    horz1AngleOffset2 = horz1AngleOffset2 + angleOffset2;
    horz1VelocityOffset2 = horz1VelocityOffset2 + velocityOffset2;
  }

  if(jugglerConfigSubMode5 == 2) // Add offset angle and velcotiy to respective routines
  {
    horz2AngleOffset1 = horz2AngleOffset1 + angleOffset1;
    horz2VelocityOffset1 = horz2VelocityOffset1 + velocityOffset1;
    horz2AngleOffset2 = horz2AngleOffset2 + angleOffset2;
    horz2VelocityOffset2 = horz2VelocityOffset2 + velocityOffset2;
  }

  if(jugglerConfigSubMode5 == 3) // Add offset angle and velcotiy to respective routines
  {
    vert2AngleOffset1 = vert2AngleOffset1 + angleOffset1;
    vert2VelocityOffset1 = vert2VelocityOffset1 + velocityOffset1;
    vert2AngleOffset2 = vert2AngleOffset2 + angleOffset2;
    vert2VelocityOffset2 = vert2VelocityOffset2 + velocityOffset2;
  }

  if(jugglerConfigSubMode5 == 4 || jugglerConfigSubMode5 == 5 ) // Add offset angle and velcotiy to respective routines
  {
    vertLAngleOffset1 = vertLAngleOffset1 + angleOffset1;
    vertLVelocityOffset1 = vertLVelocityOffset1 + velocityOffset1;
    vertRAngleOffset2 = vertRAngleOffset2 + angleOffset2;
    vertRVelocityOffset2 = vertRVelocityOffset2 + velocityOffset2;
  }

}

void EncoderButton1() // Start/Stop encoder
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

void Estop() //E STOP button is pressed 
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