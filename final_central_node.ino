/*CENTRAL node*/
#include "painlessMesh.h"
#include <EasyTransfer.h>

//create object
EasyTransfer ET; 


//in place of delay
int period = 5000;
unsigned long time_now = 0;

struct SEND_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to send
  int x=0;
  int y=0;
  int z=0;
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t blinks;
  int16_t pause;
};

//give a name to the group of data
SEND_DATA_STRUCTURE mydata;


#define   MESH_PREFIX     "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555

Scheduler userScheduler; // to control your personal task
painlessMesh  mesh;


// Needed for painless library
void receivedCallback( uint32_t from, String &msg ) {
  String str = msg.c_str();
  int data = str.toInt();
  int check = data;
  int field;


  
  if(from == 3257966599)
  {
    Serial.printf("startHere: Received from router 1 (node id: %u) msg=%s\n", from, msg.c_str());
  }
  if(from == 3257967891)
  {
      Serial.printf("startHere: Received from router 2 (node id: %u) msg=%s\n", from, msg.c_str());
  }


   check = check%10;
  //sending data to structure
       if(check == 1)
       {
        field = 1;
        mydata.x = data/10;
       }
  else if(check == 2)
       {
        field = 2;
        mydata.y = data/10;
       }
  else if(check == 3)
       {
        field = 3;
        mydata.z = data/10;     
       }
       
 
}

void newConnectionCallback(uint32_t nodeId) {
    Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
    Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
}

void setup() {
  Serial.begin(115200);

  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
  ET.begin(details(mydata), &Serial);
  
  pinMode(13, OUTPUT);
  
  randomSeed(analogRead(0));

//mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);


}

void loop() {
  //I2C communication
  
  if(millis() > time_now + period)
    {time_now = millis();
    Serial.println(mydata.x);
    
 
    Serial.println(mydata.y);

  
    Serial.println(mydata.z);
     mydata.blinks = random(5);
     mydata.pause = random(5);
     //send the data
     ET.sendData();
    }


  
  // it will run the user scheduler as well
  mesh.update();
}
