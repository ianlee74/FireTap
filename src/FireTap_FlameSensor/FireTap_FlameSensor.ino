#include <SPI.h>

#include <printf.h>

#include <Mirf.h>
#include <MirfHardwareSpiDriver.h>
#include <MirfSpiDriver.h>
#include <nRF24L01.h>

int fireThreshold = 50;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  /*
   * Setup pins / SPI.
  */
   
  /* To change CE / CSN Pins:
   * 
   * Mirf.csnPin = 9;
   * Mirf.cePin = 7;
   */
  /*
  //Mirf.cePin = 7;
  //Mirf.csnPin = 8;
  */
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  
  /*
   * Configure receiving address.
   */
   
  Mirf.setRADDR((byte *)"clie1");
  
  /*
   * Set the payload length to sizeof(unsigned long) the
   * return type of millis().
   *
   * NB: payload on client and server must be the same.
   */
   
  Mirf.payload = sizeof(unsigned long);
  
  /*
   * Write channel and payload config then power up reciver.
   */
   
  /*
   * To change channel:
   * 
   * Mirf.channel = 10;
   *
   * NB: Make sure channel is legal in your area.
   */
  Mirf.config();
  Serial.println("Beginning ... "); 
}

// the loop routine runs over and over again forever:
void loop() {

  Serial.println("At top of loop.");
  unsigned long fireSensorBits = 0;
  if (digitalRead(2) == 0)
  {
    Serial.println("Pin 2 is 0");
    fireSensorBits += 1;
  }
  if (digitalRead(3) == 0)
  {
    Serial.println("Pin 3 is 0");
    fireSensorBits += 2;
  }
  if (digitalRead(4) == 0)
  {
    Serial.println("Pin 4 is 0");
    fireSensorBits += 4;
  }
  // read the input on analog pin 0:
  //int sensorValue = analogRead(A0);
  //if (sensorValue < 500)
  if (fireSensorBits > 0)
  {
    Serial.println("I'm on fire!!!!");
    SendAlarm(fireSensorBits);
  }      
  delay(1000);
}

void SendAlarm(unsigned long fireSensorBits)
{
  unsigned long time = millis();

  Mirf.setTADDR((byte *)"serv1");
  Mirf.send((byte *)&fireSensorBits);

  Serial.print("Ready to send ");
  Serial.println(fireSensorBits);
 
  while(Mirf.isSending()){
  }

  Serial.println("Finished sending");
  delay(10);
  while(!Mirf.dataReady()){
    //Serial.println("Waiting");
    if ( ( millis() - time ) > 1000 ) {
      Serial.println("Timeout on response from server!");
      return;
    }
  }

  Mirf.getData((byte *) &time);

  Serial.print("Ping: ");
  Serial.println((millis() - time));
}
