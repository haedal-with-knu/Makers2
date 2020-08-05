
#include <SPI.h>

#include <MFRC522.h>



constexpr uint8_t RST_PIN = 9;          //구성가능, 일반 핀 참조

constexpr uint8_t SS_PIN = 10;           //구성가능, 일반 핀 참조



MFRC522 mfrc522(SS_PIN, RST_PIN);               //MFRC522 인스턴스 생성



void setup() {

 Serial.begin(9600);           //시리얼 통신 시작

 while (!Serial);            //직렬 포트가 열려있지 않은 경우 (ATMEGA32U4 기반 Arduino 추가

 SPI.begin();               //SPI 버스 시작

 mfrc522.PCD_Init();            //MFRC522 시작

 mfrc522.PCD_DumpVersionToSerial();              //PCD의 세부정보 표시 - MFRC522 카드 세부정보 표시

 Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

}



void loop() {

 if ( ! mfrc522.PICC_IsNewCardPresent()) {   
     printf("Error 1");          //새 카드 찾기

  return;

 }   



 if ( ! mfrc522.PICC_ReadCardSerial()) {              //카드 중 하나 선택
 printf("Error 1");

  return;

 }



 mfrc522.PICC_DumpToSerial(&(mfrc522.uid));            //카드에 대한 디버그 정보 덤프, PICC_HaltA()가 자동으로 호출 됨
}
