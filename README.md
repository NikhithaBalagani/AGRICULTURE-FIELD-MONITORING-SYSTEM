# Agriculture field monitoring system

# overview
Modernization of the farming process is one of the crucial steps for a country like India. Various technological improvements have been suggested in the past and have been adopted over years to improve the productivity of the agriculture field. One of the major challenges in agriculture is the proper monitoring of the soil health, the environment , and adjusting the irrigation according to this observation. Traditionally, Indian farmers have adopted manual observation based technique which has resulted in either excessive use of pesticides or under use of watering which results in less efficient and less productive crops.  This project is about developing an agriculture field monitoring system comprising of multiple sensors _light sensor, moisture sensor, temperature sensor, and  network of nodes in  mesh topology. The monitoring data should be sent to cloud server.

# Hardware Requirements
NodeMCU : for working as a node in the mesh network, some nodes will work as sensor clients, one node will work as a central node(for collecting data from all the sensor clients) and one will work as a gateway to send the data to the cloud.
Sensors : sensors such as, Temperature sensor, Moisture sensor can be used for sensing field data.
Software: Arduino IDE
Cloud Service: ThingSpeak

# Mesh Network
A mesh network is a network in which the devices or nodes are connected  so that at least some, and sometimes all, have multiple paths to other nodes. This creates multiple routes for information between pairs of users, increasing the resilience of the network in case of a failure of a node or connection. For building mesh network painless mesh is used in out project

# Painless Mesh
Painless Mesh is a library that takes care of the particulars of creating a simple mesh network using esp8266 hardware. The goal is to allow the programmer to work with a mesh network without having to worry about how the network is structured or managed. For using painless mesh we used library called painless mesh
Dependencies :
ArduinoJson
TaskScheduler
ESPAsyncTCP
EasyTransfer
After mesh is created we need to transfer the data to cloud service, we used a gate way to transfer data which is connected in serial communication.























