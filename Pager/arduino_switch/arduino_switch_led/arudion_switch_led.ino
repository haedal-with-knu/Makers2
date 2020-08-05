const int swit =12;
const int led = 10;
void setup(){
    pinMode(swit, INPUT_PULLUP);
    pinMode(led, OUTPUT);
    Serial.begin(9600);

    
}
void loop(){
    int button = digitalRead(swit);
    Serial.println(button);
    if(button == HIGH)
    {
        digitalWrite(11,HIGH);
        delay(1000);
        digitalWrite(11,LOW);
    }

}