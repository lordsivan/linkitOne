#include <LBT.h>
#include <LBTServer.h>

#include <LTask.h>
#include <LFlash.h>
#include <LSD.h>
#include <LStorage.h>

#include <LWiFi.h>
#include <LWiFiServer.h>
#include <LWiFiClient.h>

#include <ArduinoJson.h>

String blueToothBuffer=String("");

void sendBLEBroadCast(String ret){
        String ret1=ret+"\n";
        Serial.print("-->");
        Serial.print(ret1);
        Serial.println("<--");
        char buffer[200] = {0};
        memset(buffer, 0, sizeof(buffer));
        ret1.toCharArray(buffer,sizeof(buffer));
        
        // Return the command output
         if(LBTServer.connected()){
          LBTServer.write(buffer, strlen(buffer));
         }
}

void BTModuleLoop()
{      
  CheckAndConnect();
  ProcessCommand();
  
}
void CheckAndConnect(){
   
    if(!LBTServer.connected())
    {
       bool connected = LBTServer.accept(20);
 
       if( !connected )
       {
           Serial.println("No connection request yet");
       }
       else
       {
           Serial.println("Connected");
       }
    }
}

void ProcessCommand()   {
  int read_size=5;
  while(read_size!=0){
    char buffer[10];
    read_size = LBTServer.readBytes((uint8_t*)buffer, 10);          
    if(read_size > 0)
    {
        buffer[read_size]='\0';            
        blueToothBuffer+=buffer;
        /*
        Serial.print("Buffer=");
        Serial.println(buffer);
        Serial.println(blueToothBuffer);*/
    }
    int startPos=blueToothBuffer.indexOf('^');
    if(startPos>=0){
      String frontJunk=blueToothBuffer.substring(0,startPos);
      blueToothBuffer=blueToothBuffer.substring(startPos);
      /*
        Serial.print("Front Junk=");
        Serial.println(frontJunk);
        Serial.print("junk removed=");
        Serial.println(blueToothBuffer);*/     
      int endPos=blueToothBuffer.indexOf('$');        
      if(endPos>0){
        String command = blueToothBuffer.substring(1,endPos);
        /*Serial.print("Content=");
        Serial.println(command);*/

        // Command Got and execute the command
        String ret=processCommand(command)+"\n";
        Serial.print("-->");
        Serial.print(ret);
        Serial.println("<--");
        char buffer[200] = {0};
        memset(buffer, 0, sizeof(buffer));
        ret.toCharArray(buffer,sizeof(buffer));
        
        // Return the command output
        LBTServer.write(buffer, strlen(buffer));
       
        blueToothBuffer=blueToothBuffer.substring(endPos+1);            
      }
    }
  }  
}


