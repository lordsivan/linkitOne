LWiFiServer server(80);
// LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP.
#define WIFI_AUTH LWIFI_WPA

String getWifiStatus()
{
  String ssid=LWiFi.SSID();
  IPAddress ipAddress = LWiFi.localIP();
  IPAddress subNetmask=LWiFi.subnetMask(); 
  IPAddress gatewayIP1 =LWiFi.gatewayIP();
  long rssi = LWiFi.RSSI();
  
  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["command"] = "getWifiStatus";

  StaticJsonBuffer<300> dataJsonBuffer;
  JsonObject& data = root.createNestedObject("data");    
  data["connectionStatus"] = false;
  if(LWiFi.status() == LWIFI_STATUS_CONNECTED){  
    data["connectionStatus"] = true;
  }
  data["SSID"] = ssid;
  data["ipAddress"] =getIp(ipAddress);
  data["subnetMask"] = getIp(subNetmask);
  data["gatewayIP"] = getIp(gatewayIP1);
  data["signalStrength"] = rssi;  
  
  
  root.prettyPrintTo(Serial);
  char buffer1[256];
  root.printTo(buffer1, sizeof(buffer1));
  return String(buffer1);
}
String getIp(IPAddress myIp ){
  char myIpString[24];
  sprintf(myIpString, "%d.%d.%d.%d", myIp[0], myIp[1], myIp[2], myIp[3]);
  return myIpString;
}

String connectToAccessPoint(const char*  accessPoint,const char*  password)
{
  if( LWiFi.status() == LWIFI_STATUS_CONNECTED){
    LWiFi.disconnect();
  }
  while (LWiFi.status() != LWIFI_STATUS_CONNECTED)
  {
    if (LWiFi.connect(accessPoint, LWiFiLoginInfo(WIFI_AUTH, password)))
    {
      server.begin();
      return getWifiStatus();
    }
    else
    {
      Serial.println("Error - failed to connect to WiFi");      
      return String("{\"result\":\"failed\"}");
    }
  }
}
String ConfigureAndUpWifi(){
  String       setting=readSettings();
  
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject&  root = jsonBuffer.parseObject(setting);
  
  if (!root.success()) {
    Serial.println("parseObject() failed");
    return String("{\"result\":\"failed\"}");
  }
  //root.prettyPrintTo(Serial);
  const char*  accessPoint=root["data"]["accessPoint"];
  const char*  password=root["data"]["password"];  
  
  return connectToAccessPoint(accessPoint,password); 
}

String commandConfigureWifi(JsonObject&  root,String commandJson){
  // Parameter parsing..
  const char*  accessPoint=root["data"]["accessPoint"];
  const char*  password=root["data"]["password"]; 
  
  Serial.println(commandJson);
  
  writeSettings(commandJson);
  return ConfigureAndUpWifi();
}



