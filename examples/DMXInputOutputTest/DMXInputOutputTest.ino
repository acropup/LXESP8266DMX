/**************************************************************************/
/*!
    @file     DMXInputOutputTest.ino
    @author   Shane Burgess
    @license  BSD (see LXESP8266DMX LICENSE)

    Example showing LXESP8266DMX receiving DMX data on one universe
	while transmitting DMX data on another universe.
	From receive to transmit, DMX channel 1's value is inverted,
	and DMX channels 2-4 are duplicated on channels 5-7.
	BUILTIN_LED blinks whenever a DMX data packet is received.
	
    @section  HISTORY
    v1.00 - First release
*/
/**************************************************************************/
#include <LXESP8266UARTDMX.h>

int got_dmx = 0;
boolean packet_received_toggle = HIGH;

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  ESP8266DMX.setDataReceivedCallback(&gotDMXCallback);
  delay(1000);        //avoid boot print??
  ESP8266DMX.startInputOutput();
}


// ***************** input callback function *************

void gotDMXCallback(int slots) {
  got_dmx = slots;
  packet_received_toggle = !packet_received_toggle;
}

void loop() {
  digitalWrite(BUILTIN_LED, packet_received_toggle);
  if ( got_dmx ) {
    // Output the inverse of what was received on channel 1
    ESP8266DMX.setSlot(1, 255 - ESP8266DMX.getSlot(1));
	// Passthrough channels 2-4
    ESP8266DMX.setSlot(2, ESP8266DMX.getSlot(2));
    ESP8266DMX.setSlot(3, ESP8266DMX.getSlot(3));
    ESP8266DMX.setSlot(4, ESP8266DMX.getSlot(4));
	// Copy channels 2-4 to 5-7
    ESP8266DMX.setSlot(5, ESP8266DMX.getSlot(2));
    ESP8266DMX.setSlot(6, ESP8266DMX.getSlot(3));
    ESP8266DMX.setSlot(7, ESP8266DMX.getSlot(4));
  }
}