String getWaterLevel(JsonObject&  root1,String commandJson){
  Serial.println("getWaterLevel called");
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["command"] = "getWaterLevel";

  
  StaticJsonBuffer<200> dataJsonBuffer;
  JsonObject& data = root.createNestedObject("data");  
  data["lowLevelIndicator"] = digitalRead(4);
  data["midLevelIndicator"] = digitalRead(5);
  data["highLevelIndicator"] = digitalRead(6);
  
  data.prettyPrintTo(Serial);

  char buffer1[256];
  root.printTo(buffer1, sizeof(buffer1));
  root.prettyPrintTo(Serial);
  
  return String(buffer1);
}

