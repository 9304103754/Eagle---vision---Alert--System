#include <SoftwareSerial.h>

SoftwareSerial GSM(10, 11); // RX, TX pins connected to GSM module

void setup() 
{
  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);
  GSM.begin(9600); // Set GSM baud rate
  Serial.begin(9600); // For debugging
  delay(1000);
  Serial.println("Initializing GSM module...");
  GSM.println("AT");
  delay(1000);
  GSM.println("AT+CMGF=1"); // Set SMS text mode
  delay(1000);
  GSM.println("AT+CNMI=2,2,0,0,0"); // Enable message notifications
  delay(1000);
}

void loop() {
  if (Serial.available()) 
  {
    char command = Serial.read();
    Serial.println('COmand received', command);
    if (command == 'S') 
    { // Send SMS on receiving 'S'
        digitalWrite(2,LOW);
        delay(1000);
        digitalWrite(2,HIGH);
        delay(1000);
        digitalWrite(2,LOW);
        delay(1000);
        digitalWrite(2,HIGH);
        sendSMS();
    }
  }
}

// void sendSMS() 
// {
//   GSM.println("AT+CMGS=\"+919876543210\""); // Replace with recipient's number
//   delay(1000);
//   GSM.print("Weapon detected! Immediate action required.");
//   delay(1000);
//   GSM.write(26); // Send Ctrl+Z to send the message
//   delay(1000);
//   Serial.println("SMS sent.");
// }

void sendSMS() 
{
  Serial.println("Sending SMS...");

  GSM.println("AT+CMGF=1"); // Set GSM module to SMS mode
  Serial.println("Command: AT+CMGF=1");
  delay(1000);

  GSM.println("AT+CMGS=\"+919304103754\""); // Replace with recipient's number
  Serial.println("Command: AT+CMGS=\"+919304103754\"");
  delay(1000);

  GSM.print("Voilence detected! Immediate action required."); // SMS body
  Serial.println("Message: Voilence detected! Immediate action required.");
  delay(1000);

  Serial.write(0x1A); // Send Ctrl+Z to send the message
  Serial.println("Command: Ctrl+Z (26)");
  delay(1000);

  Serial.println("SMS sent.");
}
