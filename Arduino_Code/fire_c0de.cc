#include <SoftwareSerial.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
SoftwareSerial mySerial(9, 10);

int sensor=A1;
float temp_read,Temp_alert_val,Temp_shut_val;
int sms_count=0,Fire_Set;


void setup()
{
  pinMode(sensor,INPUT);
  mySerial.begin(9600);   
  Serial.begin(9600);    
  lcd.begin(16,2);  
  delay(500);
}

void loop()
{
CheckFire();
CheckShutDown();
}

void CheckFire()
{
lcd.setCursor(0,0);
lcd.print("Fire Scan - ON");
Temp_alert_val=CheckTemp();
if(Temp_alert_val>45)
{
 SetAlert(); // Function to send SMS Alerts
}
}

float CheckTemp()
{
temp_read=analogRead(sensor); // reads the sensor output (Vout of LM35)
temp_read=temp_read*5;    // converts the sensor reading to temperature
temp_read=temp_read/10;  // adds the decimal point
return temp_read; // returns temperature value in degree celsius
}

void SetAlert()
{
while(sms_count<3) //Number of SMS Alerts to be sent
{  
SendTextMessage(); // Function to send AT Commands to GSM module
}
Fire_Set=1; 
lcd.setCursor(0,1);
lcd.print("Fire Alert! SMS Sent!");
}

void CheckShutDown()
{
if(Fire_Set==1)
{

Temp_shut_val=CheckTemp();
if(Temp_shut_val<28)
{
lcd.setCursor(0,1);
lcd.print("Fire Shut! SAFE NOW");
sms_count=0;
Fire_Set=0;
}}}

void SendTextMessage()
{
  mySerial.println("AT+CMGF=1");    //To send SMS in Text Mode
  delay(2000);
  mySerial.println("AT+CMGS=\"+919544xxxxxx\"\r"); // change to the phone number you using 
  delay(2000);
  mySerial.println("Fire in NEW ROOM!");//the content of the message
  delay(200);
  mySerial.println((char)26);//the stopping character
  delay(5000);
   mySerial.println("AT+CMGS=\"+919847xxxxxx\"\r"); // change to the phone number you using 
  delay(2000);
  mySerial.println("Fire in NEW ROOM!");//the content of the message
  delay(200);
  mySerial.println((char)26);//the message stopping character
  delay(5000);
  sms_count++;
}
