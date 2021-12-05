int INs[] = {2,3,4,5};
int EN = 6;
void setup() {
  pinMode(EN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(INs[0] == 1 && INs[1] == 0 && INs[2] == 1 && INs[3] == 0){
    Serial.begin("Forward");
    analogWrite(EN, 800);
  }
  else if(INs[0] == 1 && INs[1] == 0 && INs[2] == 0 && INs[3] == 1){
    Serial.begin("RIGHT");
    analogWrite(EN, 600);
  }
  else if(INs[0] == 0 && INs[1] == 1 && INs[2] == 1 && INs[3] == 0){
    Serial.begin("Left");
    analogWrite(EN, 600);
  }
  else{
    Serial.begin("Stop");
    analogWrite(EN, 800);
  }
  
  
  
  delay(1000);
}