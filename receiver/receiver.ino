//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

// motor
const int IN[] = {4, 5, 6, 7};

void setup()
{
  while (!Serial);
    Serial.begin(9600);
  
  radio.begin();
  
  //set the address
  radio.openReadingPipe(0, address);
  
  //Set module as receiver
  radio.startListening();
}

void writeToMotor(char logic, int index){
  if(logic == 'H')
  digitalWrite(IN[index], HIGH);
  else
  digitalWrite(IN[index], LOW);
}
void loop()
{
  //Read the data if available in buffer
  if (radio.available())
  {
    char command[10] = {0};
    radio.read(&command, sizeof(command));
    for(int i=0;i<4;i++)
      writeToMotor(command[i], i);    
  }
}
