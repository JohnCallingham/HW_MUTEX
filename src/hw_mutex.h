#ifndef HW_MUTEX_H
#define HW_MUTEX_H

/**
 * Provides the following functionality;-
 * 1. Allows a number of pins to be configured as outputs.
 * 2. All outputs are reset to inactive initially.
 * 3. Allows the pins to be configured as active high or active low.
 * 4. Allows a pin to be set as active. Raise an error if the pin set to be active is not in the list.
 * 5. Ensures that only one output is active at any time.
 * 6. Makes all outputs inactive before setting one active.
 * 7. A configurable delay between all outputs going inactive and one going active.
 * 8. Allows a pin to be made inactive.
 */

 /**
  * TO DO: allow a default delay and allow the user to override this from the frog object.
  */

#include <Arduino.h>
#include <vector>

class HwMutex {
  public:
    HwMutex();

    /**
     * Stores outputPins, sets all pins to outputs and resets all pins to the inactive state.
     */
    void setOutputPins(std::vector<uint8_t> outputPins);

    void setOutputsActiveHigh() {this->activeSetting = Active::activeHigh;}
    void setOutputsActiveLow() {this->activeSetting = Active::activeLow;}
    void setDelaymS(unsigned long delaymS) {this->delaymS = delaymS;}

    /**
     * Defines which pin is to be active.
     * Makes all pins inactive, waits for a specified delay, then sets the specified pin active.
     * Returns false if the specified pin is not in the list, else true.
     */
    bool setPinActive(uint8_t pin); // error is raised if pin is not in the vector.

    /**
     * Sets pin inactive.
     * Returns false if pin is not in the list, else true.
     */
    bool setPinInActive(uint8_t pin); // error is raised if pin is not in the vector.

    /**
     * Sets all pins to the inactive state.
     */
    void setAllPinsInActive();

    /**
     * Called from loop().
     * Checks if the timeout has expired and, if so, set the active pin to the active state.
     */
    void process();

private:
  std::vector<uint8_t> outputPins;
  uint8_t currentActivePin = 0; // assumes that there is no pin 0 !!
  enum Active { activeHigh, activeLow };
  Active activeSetting; // Determines whether the outputs are active high or active low.
  unsigned long delaymS; // The delay from all pins going inactive to the one pin going active.
  unsigned long delayExpiryTime; // The millis() value when the timeout has expired. 
  bool delayRunning; // True when the timeout is running, else false.

  /**
   * Returns true if pin is one of outputPins, else false.
   */
  bool _isPinValid(uint8_t pin);

  /**
   * Set pin to be HIGH or LOW depending on activeSetting.
   */
  void _setPinActive(uint8_t pin);

  /**
   * Set pin to be LOW or HIGH depending on activeSetting.
   */
  void _setPinInActive(uint8_t pin);

  void _setPinHigh(uint8_t pin);
  void _setPinLow(uint8_t pin);

};
 
#endif
