# HW_MUTEX

This software component is part of a suite of components which can be used to build an OpenLCB/LCC node.

It implements a hardware mutex which a number of pins to be configured as outputs. Only one can be active at a time.

The output pins can be configured to be active high or active low.

When a pin is selected to be active, all pins are made inactive and the configurable delay is started. When the delay expires the selected pin is made active.
