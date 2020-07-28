# 에너르기파(초음파센서 거리측정센서)

우리가 프로젝트를 하기 위해서는 여러가지 데이터들을 필요로한다. 그 중에서 
사물과 대상간의 거리를 구하는 것은 비접촉식 센서나 접촉식 센서로 구분 되어 있다. 
거리 측정에 사용하는 전자기파는 초음파, 마이크로웨이브, 적외선, 가시광 등을 이요한다. 
이 중에서 마이크로웨이브를 이용한 방식을 레이더(Radar), 레이저를 이용한 방식을 라이다(LiDAR)라고 한다.
거리측정용으로 사용하는 센서들의 비교 성능은 아래 표와 같다. 이러한 특성에 따ㅏ 자동차에 사용되는
거리측정용 센서들의 용도는 아래 그림과 같다.  


![표](img/음파측정.PNG)  



![표](img/센서가시거리.PNG)  
이 중 우리는 싸고 간단한 초음파 센서를 사용 하고자 한다.  
　  
　  
![센서](img/ultrasonic.jpg)  

초음파 거리측정 센서는 TX와 RX가 있는데 TX를 통해 신호를 보내고 RX를 통해 신호를 받은 시간차이를 통해
거리가 얼마나 되는지 알 수 있다. 우리가 실제로 코드에 입력하는 것을 보아도 Trig에서
high신호를 보내고 echo에서 신호를 받으면 LOW가 되게 하여 거리가 얼마나 되는지 측정 할 수 있다.  
![원리](img/reason.png)  
　  
이 센서를 사용 할때 데이터 값이 0으로 가는 것은 확인 할 수 없을 것이다.
그 이유로 하드 웨어의 한계로 알 수 있는데 
    
      digitalWrite(trigPin, HIGH); 
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
이 코드를 보면 사이에 delayMicroseconds(10);이 들어간것을 확인 할 수 있다.
TRIG에서 신호를 보내고 ECHO에서 신호를 받아 들이는 대까지 
중간에 10mmsec 밑으로 delay가 없으면 데이터를 ECHO에서 받아 들일 수가 없다. 그리고 소스에
    
        distance = ((float)(340*duration) / 1000)/2;
이렇게 함수를 쓴 이유로 음파의 속도가 1초당 340m를 갈 수 있으므로 속도는 340m/s으로 생각하고
340*10^6 mm/sec 이므로 신호를 보냈을 때 돌아 오기 까지의  
 시간을 측정하여 거리를 구하면
시간 * 17 / 1000공식이 나온다.
　  

실험내용
***  
사물과 센서와의 거리 측정에 따른 LED 점등  

　  
준비물
***
아누이노 우노, 브레드 보드, 점퍼선, LED, 저항, HC-SR04  
　  
![보드](img/board.PNG)  
　  
소스 코드
***  

    
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
