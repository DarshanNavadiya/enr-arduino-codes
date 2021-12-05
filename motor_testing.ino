int ENA = 5;
int ENB = 6;
int ir1 = 8;
int ir2 = 9;
int ir3 = 10;

void setup() {
  pinMode(ENA, OUTPUT); 
  pinMode(ENB, OUTPUT);
  pinMode(ir1, OUTPUT);
  pinMode(ir2, OUTPUT);
  pinMode(ir3, OUTPUT);
}

void loop() {
  ir1_reading = digitalRead(ir1);
  ir2_reading = digitalRead(ir2);
  ir3_reading = digitalRead(ir3);
  if(!(ir1_reading == 0 || ir2_reading == 0 || ir2_reading == 0)){
    analogWrite(ENA, 105); //ENA pin
    analogWrite(ENB, 95); //ENB pin    
    } else{
    analogWrite(ENA, 0); //ENA pin
    analogWrite(ENB, 0); //ENB pin  
      }
  
}
