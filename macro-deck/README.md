# 4-by-5 macro pad

## The way the logic works
Current is sourced from the 74HC959 and sinked at the ProMicro pin.
If we have 5 rows and 4 columns of keys, the rows should be connected to the ProMicro i/o and the columns to the shift register.
We thus end up with current flowing from columns to rows, pay attention to the direction of the diodes.