void unload1() // Uload motor 1 into ball dispencer
{
  zero1 = HIGH;
  zero2 = LOW;
  zero();

  currentVelocity1 = 4000;
  currentVelocity2 = 4000;
  desiredVelocity1 = unloadVelocity1;
  OCR3A = currentVelocity1;
  OCR4A = currentVelocity2;
  desiredAngle1 = unloadAngle1;
  desiredAngle2 = currentAngle2;
  decelSteps1 = 15;
  decelSteps2 = 0;
  accel1 = HIGH;
  accel2 = LOW;

  moveSteppers();
  Serial.println("Unload");
  desiredVelocity1 = launchVelocity1;
  delay(500);
}
 
void unload2() // Uload motor 2 into ball dispencer
{
  zero1 = LOW;
  zero2 = HIGH;
  zero();

  currentVelocity1 = 4000;
  currentVelocity2 = 4000;
  desiredVelocity2 = unloadVelocity2;
  OCR3A = currentVelocity1;
  OCR4A = currentVelocity2;
  desiredAngle1 = currentAngle1;
  desiredAngle2 = unloadAngle2;
  decelSteps1 = 0;
  decelSteps2 = 15;
  accel1 = LOW;
  accel2 = HIGH;

  moveSteppers();
  desiredVelocity2 = launchVelocity2;
  delay(500);
}