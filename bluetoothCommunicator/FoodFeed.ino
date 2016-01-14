int count=0;
void food_loop(){
  if(count%100==0){
    digitalWrite(FOODFEEDER,HIGH);   
  }else if(count%100==5){
    digitalWrite(FOODFEEDER,LOW);   
  }
  count++;
}

String commandFoodFeed(JsonObject&  root,String commandJson){
  int  switchAction=root["data"]["switchAction"];
  Serial.println(switchAction);
  if(switchAction==1){
    Serial.println("strip on");
    digitalWrite(FOODFEEDER,HIGH);   
  }else {
    Serial.println("strip off");
    digitalWrite(FOODFEEDER,LOW);   
  }
  return formResponseFoodFeed();
  }
String formResponseFoodFeed()
{
  
  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["command"] = "foodFeedStatus";

  StaticJsonBuffer<300> dataJsonBuffer;
  JsonObject& data = root.createNestedObject("data");    
  data["status"] = true;
  
  
  
  root.prettyPrintTo(Serial);
  char buffer1[256];
  root.printTo(buffer1, sizeof(buffer1));
  return String(buffer1);
}
