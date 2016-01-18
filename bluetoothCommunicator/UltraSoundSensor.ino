#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.


long duration, cm;
float temperatureCoefficient = 29.1;
void ultrasonic_setup(){
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
}

void ultrasonic_loop(){
  
  int distance = getDistance();
  String jsonData = formResponseUltrasonic(distance);
  sendBLEBroadCast(jsonData);
}

String formResponseUltrasonic(int distance)
{
  
  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["command"] = "UltrasonicStatus";

  StaticJsonBuffer<300> dataJsonBuffer;
  JsonObject& data = root.createNestedObject("data");    
  data["distance"] = distance;
  
  root.prettyPrintTo(Serial);
  char buffer1[256];
  root.printTo(buffer1, sizeof(buffer1));
  return String(buffer1);
}

String commandChangeTempCoefficient(JsonObject&  root,String commandJson){
  int tempCoefficient=root["data"]["tempCoefficient"];
  Serial.println(tempCoefficient);

  
  temperatureCoefficient=tempCoefficient;

  int distance = getDistance();
  String jsonData = formResponseUltrasonic(distance);

  
  return jsonData;
}

int getDistance()
{
 
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(ECHO_PIN, HIGH);
 
  // convert the time into a distance
  cm = (duration/2) / temperatureCoefficient;
  //inches = (duration/2) / 74; 
  
  //Serial.print(inches);
  //Serial.print("Distance: ");
  //Serial.print(cm);
  //Serial.println(" cm");
  
  return cm;
}
