#include "hw_mutex.h"

HwMutex::HwMutex() {
  // Set the default active setting.
  activeSetting = Active::activeLow;

  // Set the default delay to 100mS.
  delaymS = 100;
}

void HwMutex::setOutputPins(std::vector<uint8_t> outputPins) {
  // Store the output pins.
  this->outputPins = outputPins;

  // Set all pins as outputs and inactive.
  for (auto i: this->outputPins) {
    pinMode(i, OUTPUT);
    _setPinInActive(i);
  }
}

bool HwMutex::setPinActive(uint8_t pin) {
  // Check that activePin is in the list of pins.
  if (!_isPinValid(pin)) return false;

  // // If this pin is already the active pin, then take no further action.
  // if (pin == currentActivePin) return true;

  // Reset all pins to inactive.
  for (auto i: outputPins) {
    _setPinInActive(i);
  }

  // Set this pin to be the current active pin.
  currentActivePin = pin;

  // Start the timer for delaymS.
  delayExpiryTime = millis() + delaymS;
  delayRunning = true;

  return true;
}

bool HwMutex::setPinInActive(uint8_t pin) {
  // Check that activePin is in the list of pins.
  if (!_isPinValid(pin)) return false;

  _setPinInActive(pin);

  return true;
}

void HwMutex::setAllPinsInActive() {
  for (auto i: outputPins) {
    _setPinInActive(i);
  }
}

bool HwMutex::_isPinValid(uint8_t pin) {
  //Serial.printf("\nin isPinValid() for %d", pin);
  for (auto i: outputPins) {
    //Serial.printf("\nchecking pin %d", i);
    if (i == pin) return true;
  }

  return false;
}

void HwMutex::process() {
  // Check for the timeout expiring.
  if ((delayRunning) && (millis() >= delayExpiryTime)) {
    // The timeout has expired.
    delayRunning = false;

    // Make the currentActivePin active.
    _setPinActive(currentActivePin);
  }
}

void HwMutex::_setPinActive(uint8_t pin) {
  if (activeSetting == Active::activeHigh) {
    _setPinHigh(pin);
  } else {
    _setPinLow(pin);
  }
}

void HwMutex::_setPinInActive(uint8_t pin) {
  if (activeSetting == Active::activeHigh) {
    _setPinLow(pin);
  } else {
    _setPinHigh(pin);
  }
}

void HwMutex::_setPinHigh(uint8_t pin) {
  Serial.printf("\n%d setting pin %d HIGH", millis(), pin);
  digitalWrite(pin, HIGH);
}

void HwMutex::_setPinLow(uint8_t pin) {
  Serial.printf("\n%d setting pin %d LOW", millis(), pin);
  digitalWrite(pin, LOW);
}
