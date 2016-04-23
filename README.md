# MicroTimer
A partial QTimer replacement with potential sub microsecond accuracy. It lets you specify the interval as a `qreal` instead of an `int` and also lets you specify the frequency directly. See `microtimer.h` for more details.

# Usage
Use like you would a `QTimer`. Note that single shot timers and intervals of 0 are not supported. Only the properties are identical between `MicroTimer` and `QTimer`. Some other methods/signals/slots may be missing.
