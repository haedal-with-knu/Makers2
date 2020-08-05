#include <SPI.h>

#include <MFRC522.h>
#include <Servo.h>
#define servoPin 8
Servo servo;
int pos = 0;



constexpr uint8_t RST_PIN = 9;          //구성가능, 일반 핀 참조

constexpr uint8_t SS_PIN = 10;           //구성가능, 일반 핀 참조



MFRC522 rfid(SS_PIN, RST_PIN);               //MFRC522 인스턴스 생성



void setup() {

 Serial.begin(9600);           //시리얼 통신 시작

 while (!Serial);            //직렬 포트가 열려있지 않은 경우 (ATMEGA32U4 기반 Arduino 추가

 SPI.begin();               //SPI 버스 시작

 rfid.PCD_Init();            //MFRC522 시작

 rfid.PCD_DumpVersionToSerial();              //PCD의 세부정보 표시 - MFRC522 카드 세부정보 표시

 Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
 servo.attach(servoPin);
 servo.write(0);

}



void loop() {

 if ( ! rfid.PICC_IsNewCardPresent()) {             //새 카드 찾기

  return;

 }   



 if ( ! rfid.PICC_ReadCardSerial()) {              //카드 중 하나 선택

  return;

 }

  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for(byte i=0; i< rfid.uid.size;i++)
  {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0": " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
    content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0": " "));
    content.concat(String(rfid.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message :");
  content.toUpperCase();
  if(content.substring(1)=="F2 A3 BA 79")
  {
    Serial.println("Authorized access");
    Serial.println();
    servo.write(180);
    delay(3000);
    servo.write(0);
    
    
  }
  else
  Serial.println("Error");

}
