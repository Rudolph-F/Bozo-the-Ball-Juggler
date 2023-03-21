void moveSteppers() // This fucntion moves the stepper motors to their respective positions
{
  steps_direction();
  // if(accel1 == HIGH || accel2 == HIGH)
  // {
  velocityArray();
  // }
  
  move1 = HIGH;
  move2 = HIGH;

  // TCNT3 = 0;
  MOTOR1_INTERRUPTS_ON;
  delayMicroseconds(30);
  // TCNT4 = 0;
  MOTOR2_INTERRUPTS_ON;

  while(move1 == HIGH || move2 == HIGH);// || (steps2 > 0))

  // Serial.println((String) "Steps1: " +steps1);
  // Serial.println((String) "Steps2: " +steps2);
  
  MOTOR1_INTERRUPTS_OFF;
  MOTOR2_INTERRUPTS_OFF;
  accel1 = LOW;
  accel2 = LOW;
}