/*
  Wifi Xively sensor client
 
 This sketch sends a simple time value to Xively (http://www.xively.com)
 using Wi-Fi functionality on LinkIt platform.

 Change the WIFI_AP, WIFI_PASSWORD and WIFI_AUTH accordingly.
 
 To make it work, create a feed ID with a datastream first. 
 Or change the code below to match your feed.

 created 13 Mar 2012
 modified 31 May 2012
 by Tom Igoe
 modified 8 Nov 2013
 by Scott Fitzgerald
 modified 20 Aug 2014
 by MediaTek Inc.

 This code is in the public domain.

 */

/*****************
 * This sample connectes to Xively.com API by LinkIt ONE WiFi module and keeps updating a feed in Xively.
 * You need to apply an Xively API key and create the feed first.
 */
#include <LTask.h>
#include <LWiFi.h>
#include <LWiFiClient.h>

#define SITE_URL      "api.xively.com"  // Xively API URL
#define APIKEY         "R5MiymnIHbpgo2Ji1h7VYLjxTRVLspdn8s4T4dFxVHtfTi6G" // replace your xively api key here
#define FEEDID         717486114         // replace your feed ID
#define USERAGENT      "LinkItOne_Cloud"     // user agent is the project name

#define WIFI_AP "TP-LINK"            // replace your WiFi AP SSID
#define WIFI_PASSWORD "chapratodelhi"  // replace your WiFi AP password
#define WIFI_AUTH LWIFI_WPA           // choose from LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP according to your AP

#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

void setup()
{
  Serial.begin(115200);
  
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  
  // Initializes LinkIt ONE WiFi module
  LWiFi.begin();

  Serial.print("Connecting to WiFi AP:");
  Serial.println(WIFI_AP);
  while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD)))
  {
    delay(1000);
  }
}

unsigned long distance = 0;
 
void loop()
{

  // in this sketch, we send to process time of loop()
  // to Xively server.
  // The feed is created on Xively first.
  
  Serial.print("try connect ");
  Serial.println(SITE_URL);
  LWiFiClient c;
  while (!c.connect(SITE_URL, 80))
  {
    Serial.println("retry connect");
    delay(100);
  }

  distance = getDistance();
  String data = "Ultrasonic,"+String(distance);
  Serial.println("send PUT request");
  Serial.println(data);

  // construct a HTTP PUT request
  // and set CSV data to the Xively feed.
  c.print("PUT /v2/feeds/");
  c.print(FEEDID);
  c.println(".csv HTTP/1.1");
  c.println("Host: api.xively.com");
  c.print("X-ApiKey: ");
  c.println(APIKEY);
  c.print("User-Agent: ");
  c.println(USERAGENT);
  c.print("Content-Length: ");
  int thisLength = data.length();
  c.println(thisLength);
  c.println("Content-Type: text/csv");
  c.println("Connection: close");
  c.println();
  c.println(data);

  // this is required delay, to allow server response
  delay(1000);
  // disconnect from server
  c.stop();
  // add delay to prevent connect again too fast
  delay(250);
}
