//nRF24L01 communication 2 ways Arduino A

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 8); // CE, CSN
const byte addresses [][6] = {"00001", "00002"};  //Setting the two addresses. One for transmitting and one for receiving
//int button_pinA = 4;
int led_pinA = 13;
//boolean button_stateA = 0;
char button_stateB = 0;
int out[2]={0,1};
const int DELAY=5;

void setup() {
//  pinMode(button_pinA, INPUT_PULLUP);
  pinMode(led_pinA, OUTPUT);
  radio.begin();                           //Starting the radio communication
  radio.openWritingPipe(addresses[1]);     //Setting the address at which we will send the data
  radio.openReadingPipe(1, addresses[0]);  //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN); //You can set it as minimum or maximum depending on the distance between the transmitter and receiver. 
  Serial.begin(9600);
}
int isCarSecured = 1;
void loop() {
  if(Serial.available() && isCarSecured == 1){
    radio.stopListening();
    char modelOutput = Serial.read();
    radio.write(&modelOutput, sizeof(modelOutput));
  }
  radio.startListening();
  if(radio.available()){
    char IR_Sensor;
    radio.read(&IR_Sensor, sizeof(IR_Sensor));
    Serial.println(IR_Sensor);
    if(IR_Sensor == '1'){
      isCarSecured = 0;
    }else{
      isCarSecured = 1;
    }
  }
}
