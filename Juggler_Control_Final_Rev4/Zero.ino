void zero() // Zeros both stepper motors and count the steps needed to see if any stpes have been skipped
{
  double stepsToZero1 = 0;
  double stepsToZero2 = 0;
  double angleError1 = currentAngle1;
  double angleError2 = currentAngle2;

  // Serial.println((String) "Current Angle:" + angleError1);
  // Serial.println((String) "Current Angle:" + angleError2);

  OCR3A = 1000;
  OCR4A = 1000;
  digitalWrite(dir1,up1);
  digitalWrite(dir2,up2);

  MOTOR1_INTERRUPTS_ON;
  MOTOR2_INTERRUPTS_ON;
  
  if(startUp == HIGH)
  {
    for(int x = 0; x<150; x++)
    {
      steps1 = steps2 = 1;
      MOTOR1_INTERRUPTS_ON;
      MOTOR2_INTERRUPTS_ON;
      delay(2);
    }
    startUp = LOW;
    delay(500);
  }

  digitalWrite(dir1,down1);
  digitalWrite(dir2,down2);

  while((zero1 == HIGH || zero2 == HIGH) && stepsToZero1 < 225 && stepsToZero2 < 225)
  {
    if(digitalRead(limit1) == HIGH && steps1 == 0 && zero1 == HIGH)
    {
      steps1 = 1;
      stepsToZero1 = stepsToZero1 + stepAngle;
    }

    if(digitalRead(limit1) == LOW)
    {
      zero1 = LOW;
      currentAngle1 = zeroAngle1;
    }

    if(digitalRead(limit2) == HIGH && steps2 == 0 && zero2 == HIGH) 
    {
      steps2 = 1;
      stepsToZero2 = stepsToZero2 + stepAngle;
    } 

    if(digitalRead(limit2) == LOW)
    {
      zero2 = LOW;
      currentAngle2 = zeroAngle2;
    }
  }

  if(stepsToZero1 > 225 || stepsToZero2 > 225) //This stops the motors if they havent hit a limit switch in 225° this 
  {                                            // is for safety reasons
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.write("Limit switch");
    lcd.setCursor(4,1);
    lcd.write("Malfunction");
    lcd.setCursor(0,2);
    lcd.write("Reset juggler and");
    lcd.setCursor(0,3);
    lcd.write("chek limit switches");
    digitalWrite(enable1,disable);
    digitalWrite(enable2,disable);
    while(1);
  }
  angleError1 = angleError1 - stepsToZero1 - zeroAngle1;
  angleError2 = angleError2 - stepsToZero2 - zeroAngle2;
  // Serial.println((String) "Offset1:" + angleError1);
  // Serial.println((String) "Offset2:" + angleError2);

  MOTOR1_INTERRUPTS_OFF;
  MOTOR2_INTERRUPTS_OFF;
}
