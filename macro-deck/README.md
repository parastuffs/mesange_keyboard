# 4-by-5 macro pad

## The way the logic works
Current is sourced from the 74HC959 and sinked at the ProMicro pin.
If we have 5 rows and 4 columns of keys, the rows should be connected to the ProMicro i/o and the columns to the shift register.
We thus end up with current flowing from columns to rows, pay attention to the direction of the diodes.

74HC595 -> Column -> diode -> switch -> row -> ProMicro

## Keys spacing on PCB
The standard measurement unit for a key is `1u`, which is `0.75"`, or `19.05mm`.
The center-to-center distance is supposed to be 1u as well and the edge-to-edge distance is 1/4", i.e. 6.35mm.

![spacing](figures/pcb-spacing.png)

The footprints from the `Button_Switch_Keyboard` library have a handy white outline on the `Dwgs.User` layer that delimits the keycap area.

## Build firmware
The firmware should be placed in qmk's home folder, such as `/home/para/qmk_firmware/keyboards`.

```
qmk compile -kb macrodeck -km default
avrdude -F -V -c avr109 -p atmega32u4 -P /dev/ttyACM0 -b 115200 -U flash:w:/home/para/qmk_firmware/.build/macrodeck_default.hex
```

Don't forget to short the `reset` pin to ground to enable "flashable" mode on the board (bottom two LEDs in red).

## References

[QMK documentation about layers](https://beta.docs.qmk.fm/using-qmk/software-features/feature_layers)