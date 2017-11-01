#include <dht.h>
 

 
#define dht_apin A0 
#define led A1 
#define ldr A2
#define ledR A3
#define buzz A4
dht DHT;
float ldrVal;

void setup(){
 
  Serial.begin(9600);
 //pinMode(LED_BUILTIN, OUTPUT);
 pinMode(led, OUTPUT);
 pinMode(ledR, OUTPUT);
 pinMode(buzz, OUTPUT);
  delay(500);
 
  //Serial.println("DHT11 Humidity & temperature Sensor\n\n");
 
  delay(1000);
 
}
void loop(){
 
  //Start of Program 
 
  DHT.read11(dht_apin);
 
      ldrVal = analogRead(ldr);
      Serial.print("Light = ");
      Serial.print(ldrVal);
      if(ldrVal>800)
      {
        digitalWrite(ledR, HIGH);
        digitalWrite(buzz, HIGH);
       }
       else {digitalWrite(buzz, LOW); digitalWrite(ledR, LOW);}
    Serial.print(",");
    Serial.print("Humidity = ");
    //Serial.print(",");
    Serial.print(DHT.humidity);
    Serial.print(",");
 
    Serial.print("Temperature = ");
 
    Serial.println(DHT.temperature); 
    //Serial.write(DHT.temperature);
 
    //Serial.println("C  ");

  if(DHT.temperature > 22)
  {
    digitalWrite(led, HIGH);
  }
  else if(DHT.temperature < 20)
  {
    digitalWrite(led, LOW);
    }
  /*digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW); */
  
  delay(1000);
 
 
}

