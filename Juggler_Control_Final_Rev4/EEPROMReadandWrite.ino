void WriteEEPROM() // Writes the necessary values ot the EERPOM
{
  int variableSize = sizeof(double);
  int adress = 0;
  GoForWrite = LOW;

  EEPROM.put(adress,horz1AngleOffset1); // Put was used as it only writes to the EEPRO if the data has changed 
  adress = adress + variableSize;       // the EEPROM only has aorund 100 000 write cycles per adress

  EEPROM.put(adress,horz1AngleOffset2);
  adress = adress + variableSize;

  EEPROM.put(adress,horz2AngleOffset1);
  adress = adress + variableSize;

  EEPROM.put(adress,horz2AngleOffset2);
  adress = adress + variableSize;

  EEPROM.put(adress,vert2AngleOffset1);
  adress = adress + variableSize;

  EEPROM.put(adress,vert2AngleOffset2);
  adress = adress + variableSize;

  EEPROM.put(adress,vertLAngleOffset1);
  adress = adress + variableSize;

  EEPROM.put(adress,vertRAngleOffset2);
  adress = adress + variableSize;

  EEPROM.put(adress,horz1VelocityOffset1);
  adress = adress + variableSize;

  EEPROM.put(adress,horz1VelocityOffset2);
  adress = adress + variableSize;

  EEPROM.put(adress,horz2VelocityOffset1);
  adress = adress + variableSize;

  EEPROM.put(adress,horz2VelocityOffset2);
  adress = adress + variableSize;

  EEPROM.put(adress,vert2VelocityOffset1);
  adress = adress + variableSize;

  EEPROM.put(adress,vert2VelocityOffset2);
  adress = adress + variableSize;

  EEPROM.put(adress,vertLVelocityOffset1);
  adress = adress + variableSize;

  EEPROM.put(adress,vertRVelocityOffset2);
  adress = adress + variableSize;

  EEPROM.put(adress,zeroAngle1);
  adress = adress + variableSize;

  EEPROM.put(adress,zeroAngle2);
  adress = adress + variableSize;

  EEPROM.put(adress,decelSteps);
  adress = adress + variableSize;

  EEPROM.put(adress,unloadAngle1);
  adress = adress + variableSize;

  EEPROM.put(adress,unloadVelocity1);
  adress = adress + variableSize;

  EEPROM.put(adress,unloadAngle2);
  adress = adress + variableSize;

  EEPROM.put(adress,unloadVelocity2);
  adress = adress + variableSize;

}

void ReadEEPROM() // Reads the necessary vaules from the EEPROM
{
  int variableSize = sizeof(double);
  int adress = 0; //each vaule is stored in a spesific adress and can ouly be read form the same adress

  EEPROM.get(adress,horz1AngleOffset1);
  adress = adress + variableSize;

  EEPROM.get(adress,horz1AngleOffset2);
  adress = adress + variableSize;

  EEPROM.get(adress,horz2AngleOffset1);
  adress = adress + variableSize;

  EEPROM.get(adress,horz2AngleOffset2);
  adress = adress + variableSize;

  EEPROM.get(adress,vert2AngleOffset1);
  adress = adress + variableSize;

  EEPROM.get(adress,vert2AngleOffset2);
  adress = adress + variableSize;

  EEPROM.get(adress,vertLAngleOffset1);
  adress = adress + variableSize;

  EEPROM.get(adress,vertRAngleOffset2);
  adress = adress + variableSize;

  EEPROM.get(adress,horz1VelocityOffset1);
  adress = adress + variableSize;

  EEPROM.get(adress,horz1VelocityOffset2);
  adress = adress + variableSize;

  EEPROM.get(adress,horz2VelocityOffset1);
  adress = adress + variableSize;

  EEPROM.get(adress,horz2VelocityOffset2);
  adress = adress + variableSize;

  EEPROM.get(adress,vert2VelocityOffset1);
  adress = adress + variableSize;

  EEPROM.get(adress,vert2VelocityOffset2);
  adress = adress + variableSize;

  EEPROM.get(adress,vertLVelocityOffset1);
  adress = adress + variableSize;

  EEPROM.get(adress,vertRVelocityOffset2);
  adress = adress + variableSize;

  EEPROM.get(adress,zeroAngle1);
  adress = adress + variableSize;

  EEPROM.get(adress,zeroAngle2);
  adress = adress + variableSize;

  EEPROM.get(adress,decelSteps);
  adress = adress + variableSize;

  EEPROM.get(adress,unloadAngle1);
  adress = adress + variableSize;

  EEPROM.get(adress,unloadVelocity1);
  adress = adress + variableSize;

  EEPROM.get(adress,unloadAngle2);
  adress = adress + variableSize;

  EEPROM.get(adress,unloadVelocity2);
  adress = adress + variableSize;

}
