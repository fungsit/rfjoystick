#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define TRANSMITTER 1  //comment out for Reciever code
#define LED 5
#define KEY 6
#define BUTTON_A 2
#define BUTTON_B 3
#define VRX A0
#define VRY A1
#define BAUD 9600
RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
void setup() {
  Serial.begin(BAUD);
  GPIO_SETUP();
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00001
  radio.openReadingPipe(1, addresses[1]); //channel 0 will override writing pipe, use channel 1
  radio.setPALevel(RF24_PA_MIN);  //set PA to minimum for close distance
}
void loop() {
 
#ifdef TRANSMITTER
    delay(5);
    radio.stopListening();
    int potValueX = analogRead(VRX);
    int potValueY = analogRead(VRY);
    int sw = digitalRead (KEY);
    int button_A = digitalRead (BUTTON_A);
    int button_B = digitalRead (BUTTON_B);
    int angleValueX = map(potValueX, 0, 1023, 0, 180);
    int angleValueY = map(potValueY, 0, 1023, 0, 180);
  
    Serial.print(angleValueX,DEC);
    Serial.print("  ");
    Serial.print(angleValueY,DEC);
    Serial.print(" ");
    Serial.print(sw,DEC);
    Serial.print(" ");
    Serial.print(button_A,DEC);
    Serial.print(" ");
    Serial.println(button_B,DEC);
//    radio.write(&angleValueX, sizeof(angleValueX));
//    delay(10);
//    radio.write(&angleValueY, sizeof(angleValueY));
//    delay(10);
//    radio.write(&sw,sizeof(sw));
//    delay(10);
#else // RECIEVER 
    delay(5);
    radio.startListening();
    while (!radio.available());
    int buf = 0;
    radio.read(&buf, sizeof(buf));
    Serial.println(buf);
    if(buf == 0) {
        digitalWrite(LED, HIGH);
      }
      else {
        digitalWrite(LED, LOW);
      }
#endif
  
//Test Code
//#ifdef TRANSMITTER
//    Serial.println("I'm transmitter");
//    radio.stopListening();
//    const char text[] = "Hello World";
//    radio.write(&text, sizeof(text));
//    delay(1000);
//#else    
//    Serial.println("I'm reciever");
//    radio.startListening();
//    if (radio.available()) {
//      char text[32] = "";
//      radio.read(&text, sizeof(text));
//      Serial.print("recieved something: ");
//      Serial.println(text);
//    }
//#endif
}

void GPIO_SETUP() {
  pinMode(LED, OUTPUT);
  pinMode(VRX, INPUT);
  pinMode(VRY, INPUT);
  pinMode(KEY, INPUT_PULLUP);
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  
  }
