# Terrashroom Chamber Pinout (draft)

Source of truth for the legacy firmware is `chamber/src/Habitat.h`.
We will keep this document updated as ESPHome components are wired in.

| Function | Legacy GPIO | Notes |
|----------|-------------|-------|
| Fan 1 (exhaust) | 32 | PWM capable |
| Fan 2 (intake) | 33 | PWM capable |
| Blower         | 25 | PWM capable |
| Atomizer       | 13 | MOSFET drive |
| Heater         | 12 | uses high-power MOSFET |
| UV LED         | 18 | digital output |
| Water low sense | 23 | input_pullup/pulldown TBD |
| Water read enable | 15 | enables sensor power |
| ESP32-CAM enable | 26 | toggles camera power |
| Serial2 TX/RX   | 17/16 (default) | connection to camera module |

Additional pins (buttons, LEDs, sensors) will be copied over exactly when their ESPHome components are implemented.
