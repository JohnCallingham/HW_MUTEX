# HW_MUTEX

This library has been designed to be part of the ESP32_2Servo_2Frog_2TOTI_WiFi program. It is part of a suite of libraries which can be used as part of an OpenLCB/LCC node.

This library has been developed using PlatformIO.

It implements a hardware mutex which a number of pins to be configured as outputs. Only one can be active at a time.

The output pins can be configured to be active high or active low.

When a pin is selected to be active, all pins are made inactive and the configurable delay is started. When the delay expires the selected pin is made active.
