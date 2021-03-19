#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "W6C-Nc75WLsfUYdNsWAmxmgyJiW6Yxs7";//Enter your Auth token
char ssid[] = "hail hydra_2.4";//Enter your WIFI name
char pass[] = "pointbreak";//Enter your WIFI password
long distance, distanceRoof, distanceBase;

BlynkTimer  timer;
bool pinValue = 0;

//#define trigBase D3
//#define echoBase D4
#define buzzer D1
#define trig D7
#define echo D8
#define relay D5

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
//  pinMode(trigBase, OUTPUT);
//  pinMode(echoBase, INPUT);
  
  pinMode(relay, OUTPUT);
  
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  digitalWrite(relay, HIGH);
}

BLYNK_WRITE(V0) {
  pinValue = param.asInt();
}


void loop() {
  Blynk.run();
  if (pinValue == 1) {
    digitalWrite(relay, LOW);
    Serial.println("Motor is ON");
  } else if (pinValue == 0) {
    digitalWrite(relay, HIGH);
    Serial.println("Motor is OFF");
  }
  
  calculateDistance(trig, echo);
  distanceRoof = distance;

  if (distanceRoof <= 5){
    digitalWrite(buzzer, HIGH);
  }else{
    digitalWrite(buzzer, LOW;
  }

//  calculateDistance(trigBase, echoBase);
//  distanceBase = distance;

  Blynk.virtualWrite(V1, distanceRoof);
//  Blynk.virtualWrite(V2, distanceBase);
  
  Serial.print("Roof tank water level: ");
  Serial.println(distanceRoof);
//  Serial.print("Base tank water level: ");
//  Serial.println(distanceBase);
}

void calculateDistance(int trigPin, int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(4);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long t = pulseIn(echoPin, HIGH);
 
  distance = t / 29 / 2;
}
