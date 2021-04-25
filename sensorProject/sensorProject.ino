#include <FirebaseArduino.h>
#include  <ESP8266WiFi.h>
#define FIREBASE_HOST "xxxxxx"//host name of firebase
#define FIREBASE_AUTH "xxxxx" //authentication key
#define WIFI_SSID "xxxx" //wifi ssid
#define WIFI_PASSWORD "xxxx" //wifi password

float v02=0.0,f=3000.0,v1=5.0;
float r1=1000.0,r2=180000.0,r3=1000.0;
float epsilon0=8.85e-12,epsilonr=2.2,c=0.0,x=0.0,b=0.06,d=0.005,h=0.25,avg=0.0,m=0.0;
int v0=0;
//variable initialization

void setup() {

   Serial.begin(9600);
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print(".");
  }
   
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);//connecting to firebase
  }

void loop() {
  
 for(int i=1;i<=100;i++)//loop for calculating average of 10 successive voltage values 
 {
  v0=analogRead(A0);
  v02=v0*(3.3/1024.0);
  m=m+v02;
  delay(200);
 }
  avg=m/100;
  m=0.0;
  v02=avg;
  
  c=(v02*r3)/(2*(22.0/7.0)*f*r1*r2*v1);//calculating capacitance
  x=((((c*d)/(epsilon0*b))-h)/(epsilonr-1))*100.0;//calculating displacement
  
  Serial.print("Output voltyage v02=");
  Serial.print(v02);
  Serial.print("   ");
  Serial.print("Liquid level=");
  Serial.print(x);
  Serial.println();
  
  Firebase.setFloat ("LiquidLevel",x);
  Firebase.setFloat ("OutputVoltage",v02);
  //sending data to google firebase
  
  delay(1000);
}
