# What if we use a 74HC595 to handle the columns?

I/Os are limited on a poor ProMicro, let's try to use a Serial-in-Parallel-out shift register (onwards called SR) to circumvent that limitation.

## How does the `74HC595` work?
The `74HC595` is a *serial-in, parallel-out* shift register, meaning we feed a byte serially on one pin and get the 8 bits split on eight output pins when we trigger the latch.

Here are the essentials:
- `QA` ... `QG`: 8 output pins
- `QH'`: Overflow pin to daisy-chain SRs. Any extra bit beyond the first byte sent before latching will be sent out through this pin. By connecting it to the `SER` pin of another SR, we can effectively daisy-chain them.
- `GND`
- `VCC`
- `SER`: Data input, the byte is sent here.
- `!OE`: Output enable, active low. Connect to ground to have the output constantly available.
- `RCLK`: Shift register clock pin, one cycle every bit.
- `SRCLK`: Storage register clock pin, one cycle every byte.
- `!SRCLR`: Clear everything. Short to `VCC` if you don't want to use it.

## Pull-down resistors
We need those pull-down resistors to force the input pin to a logic low when no voltage is applied, as there is none inside the ATmega32U4 chip. But we can't simply short it to ground, otherwise it would never get to a logic-high voltage.

#### Now, how do we size the resistor?
We need a few pieces of information:

1. What is `VCC`? 
In our case, it would be **5V** (but might become 3.7V or lower in a later implementation using a battery).

2. What is considered a *logic-high voltage*?
According to [Microchip's documentation](http://ww1.microchip.com/downloads/en/devicedoc/atmel-7766-8-bit-avr-atmega16u4-32u4_datasheet.pdf), the DC characteristics (table 29-1 on section 29.2, page 383) it's at least `0.2VCC + 0.9V` (= **1.9V**) and at most `VCC + 0.5`.

3. Do we drop voltage on the way?
There is a `1N4148` after each switch, between the column and the row.
According to the [documentation](https://www.vishay.com/docs/81857/1n4148.pdf), the forward voltage is *at most* **1V**.

4. What is the maximum current the `74HC595` can provide?
According to [TI's documentation](https://www.ti.com/lit/ds/scls041i/scls041i.pdf), the maximum output current is **35mA**.

Summary: We'll get **4V** at the input and can source at most **35mA**, which means we need a resistor of at least 115 ohms.
However, if we have multiple rows active at the same time, the current sourced from the column at the SR will be split. In our case, we only have 3 rows. Assuming all three are perfectly identical, we would need at least 343 ohms resistors. So there is not much needed, I don't know from where mehmedbasic took his "at least 5k", but that's overkill.
Anyway, I had **47k** resistors lying around as well, so they'll do the trick.


## Updated schematic
Notice that the rows and columns have been swapped compared to the bare-pins 9-keys keyboard.
This is a consequence of the logic being pushed *from* the columns *to* the rows.

![schematic](figures/schematics.png)custom_matrix.md).
We are going for a full replacement.


## Firmware tree
It's a bit simpler than the first one:
```
.
├── 9keys.c
├── 9keys.h
├── config.h
├── keymaps
│   └── default
│       └── keymap.c
├── matrix.c
└── rules.mk
```
The new and most notable file being `matrix.c` that we'll be detailed below.

### `Config.h`
We have reversed the diode direction:
```
#define DIODE_DIRECTION COL2ROW
```
Not that I know if it changes anything.

### `rules.mk`
Notice these lines:
```
CUSTOM_MATRIX = yes
SRC += 9keys.c
SRC += matrix.c
```


## Custom Matrix
In order to implement it in QMK, we need to use a custom matrix implementation.
QMK offers [some documentation on the matter](https://github.com/qmk/qmk_firmware/blob/master/docs/).

First, initialize the matrix:
```C
setPinInput(D5); /* Arduino denomination */
setPinInput(D6);
setPinInput(D7);

setPinOutput(SHR_DATA);
setPinOutput(SHR_LATCH);
setPinOutput(SHR_CLOCK);
```

The matrix scanning works as follow:
```
For each column:
    Select the column
    Read the rows
    For each row in rows:
        Debounce
        Set the value in the matrix
```

Let's take a quick look at the rows reading:
```C
return (readPin(ROW_C) << 2)
     | (readPin(ROW_B) << 1)
     | (readPin(ROW_A) );
```
We simply concatenated the *n* bits from the *n* rows before reading them one by one in the innermost loop of `matrix_scan()`.

But it's in the column selection that the magic happens, since we connected the columns to the SR.
If we want to scan the first column, we send the value `0x01` (see `SHR_COLS` in `config.h`) to the shift register, setting the latch low right before and high right after.
To send the byte to the SR, we pulse the `RCLK` clock until our bit reaches the MSB, so 7 times in this instance, then set the `SER` pin high, low otherwise.

This is inherent to the way a SR works: if we want our LSB bit to be latched, we need to send it as late as possible. Each rising edge of `RCLK` will shift everything from `QA` towards `QH`.
This also means that if you want to daisy-chain SRs, the *furthest* byte needs to be sent first.





## So, what happens when I press a key?
The column connected to that key is periodically set to high, just to see if that signal gets across all the way to the row on the other side. Let's say you have your key pressed at that very moment: the code we just detailed above will catch that specific row being activated when that specific column was being activated as well. Based on the keymap, the firmware knows then which signal to send through the USB. Voila.

## Compilation and transfer
```
$ qmk compile -kb 9keysSR -km default
$ avrdude -F -V -c avr109 -p atmega32u4 -P /dev/ttyACM0 -b 115200 -U flash:w:/home/para/qmk_firmware/.build/9keysSR_default.hex
```



## Troubleshooting
- **You can't have hypens `-` in the dir name of the keyboard firmware.**
- In `keymap.c`, the `QMK_KEYBOARD_H` macro was not solved by the compiler, somehow ending up empty.
This was solved by hardcoding the location of the desired header: `"../../9keys.h"`


## References and resources
- [Great write-up from mehmedbasic](https://mehmedbasic.dk/post/74hc595-keyboard/)
Note that some of is schematics seem wrong. The `!SRCLR` (11) and `VCC` (16)  pins should be connected to 5V, and the `!OE` (13) pin to the ground.
- [The full keyboard firmware of mehmedbasic](https://github.com/ripdajacker/qmk_firmware/tree/yogaext/keyboards/ripdajacker/yogaext)
- [Basic usage from aduino.cc](https://www.arduino.cc/en/Tutorial/Foundations/ShiftOut)
- [74HC595 datasheet](https://www.ti.com/lit/ds/scls041i/scls041i.pdf?ts=1613947557756&ref_url=https%253A%252F%252Fwww.google.com%252F)