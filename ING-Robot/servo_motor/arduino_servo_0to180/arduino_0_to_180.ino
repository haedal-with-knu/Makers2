/* 서보모터를 0도 부터 180도 까지 움직이게 한다.

*/
#include <Servo.h>                     //servo 함수 호출
Servo servo;                           //Servo 객체 생성
                                   

void setup(){                          //처음 시작히전에 Servo의 핀과 Serial 창을 띠우기 위해 셋팅을 한다.
  servo.attach(7);                     //서보 모터의 signal 핀을 자신이 꼽은 곳에 설정한다.
  Serial.begin(9600);                  //Serial 창을 띠우고 통신 속도를 입력한다 Serial.begin(speed)
}
void loop(){                           //무한으로 반복할 알고리즘을 적기 위한 공간이다.
 for(int i =0; i <=180;i++){           //i를 0부터 180 까지 1씩 더하는 반복문이다
  servo.write(i);                      // servo.write(degree)로 서보 모터의 각도를 조절한다.
  delay(10);                           // 지연시간을 10ms로 지정한다.
 }
  for(int i =180; i >= 0;i--){         //i를 180부터 0까지 1씩 빼는 반복문이다.
  servo.write(i);                      // servo.write(degree)로 서보 모터의 각도를 조절한다.
  delay(10);                           // 지연시간을 10ms로 지정한다.
 }
}
