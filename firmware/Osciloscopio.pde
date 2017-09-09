/*-----------------------------------------------------
Author:  --<>
Date: 2017-08-22
Description:

-----------------------------------------------------*/

int sensorPin = 13;    
int sensorValue = 0;
u8 c=0;
void setup() {
   pinMode(sensorPin,INPUT);
   digitalWrite(9,HIGH);
   digitalWrite(8,HIGH);
}

void loop() {
  digitalWrite(9,LOW);
  c = CDC.getKey();
  if(c=='i'){
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
  while(1){
       sensorValue = analogRead(sensorPin);    
      sensorValue=(sensorValue/2);
      if(sensorValue<10)CDC.printf("00%d\n",sensorValue);
      if(sensorValue<100)CDC.printf("0%d\n",sensorValue);
      else CDC.printf("%d\n",sensorValue);  // 1 digit after decimal comma
      }
  
  }
           
  

}
