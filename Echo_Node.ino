//******************************************************************************************
/*Echo Node*/                                                                              *
//******************************************************************************************
#include "painlessMesh.h"

#define   MESH_PREFIX     "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555

// Prototypes
void receivedCallback( uint32_t from, String &msg );

painlessMesh  mesh;

void setup() {
  Serial.begin(115200);
    
  mesh.setDebugMsgTypes( ERROR | STARTUP | CONNECTION );  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, MESH_PORT );
  mesh.onReceive(&receivedCallback);
}

void loop() {
  mesh.update();
}

void receivedCallback( uint32_t from, String &msg ) {
  uint32_t dist= 3810272744;
  
  Serial.printf("echoNode: Received from %u msg=%s\n", from, msg.c_str());
  Serial.printf("echoNode: sending data to %u msg=%s\n", dist, msg.c_str());
  
  mesh.sendSingle(dist, msg);
  
}
