String processCommand(String commandJson){
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject&  root = jsonBuffer.parseObject(commandJson);
  
  if (!root.success()) {
    Serial.println("processCommand() failed");    
    return String("{\"result\":\"failed\"}");
  }
  else 
  {
    const char*  command=root["command"];
    Serial.print("command=");
    root.prettyPrintTo(Serial);
    String cmm= String(command);
    
    if(cmm.startsWith("configureWifi")){
      return commandConfigureWifi(root,commandJson);        
    }
    else if(cmm.startsWith("getConfigurationDetail")){
      return getConfigurationDetail(root,commandJson);
    }
    else if(cmm.startsWith("getWaterLevel")){
      return getWaterLevel(root,commandJson);
    }
    else if(cmm.startsWith("commandLed")){
      return commandLed(root,commandJson);
    }
    else if(cmm.startsWith("commandFoodFeed")){
      return commandFoodFeed(root,commandJson);
    }    
  }
}

