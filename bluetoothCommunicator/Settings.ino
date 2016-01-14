#define Drv LFlash          // use Internal 10M Flash

LFile myFile;
String readSettings(){
    String data="";
    LFile myFile = Drv.open("settings.json");
    if (myFile) {
        Serial.println("settings.json opended");
        myFile.seek(0);        
        while (myFile.available()) {                      
            char ltr=myFile.read();            
            data+=ltr;
            //Serial.write(myFile.read());
        }        
        myFile.close();
    } else {        
        Serial.println("Unable to read setting file. taking default settings");
        data=String("{\"command\":\"configureWifi\",\"data\": {\"accessPoint\":\"sivaphone\",\"password\":\"9840378332\"}}");
    }
    
    data=String("{\"command\":\"configureWifi\",\"data\": {\"accessPoint\":\"sivaphone\",\"password\":\"9840378332\"}}");
    Serial.print("-->"); Serial.print(data); Serial.print("<--");  
    return data;
}
void writeSettings(String settingJson){
    Drv.remove("settings.json");
    LFile myFile = Drv.open("settings.json", FILE_WRITE );    
    if (myFile) { 
        Serial.print("Writing to settings.json...");
        Serial.println(settingJson);
        myFile.print(settingJson);        
        myFile.close();
        Serial.println("done.");
    } else {
        // if the file didn't open, print an error:
        Serial.println("error opening settings.json");
    }
}


String getConfigurationDetail(JsonObject&  root,String commandJson){
  String ret= readSettings();
  Serial.println(ret);
  return ret;
}
