long duration, cm;

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
  cm = (duration/2) / 29.1;
  //inches = (duration/2) / 74; 
  
  //Serial.print(inches);
  //Serial.print("Distance: ");
  //Serial.print(cm);
  //Serial.println(" cm");
  
  return cm;
}
