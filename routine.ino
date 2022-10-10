void routine()
{
  bool enableState = HIGH;
  // Serial.println("Start of Rotine");

  if(jugglerConfigSubMode5 == 1 && enableState == HIGH) //Singal Ball Horizontal Mode
  { 
    enableState = LOW;
    if(launch1 == HIGH && launch2 == LOW) // throw motor 1 motor 2 remians stationary
    {
      ballPosition = 2;
      zero1 = HIGH;
      zero2 = LOW;
      zero();
      // delay(150);

      if(routineStartUp == HIGH)
      {
        OCR3A = 1500;
        OCR4A = 1500;
        desiredAngle1 = currentAngle1;
        desiredAngle2 = launchAngle1 + angleOffset1;
        decelSteps1 = 0;
        decelSteps2 = 0;
        accel2 = LOW;
        moveSteppers();
        routineStartUp = LOW;
      }
      
      // currentVelocity1 = 4000;
      // currentVelocity2 = 4000;
      OCR3A = 3000;//desiredVelocity1 + velocityOffset1;
      OCR4A = 3000;
      desiredAngle1 = launchAngle1 + angleOffset1;
      desiredAngle2 = currentAngle2;//launchAngle2 + angleOffset2;
      decelSteps1 = 25;
      decelSteps2 = 25;
      accel1 = HIGH;
      accel2 = LOW;

      tic = micros();

      moveSteppers();

      tic = micros() - tic;
      Serial.print("Motor 1: ");
      Serial.println(tic);

      desiredAngle1 = currentAngle1;//launchAngle1 + angleOffset1;
      desiredAngle2 = launchAngle1 + angleOffset1-1.8;
      decelSteps1 = 0;
      decelSteps2 = 0;
      OCR3A = 1800;
      OCR4A = 1800;
      delay(450);
      moveSteppers();

      updateLCD = HIGH;
    }

    if(launch2 == HIGH && launch1 == LOW) // launch motor 2 motor 1 remains stationary
    {
      ballPosition = 1;
      zero1 = LOW;
      zero2 = HIGH;
      zero();

      // currentVelocity1 = 3000;
      // currentVelocity2 = 3000;
      OCR3A = 3000;//desiredVelocity1 + velocityOffset1;
      OCR4A = 3000;
      desiredAngle1 = currentAngle1;//launchAngle1 + angleOffset1;
      desiredAngle2 = launchAngle2 + angleOffset2;
      decelSteps1 = 25;
      decelSteps2 = 25;
      accel1 = LOW;
      accel2 = HIGH;
      tic = micros();

      moveSteppers();

      // Serial.println(OCR3A);
      tic = micros() - tic;
      // Serial.print("Motor 2: ");
      // Serial.println(tic);

      desiredAngle1 = launchAngle2 + angleOffset2 - 1.8;
      desiredAngle2 = currentAngle2;//launchAngle1 + angleOffset1; 
      decelSteps1 = 0;
      decelSteps2 = 0;

      OCR3A = 1500;
      OCR4A = 1500;
      delay(450);
      moveSteppers();

      updateLCD = HIGH;
    }

    launch1 = !launch1;
    launch2 = !launch2;
 }    

  if(jugglerConfigSubMode5 == 2 && enableState == HIGH) // Two ball horizontal mode
  {   
    enableState = LOW;
    zero1 = HIGH;
    zero2 = HIGH;
    zero();
    // delay(150);

    currentVelocity1 = 3000;
    currentVelocity2 = 3000;
    OCR3A = currentVelocity1;//desiredVelocity1 + velocityOffset1;
    OCR4A = currentVelocity2;//desiredVelocity2 + velocityOffset2;
    desiredAngle1 = launchAngle1 + angleOffset1; //81.45
    desiredAngle2 = launchAngle2 + angleOffset2;
    decelSteps1 = 25;
    decelSteps2 = 25;
    accel1 = HIGH;
    accel2 = HIGH;
    // tic = micros();

    moveSteppers();

    // Serial.println(OCR3A);
    // tic = micros() - tic;
    // Serial.println(tic);

    
    desiredAngle1 = launchAngle2 + angleOffset2-5.4; //81.45
    desiredAngle2 = launchAngle1 + angleOffset1-0.9;
    decelSteps1 = 0;
    decelSteps2 = 0;
    OCR3A = 1800;
    OCR4A = 1800;
    delay(450);
    moveSteppers();

    enableState = LOW;
    // Serial.println(OCR3A);
    //cli();
    //while(digitalRead(button) == LOW);
    //delay(900);
    //lcd.clear();
    updateLCD = HIGH;
 }    

  if(jugglerConfigSubMode5 == 3 && enableState == HIGH) // Two ball vertical mode
  {   
    enableState = LOW;
    zero1 = HIGH;
    zero2 = HIGH;
    zero();

    currentVelocity1 = 1500;
    currentVelocity2 = 1500;
    OCR3A = currentVelocity1;//desiredVelocity1 + velocityOffset1;
    OCR4A = currentVelocity2;//desiredVelocity2 + velocityOffset2;
    desiredAngle1 = launchAngle1 + angleOffset1; //81.45
    desiredAngle2 = launchAngle2 + angleOffset2;
    decelSteps1 = 30;
    decelSteps2 = 30;
    accel1 = HIGH;
    accel2 = HIGH;
    // tic = micros();

    moveSteppers();

    // tic = micros() - tic;
    // Serial.println(tic);

    
    desiredAngle1 = launchAngle1 + angleOffset1 - 0.9; //81.45
    desiredAngle2 = launchAngle2 + angleOffset2 -0.9;
    decelSteps1 = 0;
    decelSteps2 = 0;
    OCR3A = 2000;
    OCR4A = 2000;
    delay(480);
    moveSteppers();

    while(digitalRead(encoderButton1) == LOW);
    updateLCD = HIGH;
 } 

  if(jugglerConfigSubMode5 == 4 && enableState == HIGH) // One ball vertical mode left (motor 2)
  {   
    enableState = LOW;
    zero1 = HIGH;
    zero2 = HIGH;
    zero();

    currentVelocity1 = 1500;
    currentVelocity2 = 1500;
    OCR3A = currentVelocity1;//desiredVelocity1 + velocityOffset1;
    OCR4A = currentVelocity2;//desiredVelocity2 + velocityOffset2;
    desiredAngle1 = currentAngle1; //81.45
    desiredAngle2 = launchAngle2 + angleOffset2;
    decelSteps1 = 0;
    decelSteps2 = 30;
    accel1 = LOW;
    accel2 = HIGH;
    // tic = micros();

    moveSteppers();

    // Serial.println(OCR3A);
    // tic = micros() - tic;
    // Serial.println(tic);

    
    desiredAngle1 = currentAngle1;
    desiredAngle2 = launchAngle2 + angleOffset2;
    decelSteps1 = 0;
    decelSteps2 = 0;
    OCR3A = 2000;
    OCR4A = 2000;
    delay(480);
    moveSteppers();

    updateLCD = HIGH;
  } 

  if(jugglerConfigSubMode5 == 5 && enableState == HIGH) // One ball vertical mode right (motor 1)
  {   
    enableState = LOW;
    zero1 = HIGH;
    zero2 = HIGH;
    zero();

    currentVelocity1 = 1500;
    currentVelocity2 = 1500;
    OCR3A = currentVelocity1;//desiredVelocity1 + velocityOffset1;
    OCR4A = currentVelocity2;//desiredVelocity2 + velocityOffset2;
    desiredAngle1 = launchAngle1 + angleOffset1;
    desiredAngle2 = currentAngle2; 
    decelSteps1 = 30;
    decelSteps2 = 0;
    accel1 = HIGH;
    accel2 = LOW;
    // tic = micros();

    moveSteppers();

    // Serial.println(OCR3A);
    // tic = micros() - tic;
    // Serial.println(tic);

    
    desiredAngle1 = launchAngle1 + angleOffset1;
    desiredAngle2 = currentAngle2; 
    decelSteps1 = 0;
    decelSteps2 = 0;
    OCR3A = 2000;
    OCR4A = 2000;
    delay(480);
    moveSteppers();

    updateLCD = HIGH;
 }

}
