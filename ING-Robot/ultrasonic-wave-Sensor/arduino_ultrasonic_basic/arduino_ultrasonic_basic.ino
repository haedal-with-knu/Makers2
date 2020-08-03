
int echo = 7;
int trig = 6;
int led[6]= {8, 9, 10, 11, 12, 13};

void setup()
{
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  for(int i=0; i<6; i++)
    pinMode(led[i], OUTPUT);
}

void loop()
{
  long duration, distance;
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = ((float)(17*duration) / 1000)/2;
  Serial.print(distance);
  Serial.println(" cm");

  if(distance < 10)
    digitalWrite(led[0],HIGH);
  else if(distance<15)
    digitalWrite(led[1],HIGH);
  else if(distance<20)
    digitalWrite(led[2],HIGH);
  else if(distance<25)
    digitalWrite(led[3],HIGH);
  else if(distance<30)
    digitalWrite(led[4],HIGH);
  else if(distance<35)
    digitalWrite(led[5],HIGH);
  else
    digitalWrite(led,LOW);
  delay(500);
}
