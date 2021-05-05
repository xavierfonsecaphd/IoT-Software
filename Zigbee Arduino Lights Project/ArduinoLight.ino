#include <SoftwareSerial.h>

SoftwareSerial software_Serial(4, 5); // RX, TX

char recvChar;
String readString;
int relayButton = 7;

void setup() {

  // Open serial communications and wait for port to open:
  Serial.begin(38400);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  pinMode(relayButton, OUTPUT);
  digitalWrite(relayButton, LOW);
  
  // set the data rate for the SoftwareSerial port
  software_Serial.begin(38400);

  delay(2000);

  Serial.println("Device Started.");
  software_Serial.println("P2P 0001 Bom dia Interruptor. Bora?");
}


void loop()
{
  if (software_Serial.available())
  {
    readString = "";
    while(software_Serial.available())
    {
      recvChar = software_Serial.read();
      readString += recvChar;
      
    }
    
    if (readString[0] == '1')
    {
        Serial.println("ON!");
        digitalWrite(relayButton, HIGH);
    }
    if (readString[0] == '0')
    {
        Serial.println("OFF!");
        digitalWrite(relayButton, LOW);
    }
  }
  if(Serial.available())
  {
    readString = "P2P 0001 ";
    while(Serial.available())
    {
      recvChar = Serial.read();
      readString += recvChar; //makes the string readString
    }
    software_Serial.println(readString); 
  }
}

