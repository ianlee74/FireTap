#include <SPI.h>

#include "Mirf.h"
#include "MirfHardwareSpiDriver.h"
#include "MirfSpiDriver.h"
#include "nRF24L01.h"

void setup(){
  digitalWrite(6, 1);
  pinMode(6, OUTPUT);

  Serial.begin(9600);
  /*
   * Set the SPI Driver.
   */
  Mirf.spi = &MirfHardwareSpi;
  
  /*
   * Setup pins / SPI.
   */
  //Mirf.csnPin = 8;
  //Mirf.cePin = 7;
  Mirf.init();
  
  /*
   * Configure reciving address.
   */
  Mirf.setRADDR((byte *)"serv1");
  
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
  Mirf.config();

  Serial.println("Listening..."); 
}

void loop(){
  Serial.println("At top of server loop.");
  /*
   * A buffer to store the data.
   */
  byte data[Mirf.payload];
  
  /*
   * If a packet has been received.
   *
   * isSending also restores listening mode when it 
   * transitions from true to false.
   */
  if(!Mirf.isSending() && Mirf.dataReady()){
    Serial.println("Got packet");
    digitalWrite(6, 0);
    delay(3000);
    digitalWrite(6, 1);
    /*
     * Get load the packet into the buffer.
     */
    Mirf.getData(data);
    Serial.println(data[0]);
    /*
     * Set the send address.
     */
    Mirf.setTADDR((byte *)"clie1");
    
    /*
     * Send the data back to the client.
     */
    Mirf.send(data);
    
    /*
     * Wait untill sending has finished
     *
     * NB: isSending returns the chip to receving after returning true.
     */
      
    Serial.println("Reply sent.");
  }
  delay(500);
}


