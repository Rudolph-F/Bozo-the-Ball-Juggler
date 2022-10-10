ISR(TIMER3_COMPA_vect) // Compare registor vector
{
  // TCNT1 = 0;			// Reset timer 1 to zero;
  if(steps1 > 0)
  {
    if(stepState1 == HIGH)
    {
      PORTG &= B011111; // D4 LOW
      // PORTG ^= (1 << PG5);
      if(accel1 == HIGH)
      {
        OCR3A = velocityArray1[steps1];
        // Serial.println(OCR3A);
      }
      
      steps1 = steps1 - 1;

    }
    else
    {
  	  PORTG |= B100000; // D4 HIGH  
      // PORTG ^= (1 << PG5);
    }
    stepState1 =! stepState1;   
  }
  else 
  {
    move1 = LOW;  
  }
   //PORTB ^= (1 << PB5); // uses XOR ^ operation to invert pin  //PORTB = PORTB ^ B00100000; //same as the above
}

ISR(TIMER4_COMPA_vect) // Compare registor vector
{
  //TCNT2 = 0;			// Reset timer 1 to zero;
  if(steps2 > 0)
  {
    if(stepState2 == HIGH)
    {
      PORTH &= B11011111; // D8 LOW
      // PORTH ^= (1 << PH5);
      if(accel2 == HIGH)
      {

        OCR4A = velocityArray2[steps2];
        // Serial.println(OCR4A);

      }
      steps2 = steps2 - 1;
    }
    else
    {
  	  PORTH |= B00100000; // D8 HIGH  
      // PORTH ^= (1 << PH5);
    }
    stepState2 =! stepState2;
  }
  else 
  {
    move2 = LOW;
  }
  //PORTB ^= (1 << PB4); // uses XOR ^ operation to invert pin
  //PORTB = PORTB ^ B00010000; //same as the above
}