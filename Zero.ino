void zero()
{
  // stepsToZero1 = -150;
  // stepsToZero1 = -150;
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

  while(zero1 == HIGH || zero2 == HIGH)
  {
    if(digitalRead(limit1) == HIGH && steps1 == 0 && zero1 == HIGH)
    {
      steps1 = 1;
    }

    if(digitalRead(limit1) == LOW)
    {
      zero1 = LOW;
      currentAngle1 = zeroAngle1;
    }

    if(digitalRead(limit2) == HIGH && steps2 == 0 && zero2 == HIGH) 
    {
      steps2 = 1;
    } 

    if(digitalRead(limit2) == LOW)
    {
      zero2 = LOW;
      currentAngle2 = zeroAngle2;
    }
  }

  MOTOR1_INTERRUPTS_OFF;
  MOTOR2_INTERRUPTS_OFF;
}
