//nRF24L01 communication 2 ways Arduino B

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 8); // CE, CSN
const byte addresses [][6] = {"00001", "00002"};    //Setting the two addresses. One for transmitting and one for receiving
int button_pinB = 6;
int led_pinB = 13;
char button_stateA;
boolean button_stateB = 0;

int DELAY = 5;
const int IN[] = {2,3,4,5};
void setup() {
//  pinMode(button_pinB, INPUT_PULLUP);
  
  pinMode(led_pinB, OUTPUT);
  radio.begin();                            //Starting the radio communication
  radio.openWritingPipe(addresses[0]);      //Setting the address at which we will send the data
  radio.openReadingPipe(1, addresses[1]);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);            //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  Serial.begin(9600);
}
int prevTime = millis();
int currTime = 0;
int interval = 1000;

const String commands[] = {"LHLH", "LHHL", "HLLH", "HHHH"};
void writeToMotor(char logic, int index){
  if(logic == 'H')
  digitalWrite(IN[index], HIGH);
  else
  digitalWrite(IN[index], LOW);
}
void loop() 
{
  currTime = millis();
  if(currTime - prevTime >= interval){
    radio.stopListening();
    char data = '0';
    radio.write(&data, sizeof(data));
    delay(10);
    prevTime = currTime;  
  }
  radio.startListening();
  if(radio.available()){
    char modelOutput;
    radio.read(&modelOutput, sizeof(modelOutput));
    Serial.print("Model output : ");
    Serial.println(modelOutput);
    int commandIndex = modelOutput - '0';
    for(int i=0;i<4;i++)
      writeToMotor(commands[commandIndex][i], i);  
  }
}
