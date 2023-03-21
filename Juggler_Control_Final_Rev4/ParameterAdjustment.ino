void parameterAdjustment()
{

  lcd.clear();
  lcd.setCursor(2,1);
  lcd.print("You have entered"); 
  lcd.setCursor(2,2);
  lcd.print("programming mode"); 

  while(digitalRead(encoderButton2) == LOW);

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

  ReadEEPROM();

  digitalWrite(enable1,enable);
  digitalWrite(enable2,enable);

  jugglerConfig = 0;
  jugglerConfigSubMode5 = 0;

  zero1 = HIGH;
  zero2 = HIGH;

  lcd.clear();
  lcd.setCursor(4,1);
  lcd.print("Finding Zero");
  lcd.setCursor(6,2);
  lcd.print("Positions");

  zero();
// ------------Adjust zero angle Offsets----------------
  currentVelocity1 = 1000;
  currentVelocity2 = 1000;
  OCR3A = currentVelocity1;
  OCR4A = currentVelocity2;
  desiredVelocity1 = 1000;
  desiredVelocity2 = 1000;
  desiredAngle1 = 90; 
  desiredAngle2 = 90;
  decelSteps1 = 30;
  decelSteps2 = 30;
  accel1 = HIGH;
  accel2 = HIGH;

  moveSteppers();

  MOTOR1_INTERRUPTS_ON;
  MOTOR2_INTERRUPTS_ON;

  lcd.clear();
  adjustZeroAngle1 = HIGH;
  adjustZeroAngle2 = LOW;

  lcd.setCursor(0,1);
  lcd.print("Zero Angle 1:");

  while (digitalRead(encoderButton2) == HIGH) //rotate encoder button 1 to adjust arm angle
  {
    if(updateLCD == HIGH) // LCD function to update it once the angle has been changed
    {
      lcd.setCursor(13,1);
      lcd.print(zeroAngle1,4);
      updateLCD = LOW;
    } 
  }

  while (digitalRead(encoderButton2) == LOW);

  adjustZeroAngle1 = LOW;
  adjustZeroAngle2 = HIGH;
  
  lcd.setCursor(0,1);
  lcd.print("Zero Angle 2:");

  while (digitalRead(encoderButton2) == HIGH) //rotate encoder button 1 to adust arm angle
  {
    if(updateLCD == HIGH) // LCD function to update it once the angle has been changed
    {
      lcd.setCursor(13,1);
      lcd.print(zeroAngle2,4);
      updateLCD = LOW;
    } 
  }

  while (digitalRead(encoderButton2) == LOW);
  lcd.clear();

  adjustZeroAngle1 = LOW;
  adjustZeroAngle2 = LOW;
  //-----Adjust Unload Velocity and angle -------------

  adjustUnloadAngle1 = HIGH;
  lcd.setCursor(0,1);
  lcd.print("Unload Angle 1:");

  updateLCD = HIGH;

  while (digitalRead(encoderButton2) == HIGH) //rotate encoder button 1 to adust arm angle
  {
    if(updateLCD == HIGH) // LCD function to update it once the angle has been changed
    {
      lcd.setCursor(5,2);
      lcd.print(unloadAngle1,4);
      updateLCD = LOW;
    } 

    if(digitalRead(encoderButton1) == LOW)
    {
      unload1();
    }
  }
  adjustUnloadAngle1 = LOW;
  lcd.clear();
  while (digitalRead(encoderButton2) == LOW);
  // -------- Adjust unload velocity 1 ---------------
  adjustUnloadVelocity1 = HIGH;
  lcd.setCursor(0,1);
  lcd.print("Unload Velocity 1:");

  updateLCD = HIGH;

  while (digitalRead(encoderButton2) == HIGH) //rotate encoder button 1 to adust arm angle
  {
    if(updateLCD == HIGH) // LCD function to update it once the angle has been changed
    {
      lcd.setCursor(5,2);
      lcd.print(unloadVelocity1);
      updateLCD = LOW;
    } 

    if(digitalRead(encoderButton1) == LOW)
    {
      unload1();
    }
  }
  adjustUnloadVelocity1 = LOW;

  lcd.clear();
  while (digitalRead(encoderButton2) == LOW);
  
  //-----Adjust unload angle 2--------
  adjustUnloadAngle2 = HIGH;
  lcd.setCursor(0,1);
  lcd.print("Unload Angle 2:");

  updateLCD = HIGH;

  while (digitalRead(encoderButton2) == HIGH) //rotate encoder button 1 to adust arm angle
  {
    if(updateLCD == HIGH) // LCD function to update it once the angle has been changed
    {
      lcd.setCursor(5,2);
      lcd.print(unloadAngle2,4);
      updateLCD = LOW;
    } 

    if(digitalRead(encoderButton1) == LOW)
    {
      unload2();
    }
  }
  adjustUnloadAngle2 = LOW;
  lcd.clear();
  while (digitalRead(encoderButton2) == LOW);
  // -------- Adjust unload velocit 2 ---------------
  adjustUnloadVelocity2 = HIGH;
  lcd.setCursor(0,1);
  lcd.print("Unload Velocity 2:");

  updateLCD = HIGH;

  while (digitalRead(encoderButton2) == HIGH) //rotate encoder button 1 to adust arm angle
  {
    if(updateLCD == HIGH) // LCD function to update it once the angle has been changed
    {
      lcd.setCursor(5,2);
      lcd.print(unloadVelocity2);
      updateLCD = LOW;
    } 

    if(digitalRead(encoderButton1) == LOW)
    {
      unload2();
    }
  }
  adjustUnloadVelocity2 = LOW;

  lcd.clear();
  while (digitalRead(encoderButton2) == LOW);
  
  //----- Adjust Deceleration Steps ------------
  adjustDecelSteps = HIGH;
  lcd.setCursor(0,1);
  lcd.print("Deceleration Steps:");

  updateLCD = HIGH;

  while (digitalRead(encoderButton2) == HIGH) //rotate encoder button 1 to adust arm angle
  {
    if(updateLCD == HIGH) // LCD function to update it once the angle has been changed
    {
      lcd.setCursor(10,2);
      lcd.print(decelSteps);
      updateLCD = LOW;
    } 
  }
  adjustDecelSteps = LOW;

  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Zero angle Vlaues"); 
  lcd.setCursor(0,2);
  lcd.print("updated successfully");
  delay(500);

  while (digitalRead(encoderButton2) == LOW);
  
// ---- Restoring parameters --------
  jugglerConfig = 5;
  jugglerConfigSubMode5 = 1;

  MOTOR1_INTERRUPTS_OFF;
  MOTOR2_INTERRUPTS_OFF;

  zero1 = HIGH;
  zero2 = HIGH;

  WriteEEPROM();

}