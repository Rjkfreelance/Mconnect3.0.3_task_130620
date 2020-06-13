void taskPackdatcon(void*){
   const char* Dataram;
      VOID SETUP()
      {  
         
      }
          
 VOID LOOP()
 {   
   if(xsdwrite == 1){
    task_CheckWiFiMqtt.stop();
    chipid = ESP.getEfuseMac();
    sprintf(Chipid_buf, "%04X%08X", (uint16_t)(chipid >> 32), (uint32_t)(chipid));
    DELAY(50);
     data_time();
   /*-------------------Start PackData--------------------------*/
  packdata_HEAD();
  packdata_DATE();
  packdata_IO();
  packdata_PWM();
  packdata_RELAY();
  packdata_PWM2();
  packdata_AD();
  packdata_GPS();
  packdata_M1();
  packdata_M2();
  packdata_M3();
  DELAY(100);
         /*
         bufwrite_eeprom1 = mac.readAddress(writeaddr_eeprom1);
         bufwrite_eeprom2 = mac.readAddress(writeaddr_eeprom2);
         write_addeeprom = (bufwrite_eeprom2 << 8) + bufwrite_eeprom1;
         */
  String sText; 

  sText += sDate;
  
  for (int i = 0; i < sizeof(buf_io); i++)
  {
    sText += buf_io[i];
  }
  sText += ";" ;
  for (int i = 0; i < sizeof(DATA_PACKPWM1); i++)
  {
    sText += DATA_PACKPWM1[i];
  }
  sText += ";" ;
  for (int i = 0; i < sizeof(DATA_PACKPWM2); i++)
  {
    sText += DATA_PACKPWM2[i];
  }
  sText += ";" ;
  for (int i = 0; i < sizeof(DATA_PACKRELAY); i++)
  {
    sText += DATA_PACKRELAY[i];
  }
  sText += ";" ;
  for (int i = 0; i < sizeof(DATA_PACKPWM3); i++)
  {
    sText += DATA_PACKPWM3[i];
  }
  sText += ";" ;
  for (int i = 0; i < sizeof(DATA_PACKPWM4); i++)
  {
    sText += DATA_PACKPWM4[i];
  }
  sText += ";" ;
  for (int i = 0; i < sizeof(DATA_PACKAD1); i++)
  {
    sText += DATA_PACKAD1[i];
  }
  sText += ";" ;
  for (int i = 0; i < sizeof(DATA_PACKAD2); i++)
  {
    sText += DATA_PACKAD2[i];
  }
  sText += ";" ;
  for (int i = 0; i < sizeof(DATA_PACKAD3); i++)
  {
    sText += DATA_PACKAD3[i];
  }
  sText += ";" ;
  for (int i = 0; i < sizeof(DATA_PACKGPS); i++)
  {
    sText += DATA_PACKGPS[i];
  }
  sText += ";" ;
  for (int i = 0; i < sizeof(DATA_PACKM1); i++)
  {
    sText += DATA_PACKM1[i];
  }
  sText += ";" ;
  for (int i = 0; i < sizeof(DATA_PACKM2); i++)
  {
    sText += DATA_PACKM2[i];
  }
  sText += ";" ;
  for (int i = 0; i < sizeof(DATA_PACKM3); i++)
  {
    sText += DATA_PACKM3[i];
  }
  sText += ";" ;
  Dataram = sText.c_str();
  DELAY(50);
  Serial.print("Datawrite Ram if Write SDcard : ");
  Serial.println(sText);
  Serial.print("EEPROM ADDR : ");
  Serial.println(write_addeeprom);
  
  for (int i = 0; i < addrsize; i++)
  {
    mac.writeAddress(write_addeeprom, Dataram[i]);
    write_addeeprom++;
  }
  
 /*
  mac.writeAddress(writeaddr_eeprom1, write_addeeprom & 0xFF); //ระบุ ADDRESS
  mac.writeAddress(writeaddr_eeprom2, (write_addeeprom >> 8) & 0xFF);
  */
  }
  DELAY(1000);  
 }
 if(xsdwrite == 0){
   task_PackdataWriteRam.stop();
   task_CheckWiFiMqtt.resume();
 }
}
