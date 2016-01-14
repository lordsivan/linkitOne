#include "plotly_streaming_wifi.h"

// Sign up to plotly here: https://plot.ly
// View your API key and streamtokens here: https://plot.ly/settings

// View your tokens here: https://plot.ly/settings
// Supply as many tokens as data traces
// e.g. if you want to ploty A0 and A1 vs time, supply two tokens
// arguments: username, api key, streaming token, filename

#define nTraces 2
char *tokens[nTraces] = {"bplf8aa98h", "91kpmq42gd"};
plotly graph = plotly("lordsivan", "45e78mh196", tokens, "plotly_logs", nTraces);

void Plotly_setup() {
  graph.fileopt="extend"; // See the "Usage" section in https://github.com/plotly/arduino-api for details
  bool success;
  success = graph.init();
  if(!success){
    Serial.println("Plotly failed");
  } 
  else {
    Serial.println("Plotly success");
  }
  graph.openStream();
}

unsigned long x;
int y;

void Plotly_loop() {
  unsigned long x=millis();
  float y=analogRead(A0);
  graph.plot(x, y, tokens[0]);
  graph.plot(x, y, tokens[1]);
  //Serial.println(x);
  //Serial.println(y);
}
