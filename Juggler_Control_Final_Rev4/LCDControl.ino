void setLCD() // Sets the LCD display to the respective routine and mdoe
{
  updateLCD = LOW;
  // Serial.println("LCD");
  if(stopMotors == HIGH)
  {
    lcd.clear();
    lcd.setCursor(3,1);
    lcd.write("Motors Disabled");
    return;
  }
  setIndicator();

  if(jugglerConfigSubMode5 == 1)
  {
    lcd.setCursor(13,0);
    lcd.write("HORZ "); 
    lcd.print("1");
    launchAngle1 = 99.5625 + horz1AngleOffset1; 
    launchAngle2 = 99.5625 + horz1AngleOffset2;
    desiredVelocity1 = 140 + horz1VelocityOffset1;
    desiredVelocity2 = 140 + horz1VelocityOffset2;
  }

  if(jugglerConfigSubMode5 == 2)
  {
    lcd.setCursor(13,0);
    lcd.write("HORZ "); 
    lcd.print("2");
    launchAngle1 = 97.8750 + horz2AngleOffset1; 
    launchAngle2 = 101.2375 + horz2AngleOffset2;//97.2
    desiredVelocity1 = 133 + horz2VelocityOffset1;
    desiredVelocity2 = 142 + horz2VelocityOffset2;//135
    
  }

  if(jugglerConfigSubMode5 == 3)
  {
    lcd.setCursor(13,0);
    lcd.write("VERT "); 
    lcd.print("2");
    launchAngle1 = 81.5625  + vert2AngleOffset1;//82.0125; 
    launchAngle2 = 81.5625  + vert2AngleOffset2;
    desiredVelocity1 = 145 + vert2VelocityOffset1;
    desiredVelocity2 = 145 + vert2VelocityOffset2;
  }

  if(jugglerConfigSubMode5 == 4)
  {
    lcd.setCursor(13,0);
    lcd.write("VERT "); 
    lcd.write("R");
    launchAngle1 = 81.5625 + vertLAngleOffset1;
    launchAngle2 = 81.5625 + vertRAngleOffset2;
    desiredVelocity1 = 145 + vertLVelocityOffset1;
    desiredVelocity2 = 145 + vertRVelocityOffset2;
  }

  if(jugglerConfigSubMode5 == 5)
  {
    lcd.setCursor(13,0);
    lcd.write("VERT "); 
    lcd.write("L");
    launchAngle1 = 81.5625 + vertLAngleOffset1; 
    launchAngle2 = 81.5625 + vertRAngleOffset2;
    desiredVelocity1 = 145 + vertLVelocityOffset1;
    desiredVelocity2 = 145 + vertRVelocityOffset2;
  }

  lcd.setCursor(13,1);
  lcd.write("Ft:");
  lcd.print(flightTime);

  lcd.setCursor(13,2);
  lcd.write("Fd:");
  lcd.print(flightDistance);

  if(jugglerConfigSubMode8 == 1)
  {
    lcd.setCursor(13,3);
    lcd.write("Auto:"); //Manu
    lcd.write("  ");
    lcd.setCursor(18,3);
    lcd.print(juggleCount);
    if(juggleCount == -1)
    {
      juggleInf = HIGH;
    }
    else
    {
      juggleInf = LOW;
    }
  }

  if(jugglerConfigSubMode8 == 2)
  {
    lcd.setCursor(13,3);
    lcd.write("Manual"); //Manual
    lcd.write(" ");
    juggleCount = 1;
    // lcd.print(juggleCount);
  }

  lcd.setCursor(0,0);
  lcd.write("A1:");
  lcd.print("        ");
  lcd.setCursor(3,0);
  lcd.print(launchAngle1,4);

  lcd.setCursor(0,1);
  lcd.write("V1:");
  lcd.print(desiredVelocity1);

  lcd.setCursor(0,2);
  lcd.write("A2:");
  lcd.print("        ");
  lcd.setCursor(3,2);
  lcd.print(launchAngle2,4);

  lcd.setCursor(0,3);
  lcd.write("V2:");
  lcd.print(desiredVelocity2); 
} 



void setIndicator()
{
    if(jugglerConfig == 1)
    {
      lcd.setCursor(11,0);
      lcd.write("<");
    }
    else 
    {
    lcd.setCursor(11,0);
    lcd.write(" ");
    }

    if(jugglerConfig == 2)
    {
      lcd.setCursor(11,1);
      lcd.write("<");
    }
    else 
    {
    lcd.setCursor(11,1);
    lcd.write(" ");
    }

    if(jugglerConfig == 3)
    {
      lcd.setCursor(11,2);
      lcd.write("<");
    }
    else 
    {
    lcd.setCursor(11,2);
    lcd.write(" ");
    }

    if(jugglerConfig == 4)
    {
      lcd.setCursor(11,3);
      lcd.write("<");
    }
    else 
    {
    lcd.setCursor(11,3);
    lcd.write(" ");
    }

    if(jugglerConfig == 5)
    {
      lcd.setCursor(12,0);
      lcd.write(">");
    }
    else 
    {
    lcd.setCursor(12,0);
    lcd.write(" ");
    }

    if(jugglerConfig == 6)
    {
      lcd.setCursor(12,1);
      lcd.write(">");
    }
    else 
    {
    lcd.setCursor(12,1);
    lcd.write(" ");
    }

    if(jugglerConfig == 7)
    {
      lcd.setCursor(12,2);
      lcd.write(">");
    }
    else 
    {
    lcd.setCursor(12,2);
    lcd.write(" ");
    }

    if(jugglerConfig == 8)
    {
      lcd.setCursor(12,3);
      lcd.write(">"); //→ 
    }
    else if(jugglerConfig == 9)
    {
      lcd.setCursor(12,3);
      lcd.write(")"); //→ 
    }
   else 
    {
      lcd.setCursor(12,3);
      lcd.write(" ");
    }
}