/*GATEWAY code*/

#include "ThingSpeak.h"
#include "secrets.h"
#include <ESP8266WiFi.h>

#include <EasyTransfer.h>

//create object
EasyTransfer ET; 

struct RECEIVE_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int x=0;
  int y=0;
  int z=0;
  int16_t blinks;
  int16_t pause;
};

//give a name to the group of data
RECEIVE_DATA_STRUCTURE mydata;



char ssid[] = "ap";   // your network SSID (name) 
char pass[] = "12345678";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = 812759;
const char * myWriteAPIKey = "P0S0V1PCRA7KNACJ";

// Initialize our values
int number1 = 0;
int number2 = 0;
int number3 = 0;
//int number4 = random(0,100);
//String myStatus = "";

void setup() {
  Serial.begin(115200);  // Initialize serial

   //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc. 
  ET.begin(details(mydata), &Serial);
  
  pinMode(13, OUTPUT);
  

  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {


  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

  
    //check and see if a data packet has come in. 
  if(ET.receiveData()){
    //this is how you access the variables. [name of the group].[variable name]
    Serial.println(mydata.x);
    number1 = mydata.x;
    Serial.println(mydata.y);
    number2 = mydata.y;
    Serial.println(mydata.z);
    number3 = mydata.z;
    Serial.printf("\n");

  }

  // set the fields with the values
  ThingSpeak.setField(1, number1);
  ThingSpeak.setField(2, number2);
  ThingSpeak.setField(3, number3);
  

  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  

  
  delay(4000); // Wait 20 seconds to update the channel again
}
