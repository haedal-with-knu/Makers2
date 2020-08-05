# include <SPI.h>

# include <MFRC522.h>

constexpr uint8_t RST_PIN = 9;          //구성가능, 일반 핀 참조

constexpr uint8_t SS_PIN = 10;           //구성가능, 일반 핀 참조

MFRC522 mfrc522(SS_PIN, RST_PIN);               //MFRC522 인스턴스 생성
const byte KEYB[] = { 0xDE, 0xAD, 0xBE, 0xEB, 0xDE, 0xAD};



void setup() {

 Serial.begin(9600);           //시리얼 통신 시작

 SPI.begin();               //SPI 버스 시작

 mfrc522.PCD_Init();            //MFRC522 시작

 mfrc522.PCD_DumpVersionToSerial();              //PCD의 세부정보 표시 - MFRC522 카드 세부정보 표시

 Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

 Serial.println("A 키를 이용하여 데이터를 쓰고 읽는 방법을 보여주는 예제");

}



void loop() {

    byte buffer[18];
    byte size =sizeof(buffer);

 if ( ! mfrc522.PICC_IsNewCardPresent()) {   
     printf("Error 1");          //새 카드 찾기

  return;

 }   



 if ( ! mfrc522.PICC_ReadCardSerial()) {              //카드 중 하나 선택
 printf("Error 2");

  return;

 }
 // 카드 선택 되었으면 mfrc522.uid에 UID 정보 16진수를 출력
 Serial.print("카드 UID:");
 for (byte i = 0; i < mfrc522.uid.size; i++)
 {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
 }
 Serial.println();


// 타입 찾기
 byte piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
 Serial.print("PICC 타입: ");
 Serial.println(mfrc522.PICC_GetTypeName(piccType));

 if( piccType != MFRC522::PICC_TYPE_MIFARE_MINI
 && piccType != MFRC522::PICC_TYPE_MIFARE_1K
 && piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
     Serial.println("이 예제는 MIFARE Classic 카드에서만 동작합니다.");
     return;
 }


 // KeyA를 초기화 및 새로 사용 할 keyB준비
 MFRC522::MIFARE_Key keyA,keyB;                        // 신규 클래스 선언 
 //
 byte trailerBuffer[] = { 255,255,255,255,255,255,  0,0,0,0, 255,255,255,255,255,255}; //keep default keys.

 for (byte i = 0; i<6; i++){
     keyA.keyByte[i] = 0xFF;

 }
  // 이 예제에서는 1번째 섹터의 0번과 3번 블록 (sector Trailer)을 사용
byte valueBlockA = 8;
byte trailerBlock = 11;


//A키로 인증
Serial.println("A키로 인증 중 ...");
byte status;
status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &keyA, &(mfrc522.uid));
if(status != MFRC522::STATUS_OK){
    Serial.print("PCD_Authenticate() 실패: ");
    Serial.print(mfrc522.GetStatusCodeName(status));
    return;
}
// 저장할 데이터 (16bytes)
byte value1Block[] = {
    0,0,0,0,  0,0,0,0,   0,0,0,0,   0,0,0,0, valueBlockA,~valueBlockA,valueBlockA,~valueBlockA
    };


// 1 번째 블록 (value block)에 데이터 기록
Serial.println("1번째 블록 기록 중 : 2번째 섹터의 첫번째 블록");
print_buffer(value1Block);
status = mfrc522.MIFARE_Write(valueBlockA, value1Block, 16);
if (status != MFRC522::STATUS_OK)
{
    Serial.print("MIFARE_Write() 실패 :");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
}

Serial.println("1 번째 블록 읽는 중: 2번 째 섹터의 첫번째 블록");
size = sizeof(buffer);
status = mfrc522.MIFARE_Read(valueBlockA, buffer, &size);
if (status != MFRC522::STATUS_OK)
{
    Serial.print("MIFARE_Read() 실패 :");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
}

print_buffer(buffer);

//PICC를 멈춤
mfrc522.PICC_HaltA();

//PCD의 Crypto를 멈춥니다
mfrc522.PCD_StopCrypto1();

// 스케치도 멈추게 합니다.
while(true){
    ;
    
}
}
void print_buffer(byte buffer[])
{
    Serial.print(String("buffer[] = {"));
    for(int i = 0; i < 16; i++){
        if(i != 0)
        Serial.print(',');

        Serial.print(buffer[i]);
        
    }
    Serial.print("}");
}