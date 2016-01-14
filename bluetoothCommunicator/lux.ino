void lux_loop(){
  int lux = analogRead(LUX); 
  Serial.print("Lux="); 
  Serial.println(lux);
  sendBLEBroadCast(formResponseLux(lux));
  if(lux<90){
    Serial.println("------------------Switching on LED");
    digitalWrite(STRIPLED,HIGH);   
  }else {
     Serial.println("------------------Switching OFF LED");
     digitalWrite(STRIPLED,LOW);   
  }
}


String commandLed(JsonObject&  root,String commandJson){
  int  switchAction=root["data"]["switchAction"];
  Serial.println(switchAction);
  if(switchAction==1){
    Serial.println("strip on");
    digitalWrite(STRIPLED,HIGH);  
  }else {
    Serial.println("strip off");
    digitalWrite(STRIPLED,LOW);  
  }
  return formResponseLux(0);
  }
String formResponseLux(int level)
{
  if(level==0){
    level = analogRead(LUX);     
  }
  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["command"] = "luxStatus";

  StaticJsonBuffer<300> dataJsonBuffer;
  JsonObject& data = root.createNestedObject("data");    
  data["connectionStatus"] = false;
  data["level"] = level;
  
  
  root.prettyPrintTo(Serial);
  char buffer1[256];
  root.printTo(buffer1, sizeof(buffer1));
  return String(buffer1);
}

