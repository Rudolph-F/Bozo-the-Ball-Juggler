void steps_direction()
{
  steps1 = (desiredAngle1 - currentAngle1)/1.8*microStep;
  steps2 = (desiredAngle2 - currentAngle2)/1.8*microStep;

  if(steps1 >= 0)
  {
   digitalWrite(dir1,up1);
   steps1 = steps1 + decelSteps1;
   currentAngle1 = desiredAngle1 + (decelSteps1*stepAngle);
  }
  else
  {
   digitalWrite(dir1,down1);
   steps1 = abs(steps1);
   steps1 = steps1 + decelSteps1;
   currentAngle1 = desiredAngle1 - (decelSteps1*stepAngle);
  }

  if(steps2 >= 0)
  {
   digitalWrite(dir2,up2);
   steps2 = steps2 + decelSteps2;
   currentAngle2 = desiredAngle2 + (decelSteps2*stepAngle);   
  }
  else
  {
   digitalWrite(dir2,down2);
   steps2 = abs(steps2);
   steps2 = steps2 + decelSteps2;
   currentAngle2 = desiredAngle2 - (decelSteps2*stepAngle);
  }

  delay(1);
}
