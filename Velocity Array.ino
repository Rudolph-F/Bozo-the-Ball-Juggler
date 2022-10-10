void velocityArray()
{  

  //--------------------------Accelerate 1 -----------------------------------
  int stepCount = steps1 - decelSteps1+1;
 // memset(velocityArray,0,steps1);

 if(accel1 == HIGH)
 {
    currentVelocity1 = desiredVelocity1 + velocityOffset1;

    for(int x = decelSteps1+1; x<=steps1; x++)
    {
      stepCount = stepCount - 1;
      currentVelocity1 = currentVelocity1 + (2*currentVelocity1)/(4*stepCount - 1);
      
      velocityArray1[x] = currentVelocity1;
      // Serial.println((String) "Step Count: "+stepCount);
      // Serial.println((String) "Current Velocity 1: "+currentVelocity1);
    }

    // Serial.println((String) "Current Velocity 1: "+currentVelocity1);
    // Serial.println((String) "Steps 1: "+steps1);

    //--------------------------Decelerate 1 -----------------------------------
    stepCount = decelSteps1 + 5;
    OCR3A = currentVelocity1;
    currentVelocity1 = desiredVelocity1 + velocityOffset1;

    for(int x = decelSteps1; x>0; x--)
    {
      stepCount = stepCount - 1;
      currentVelocity1 = currentVelocity1 + (2*currentVelocity1)/(4*stepCount - 1);
      //Serial.println((String) "Current Velocity 1: "+currentVelocity1);

      velocityArray1[x] = currentVelocity1;
    }
 }
 
  // Serial.println((String) "Current Velocity 1: "+currentVelocity1);

  if(accel2 == HIGH)
  {
  //--------------------------Accelerate 2 -----------------------------------
    stepCount = steps2 - decelSteps2+1;
    currentVelocity2 = desiredVelocity2 + velocityOffset2;

    for(int x = decelSteps2+1; x<=steps2; x++)
    {
      stepCount = stepCount - 1;
      currentVelocity2 = currentVelocity2 + (2*currentVelocity2)/(4*stepCount - 1);
      
      velocityArray2[x] = currentVelocity2;
    }

    //--------------------------Decelerate 2 -----------------------------------
    stepCount = decelSteps2 + 5;
    OCR4A = currentVelocity2;
    currentVelocity2 = desiredVelocity2 + velocityOffset2;

    for(int x = decelSteps2; x>=0; x--)
    {
      stepCount = stepCount - 1;
      currentVelocity2 = currentVelocity2 + (2*currentVelocity2)/(4*stepCount - 1);
      //Serial.println((String) "Current Velocity 1: "+currentVelocity1);

      velocityArray2[x] = currentVelocity2;
    }
  }
 }