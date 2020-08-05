const int swit = 12;
void setup(){
    pinMode(swit, INPUT_PULLUP);
    Serial.begin(9600);

    
}
void loop(){
    int button = digitalRead(swit);
    Serial.println(button);
    delay(1);
}