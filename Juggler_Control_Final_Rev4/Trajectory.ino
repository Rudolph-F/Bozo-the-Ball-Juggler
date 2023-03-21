
void trajectory(double Time, double Dx)
{ 
  
  double Theta = atan((Dy+0.5*g*Time*Time)/Dx)*180/PI; //Equation 1 
  double V0 = (Dy + 0.5*g*Time*Time)/(sin(Theta*PI/180)*Time); //Equation 2
  
  //----Round to nearest launch angle ------
  int steps = round(Theta/stepAngle);
  Theta = steps*stepAngle; // New Launch angle multiple of step angle
  
  //----Determine new launch distance -------
  double DxLoss = armLength - cos((90-Theta)*PI/180)*armLength; // Equation 3
  Dx = Dx - 2*DxLoss;
  
  //----- New Flight time -----
  Time = sqrt(((tan(Theta*PI/180)*Dx-Dy)*2)/g); // Equation 4
  
  //----- New Launch Velocity ----- 
  V0 = Dx/(cos(Theta*PI/180)*Time); //Equation 5
  
  // ---- Determine Step Time -----
  double StepsPs = V0/armLength*180/PI/stepAngle;
  double pulseTime = 1/StepsPs/2;
  
  trajectoryResults[0] = round(pulseTime/TimePtick); // Detrmine the number of timer overflows needed
  trajectoryResults[1] = Theta; // Launch Angle
}