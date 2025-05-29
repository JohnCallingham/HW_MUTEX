#include <Arduino.h>
#include "hw_mutex.h"

HW_MUTEX myMutex;

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  delay(5000);

  Serial.println("\n started");

  myMutex.setOutputsActiveHigh();
  myMutex.setDelaymS(5000);

  /**
   * If it is required to override the default active low setting then
   * setOutputsActiveHigh() must be called before setOutputPins() as
   * setOutputPins() will set all pins to inactive.
   */
  myMutex.setOutputPins ( { 1, 2 } );
  
  uint8_t activePin = 1;
  bool error = !myMutex.setPinActive(activePin);
  if (error) {
    Serial.printf("\ninvalid pin %d", activePin);
  }
}

void loop() {

  myMutex.process();

}
