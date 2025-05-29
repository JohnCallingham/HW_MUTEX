#include "hw_mutex.h"

HW_MUTEX::HW_MUTEX() {
  // Set the default active setting.
  activeSetting = Active::activeLow;
}

void HW_MUTEX::setOutputPins(std::vector<uint8_t> outputPins) {
  // Store the output pins.
  this->outputPins = outputPins;

  // Set all pins as outputs and inactive.
  for (auto i: this->outputPins) {
    pinMode(i, OUTPUT);
    _setPinInActive(i);
  }
}

bool HW_MUTEX::setPinActive(uint8_t pin) {
  // Check that activePin is in the list of pins.
  if (!_isPinValid(pin)) return false;

  // If this pin is already the active pin, then take no further action.
  if (pin == currentActivePin) return true;

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

bool HW_MUTEX::setPinInActive(uint8_t pin) {
  // Check that activePin is in the list of pins.
  if (!_isPinValid(pin)) return false;

  _setPinInActive(pin);

  return true;
}

bool HW_MUTEX::_isPinValid(uint8_t pin) {
  //Serial.printf("\nin isPinValid() for %d", pin);
  for (auto i: outputPins) {
    //Serial.printf("\nchecking pin %d", i);
    if (i == pin) return true;
  }

  return false;
}

void HW_MUTEX::process() {
  // Check for the timeout expiring.
  if ((delayRunning) && (millis() >= delayExpiryTime)) {
    // The timeout has expired.
    delayRunning = false;

    // Make the currentActivePin active.
    _setPinActive(currentActivePin);
  }
}

void HW_MUTEX::_setPinActive(uint8_t pin) {
  if (activeSetting == Active::activeHigh) {
    _setPinHigh(pin);
  } else {
    _setPinLow(pin);
  }
}

void HW_MUTEX::_setPinInActive(uint8_t pin) {
  if (activeSetting == Active::activeHigh) {
    _setPinLow(pin);
  } else {
    _setPinHigh(pin);
  }
}

void HW_MUTEX::_setPinHigh(uint8_t pin) {
  Serial.printf("\n%d setting pin %d HIGH", millis(), pin);
  digitalWrite(pin, HIGH);
}

void HW_MUTEX::_setPinLow(uint8_t pin) {
  Serial.printf("\n%d setting pin %d LOW", millis(), pin);
  digitalWrite(pin, LOW);
}
