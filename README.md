# HW_MUTEX

The file hw_mutex.h contains a single class HwMutex. This class accepts a number of GPIO output pins and ensures that only one of them can be active at a time.

The GPIO outputs can be configured to all be active high or all be active low.

When one of the output pins is set to be active all of the output pins are set to be inactive and a timer is started. When the timer expires the selectted output is made active.

This library is used when switching frogs to ensure that the frog can never be connected to both supply rails at the same time.

This library has been developed using PlatformIO.
