/* 

*/
#include <Servo.h>                     //servo 함수 호출
Servo servo;                           //Servo 객체 생성

int motor = 7;                                   
int angle = 0;
void setup(){                          //처음 시작히전에 Servo의 핀과 Serial 창을 띠우기 위해 셋팅을 한다.
  servo.attach(motor);                     //서보 모터의 signal 핀을 자신이 꼽은 곳에 설정한다.
  Serial.begin(9600);                  //Serial 창을 띠우고 통신 속도를 입력한다 Serial.begin(speed)
  
  Serial.println("Enter the u or d");
  Serial.println("u = angle + 15");
  Serial.println("d = angle -15\n");
  Serial.println("Variable       Current degree");
  servo.write(0);     
}
void loop(){                           //무한으로 반복할 알고리즘을 적기 위한 공간이다.
if(Serial.available())  // 시리얼모니터가 사용가능할 때
  {
    char input = Serial.read(); // 문자 입력받기
    
    if(input == 'u')    // u 키를 누를 때
    {
      Serial.print("+15");  // '+15'를 시리얼 모니터에 출력
      if(angle>=180){
      angle = 180;
      Serial.print("각도를 더 늘릴수 없습니다!");}
      else{
      angle +=15;
                    
        servo.write(angle); 
        delay(10);
      
      Serial.print("\t\t");
      Serial.println(angle);}  // 현재 각도 출력
    } 
    else if(input == 'd')   // 'd'키를 입력했을 때
    {
      Serial.print("-15");  // '-15'를 시리얼 모니터에 출력
      if(angle<=0){
      angle = 0;
      Serial.print("각도를 더 줄일수 없습니다!");}
      else{
      angle -=15;
                    
        servo.write(angle); 
        delay(10);
      
      Serial.print("\t\t");
      Serial.println(angle);}  // 현재 각도 출력
    }
    else if(input == '\n')
    {
      Serial.println("");
    }
    else
    {
      Serial.println("잘못된 입력입니다!!");
    }
    }
  }
