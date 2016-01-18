void setup()
{
    // 0. Pin configuration
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(A0,INPUT);  

    pinMode(2, OUTPUT); // OUT
    pinMode(7, OUTPUT); // IN
    
    
    // 1. Initialize serial and wait for some data  
    Serial.begin(9600);
    while(!Serial.available()); 

    // 2. Initialize storage card
    Serial.print("Initializing Storage card...");
    pinMode(10, OUTPUT);
    LTask.begin();
    LFlash.begin();     

    // 3. Start WIFI and configure wifi
   // LWiFi.begin();
    //ConfigureAndUpWifi();
    
    //4. Start Bluetooth
    bool success = LBTServer.begin();      
    if( !success )
    {
        Serial.println("Cannot begin Bluetooth Server successfully");
        // don't do anything else
        while(true);
    }
    else
    {
        Serial.println("Bluetooth Server begin successfully");
    }    

    //5 plotly
    //Plotly_setup();

    //6.PHMointer
    //PHMointor_setup();
    
    //7. Ultrasonic
    ultrasonic_setup();
    
}
void loop(){
  BTModuleLoop();
  //Plotly_loop();
  //ph_loop();
  //lux_loop();
  //temp_loop();
  //food_loop();
  ultrasonic_loop();
}

