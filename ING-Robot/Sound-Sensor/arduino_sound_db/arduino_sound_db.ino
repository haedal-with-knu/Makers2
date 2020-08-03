int SoundSensor = A0;     // 사운드 센서 설정


void setup() {               
  Serial.begin(9600); // 시리얼모니터 사용
  pinMode(SoundSensor,INPUT)
}

void loop() {     
  int level = analogRead(SoundSensor);
  Serial.println(level);
  delay(300);
}
