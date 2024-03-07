// https://www.instructables.com/Arduino-Tinfoil-Piano/
// Based on the Capacitive Sensing
#include <CapacitiveSensor.h>

const int r_led = 8;
const int g_led = 9;
const int b_led = 10;
const int rw_led = A3;
const int gw_led = A2;
const int bw_led = A1;

CapacitiveSensor   cs_2_3 = CapacitiveSensor(2,3);        
CapacitiveSensor   cs_2_4 = CapacitiveSensor(2,4);         
CapacitiveSensor   cs_2_5 = CapacitiveSensor(2,5);     
CapacitiveSensor   cs_2_6 = CapacitiveSensor(2,6);       
CapacitiveSensor   cs_2_7 = CapacitiveSensor(2,7);

int treshold = 4000;

bool rFlag = false;
bool gFlag = false;
bool bFlag = false;

int rVal = 0;
int gVal = 0;
int bVal = 0;
int sVal = 0;

void setup()                    
{
  cs_2_6.set_CS_AutocaL_Millis(0xFFFFFFFF);
  pinMode(r_led, OUTPUT);
  pinMode(g_led, OUTPUT);
  pinMode(b_led, OUTPUT);
  pinMode(rw_led, OUTPUT);
  pinMode(gw_led, OUTPUT);
  pinMode(bw_led, OUTPUT);
  Serial.begin(9600);
}

void loop()                    
{
  long rSensor = cs_2_3.capacitiveSensor(30);
  long gSensor = cs_2_4.capacitiveSensor(30);
  long bSensor = cs_2_5.capacitiveSensor(30);
  long wSensor = cs_2_6.capacitiveSensor(30);
  long sSensor = cs_2_7.capacitiveSensor(30); 

  Serial.print("rSensor "); 
  Serial.println(rSensor);          
  Serial.print("gSensor "); 
  Serial.println(gSensor);   
  Serial.print("bSensor "); 
  Serial.println(bSensor);   
  Serial.print("wSensor "); 
  Serial.println(wSensor);    
  Serial.print("sSensor: ");
  Serial.println(sSensor);   

  Serial.println(sVal);
  Serial.println(255 * (sVal - 10000) / (40000 - 10000));  

  sVal = 255.0 * (sSensor - 10000.0) / (40000.0 - 10000.0);

  if (sVal < 0) {
    sVal = 0;
  }
  else if (sVal > 255) {
    sVal = 255;
  }    

  sVal = 255 - sVal;

  if (rSensor > treshold || rFlag == true) {
    digitalWrite(r_led, HIGH);
    analogWrite(rw_led, sVal);
    rFlag = true;
  }
  else{
    digitalWrite(r_led,LOW);
    rFlag = false;
  }

  if (gSensor > treshold || gFlag == 1) {
    digitalWrite(g_led, HIGH);
    analogWrite(gw_led, sVal);
    gFlag = true;
  }
  else {
    digitalWrite(g_led,LOW);
    gFlag = false;
  }

  if (bSensor > treshold || bFlag == 1) {
    digitalWrite(b_led, HIGH);
    analogWrite(bw_led, sVal);
    bFlag = true;
  }
  else {
    digitalWrite(b_led,LOW);  
    bFlag = false;
  }   

  if (wSensor > treshold) {
    if (wSensor < 15000) {
      analogWrite(rw_led,0);
      analogWrite(gw_led,0);
      analogWrite(bw_led,0);
    }
    digitalWrite(r_led,LOW);
    digitalWrite(g_led,LOW);
    digitalWrite(b_led,LOW);
    rFlag = false;
    gFlag = false;
    bFlag = false;
  }

  delay(500);
}
