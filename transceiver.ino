//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

int counter = 0;
const int delay_counter = 5000;

void setup()
{
  radio.begin();
  
  //set the address
  radio.openWritingPipe(address);
  
  //Set module as transmitter
  radio.stopListening();
}
void loop()
{
  const char forward[] = "HLHL";
  const char right[] = "HLLLL";
  const char left[]= "LLHL";
  const char back[] = "LLLL";

  if(counter == 0){
    radio.write(&forward, sizeof(forward));
  }else if(counter == 1){
    radio.write(&right, sizeof(right));
  }else if(counter == 2){
    radio.write(&left, sizeof(left));
  }else{
    radio.write(&back, sizeof(back));
    counter = -1;
  }
  
  counter++;
  delay(delay_counter);
}