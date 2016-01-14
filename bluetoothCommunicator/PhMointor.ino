



void PHMointor_setup(){
   pinMode(LOWLEVEL,INPUT);
   pinMode(MEDLEVEL,INPUT);
   pinMode(HIGHLEVEL,INPUT);
   pinMode(PHSWITCH,INPUT);

    pinMode(LUX,INPUT);
    pinMode(PH,INPUT);
  
   pinMode(FRESH,OUTPUT);
   pinMode(DIRTY,OUTPUT);
   pinMode(STRIPLED,OUTPUT);
   pinMode(FOODFEEDER,OUTPUT);
   pinMode(HEATER,OUTPUT);

  
   digitalWrite(PHSWITCH,LOW);
   digitalWrite(FRESH,LOW);
   digitalWrite(DIRTY,LOW);
   digitalWrite(STRIPLED,LOW);
   digitalWrite(FOODFEEDER,LOW);
   digitalWrite(HEATER,LOW);   
}





void ph_loop1(){
    int phlevel = analogRead(PH);  
    Serial.print("PH=");
    Serial.println(phlevel);

    int lux = analogRead(LUX);  
    Serial.print("LUX=");
    Serial.println(lux);
    delay(1000);
}

void ph_loop(){
    int phlevel = digitalRead(PHSWITCH);  
    int low = digitalRead(LOWLEVEL);
    int mid = digitalRead(MEDLEVEL);
    int high = digitalRead(HIGHLEVEL);

    Serial.print(phlevel);

    digitalWrite(FRESH,LOW);
    digitalWrite(DIRTY ,LOW);
    
  if (phlevel==HIGH) {
    Serial.println("Ph level high");
    while(low== HIGH){
      Serial.println("Water is not reached low mark");
      
      digitalWrite(DIRTY ,HIGH);
      low = digitalRead(LOWLEVEL);
      mid = digitalRead(MEDLEVEL);
      high = digitalRead(HIGHLEVEL);
      
      Serial.println(low);
      Serial.println(mid);
      Serial.println(high);
    }
    digitalWrite(FRESH,LOW);
    digitalWrite(DIRTY ,LOW);
    high = digitalRead(HIGHLEVEL);
    while(high==LOW){
      Serial.println("Wating for refill");
      digitalWrite(FRESH,HIGH);
      high = digitalRead(HIGHLEVEL);
    }
    digitalWrite(FRESH,LOW);
    digitalWrite(DIRTY ,LOW);
  } else {
    Serial.println("Ph level LOW");
  }
}
