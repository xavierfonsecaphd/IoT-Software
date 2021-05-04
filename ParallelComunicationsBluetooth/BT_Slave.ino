// This module work as Slave
// Upload this sketch into Arduino and press reset

#include <SoftwareSerial.h> //Software Serial Port

#define RxD 5
#define TxD 4

SoftwareSerial blueToothSerial(RxD,TxD);

void setup() 

{ 
 Serial.begin(38400);
 pinMode(RxD, INPUT);
 pinMode(TxD, OUTPUT);
 
 setupBlueToothConnection(); 
} 

void loop() 
{ 
 char recvChar;

 while(1)
 {
   if(blueToothSerial.available())
   {//check if there's any data sent from the remote bluetooth shield
     recvChar = blueToothSerial.read();
     Serial.print(recvChar);
   }
   
   if(Serial.available())
   {//check if there's any data sent from the local serial terminal, you can add the other applications here

     recvChar = Serial.read();
     blueToothSerial.print(recvChar);
   }
 }
} 

void setupBlueToothConnection()
{

 blueToothSerial.begin(38400); //Set BluetoothBee BaudRate to default baud rate 38400
 delay(2000); // This delay is required.
 Serial.println("The slave bluetooth is inquirable!");
 blueToothSerial.flush();
}
