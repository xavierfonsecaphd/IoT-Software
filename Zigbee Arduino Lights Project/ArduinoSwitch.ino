#include <SoftwareSerial.h>

SoftwareSerial software_Serial(4, 5); // RX, TX


//int i, count;
int state;
bool cmdSent = false;
char recvChar;
String readString;
int buttonPin = 2;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(38400);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  pinMode(buttonPin, INPUT);      // sets the digital pin as output

  // set the data rate for the SoftwareSerial port
  software_Serial.begin(38400);

  delay(2000);

  Serial.println("Device Started.");
  software_Serial.println("P2P 0000 Bom dia meu Mestre. Vamos dar Luz?");
}


void loop()
{

    state = digitalRead(buttonPin);
    if ((state == HIGH) && (!cmdSent))
    {
      cmdSent = true;
      Serial.println("SENT");
      software_Serial.println("P2P 0000 1");
    }
    else if ((state == LOW) && (cmdSent))
    {
      Serial.println("Idle");
      cmdSent = false;
      software_Serial.println("P2P 0000 0");
    }


  
  if (software_Serial.available())
  {
    readString = "";
    while(software_Serial.available())
    {
      recvChar = software_Serial.read();
      readString += recvChar;
      
    }
    readString += '\n'; 
    Serial.print(readString);
  }

}


      //readString += recvChar; //makes the string readString
      //count ++;
 //for (i = 0; i < count; i++)
    //{
    //  software_Serial.print(readString[i]); 
    //}

    //readString += '\n'; 
    //software_Serial.print("\nP2P 0000 " + readString); 




