#define BLYNK_TEMPLATE_ID "TMPLoLw1jQf8"
#define BLYNK_DEVICE_NAME "ServoControl"
#define BLYNK_AUTH_TOKEN "_U01qp0mch2XJiFCRh15WF53EHvKuiFf"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

#define MA1 14
#define MA2 12
#define MB1 13
#define MB2 15
#define LDR_pin 
#define LED_pin 2
#define trigpin 6 //pinout
#define echopin 7//pinout
#define buzzer_pin 9 //pinout
Servo servo1;
BlynkTimer timer;

char auth[ ] = "_U01qp0mch2XJiFCRh15WF53EHvKuiFf";
char ssid[ ] = "AndroidAPF59A";
char pass[ ] = "candles101";

float duration, distance; //ultrasonic ip op variables 
int ldr_input; //ldr analog input variable

//void myTimer(){(CHECK3)
 // Blynk.virtualWrite(V5, ldr_input);
//}

void setup()
{
  Serial.begin(115200);
  servo1.attach(5); //servo pin connected
  Blynk.begin(auth, ssid, pass); //blynk authentication
  //timer.setInterval(1000, myTimer); (CHECK2)
  //motor connections
  pinMode(MA1, OUTPUT);
  pinMode(MA2, OUTPUT);
  pinMode(MB1, OUTPUT);
  pinMode(MB2, OUTPUT);
  //ultrasonic pins 
  pinMode(echopin, INPUT);
  pinMode(trigpin, OUTPUT);
  //ldr
  pinMode(LDR_pin, INPUT);
  //led 
  pinMode(LED_pin, OUTPUT);
}

void loop()
{
  Blynk.run(); //start of the blynk function 
  ldr_input=analogRead(A0); //ldr analog input 
  
  if(ldr_input<500){ //if light intensity low, turn on LED 
    digitalWrite(LED_pin, HIGH);
    Serial.println(ldr_input);
  }
  
  else{ //if light intensity higher than 500, display on blynk
    digitalWrite(LED_pin, LOW);
    Serial.println(ldr_input); 
    //blynk code to display light intensity (ldr input) 
    //timer.run();  (CHECK1)
    Blynk.virtualWrite(V5, ldr_input);
  }
  
  //ultrasonic input from transducer
  digitalWrite(trigpin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);
  
  duration=pulseIn(echopin,HIGH); //reflected wave time calculation in microseconds
  distance=(duration/2)*0.0343; //distance (in cm) calc w speed of sound
  if (distance<=8){
    //buzzer start code
    tone(buzzer_pin, 500); //pin number and frequency 
  }
  
}

BLYNK_WRITE(V1){ //moving forward
 int pinValue = param.asInt();
 if(pinValue==0)
 {
   // Stop
   digitalWrite(MA1,LOW);
   digitalWrite(MA2,LOW);
   digitalWrite(MB1,LOW);
   digitalWrite(MB2,LOW);
   Serial.println("Stopping");
 }
 else
 {
   // Forward
   digitalWrite(MA1,HIGH);
   digitalWrite(MA2,LOW);
   digitalWrite(MB1,HIGH);
   digitalWrite(MB2,LOW);
   Serial.println("Moving Forward");
 }
}

BLYNK_WRITE(V2){ //moving backward
 int pinValue = param.asInt();
 if(pinValue==0)
 {
   // Stop
   digitalWrite(MA1,LOW);
   digitalWrite(MA2,LOW);
   digitalWrite(MB1,LOW);
   digitalWrite(MB2,LOW);
   Serial.println("Stopping");
 }
 else
 {
   // Backward
   digitalWrite(MA1,LOW);
   digitalWrite(MA2,HIGH);
   digitalWrite(MB1,LOW);
   digitalWrite(MB2,HIGH);
   Serial.println("Moving Backwards");
 }
}

BLYNK_WRITE(V3){ //moving left
 int pinValue = param.asInt();
 if(pinValue==0)
 {
   // Stop
   digitalWrite(MA1,LOW);
   digitalWrite(MA2,LOW);
   digitalWrite(MB1,LOW);
   digitalWrite(MB2,LOW);
   Serial.println("Stopping");
 }
 else
 {
   // Left
   digitalWrite(MA1,HIGH);
   digitalWrite(MA2,LOW);
   digitalWrite(MB1,LOW);
   digitalWrite(MB2,LOW);
   Serial.println("Moving Left");
 }
}

BLYNK_WRITE(V4){ //moving right
 int pinValue = param.asInt();
 if(pinValue==0)
 {
   // Stop
   digitalWrite(MA1,LOW);
   digitalWrite(MA2,LOW);
   digitalWrite(MB1,LOW);
   digitalWrite(MB2,LOW);
   Serial.println("Stopping");
 }
 else
 {
   // Right
   digitalWrite(MA1,LOW);
   digitalWrite(MA2,LOW);
   digitalWrite(MB1,HIGH);
   digitalWrite(MB2,LOW);
   Serial.println("Moving Right");
 }
}
