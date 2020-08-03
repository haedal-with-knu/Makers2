#include <SoftwareSerial.h>
#define RX 8
#define TX 7
SoftwareSerial bluetooth(RX, TX);

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);

}

void loop() {
  char val = bluetooth.read();
  if(bluetooth.available()){
    Serial.write(bluetooth.read());
  }
  if(val == 'a')
  {
    digitalWrite(3,HIGH);
  }

  if(val == 'b')
  {
    digitalWrite(5,HIGH); 
    Serial.print("a");
  }
  if(val == 'c')
  {
    digitalWrite(3,LOW);
  }
  if(val == 'd')
  {
    digitalWrite(5,LOW);
  }


}
