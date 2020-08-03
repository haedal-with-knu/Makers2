   const int buzzer = 9; //핀을 다른 PWM pin으로도 사용 할 수 있지만 
                        //3 또는 11번은 tone 함수를 받을 수 없다. 
                       
    const int songspeed = 1.5; //값을 2로 바꾸면 조금더 느린 버전으로 노래를 할 수 있다.
    //*****************************************
    #define NOTE_C4  262    
    #define NOTE_D4  294    //이렇게 Define하는 이유는 int나 float long double등으로 변수를 생성 할시
    #define NOTE_E4  330    //메모리에 데이터가 저장되므로 데이터가 쓰인다. 하지만 Define은 뒤에 ';'가 붙지 않는다.
    #define NOTE_F4  349    //상수는 메모리를 차지하지 않는다.
    #define NOTE_G4  392
    #define NOTE_A4  440
    #define NOTE_B4  494
    #define NOTE_C5  523
    #define NOTE_D5  587
    #define NOTE_E5  659
    #define NOTE_F5  698
    #define NOTE_G5  784
    #define NOTE_A5  880
    #define NOTE_B5  988
    //*****************************************
    int notes[] = {       0은 reset하기 위한 것이다.
       NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
       NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
       NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
       NOTE_A4, NOTE_G4, NOTE_A4, 0,
       
       NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
       NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
       NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
       NOTE_A4, NOTE_G4, NOTE_A4, 0,
       
       NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
       NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
       NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
       NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
       
       NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
       NOTE_D5, NOTE_E5, NOTE_A4, 0, 
       NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
       NOTE_C5, NOTE_A4, NOTE_B4, 0,
    
       NOTE_A4, NOTE_A4, 
       //Repeat of first part
       NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
       NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
       NOTE_A4, NOTE_G4, NOTE_A4, 0,
    
       NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
       NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
       NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
       NOTE_A4, NOTE_G4, NOTE_A4, 0,
       
       NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
       NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
       NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
       NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
       
       NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
       NOTE_D5, NOTE_E5, NOTE_A4, 0, 
       NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
       NOTE_C5, NOTE_A4, NOTE_B4, 0,
       //End of Repeat
    
       NOTE_E5, 0, 0, NOTE_F5, 0, 0,
       NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
       NOTE_D5, 0, 0, NOTE_C5, 0, 0,
       NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,
    
       NOTE_E5, 0, 0, NOTE_F5, 0, 0,
       NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
       NOTE_D5, 0, 0, NOTE_C5, 0, 0,
       NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4
    };
    //*****************************************
    int duration[] = {        
      125, 125, 250, 125, 125, 
      125, 125, 250, 125, 125,
      125, 125, 250, 125, 125,
      125, 125, 375, 125, 
      
      125, 125, 250, 125, 125, 
      125, 125, 250, 125, 125,
      125, 125, 250, 125, 125,
      125, 125, 375, 125, 
      
      125, 125, 250, 125, 125, 
      125, 125, 250, 125, 125,
      125, 125, 250, 125, 125,
      125, 125, 125, 250, 125,
    
      125, 125, 250, 125, 125, 
      250, 125, 250, 125, 
      125, 125, 250, 125, 125,
      125, 125, 375, 375,
    
      250, 125,
      125, 125, 250, 125, 125,
      125, 125, 250, 125, 125,
      125, 125, 375, 125, 
      
      125, 125, 250, 125, 125, 
      125, 125, 250, 125, 125,
      125, 125, 250, 125, 125,
      125, 125, 375, 125, 
      
      125, 125, 250, 125, 125, 
      125, 125, 250, 125, 125,
      125, 125, 250, 125, 125,
      125, 125, 125, 250, 125,
    
      125, 125, 250, 125, 125, 
      250, 125, 250, 125, 
      125, 125, 250, 125, 125,
      125, 125, 375, 375,

      
      250, 125, 375, 250, 125, 375,
      125, 125, 125, 125, 125, 125, 125, 125, 375,
      250, 125, 375, 250, 125, 375,
      125, 125, 125, 125, 125, 500,
    
      250, 125, 375, 250, 125, 375,
      125, 125, 125, 125, 125, 125, 125, 125, 375,
      250, 125, 375, 250, 125, 375,
      125, 125, 125, 125, 125, 500
    };
    
    void setup() {
      for (int i=0;i<203;i++){              //총 노드 수는 203개다.
      int wait = duration[i] * songspeed;
      tone(buzzer,notes[i],wait);          
      delay(wait);}                        //
    }
    
    void loop() {
    
    }