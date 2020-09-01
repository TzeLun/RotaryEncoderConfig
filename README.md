# RotaryEncoderConfig
Simple Arduino code to configure an incremental rotary encoder for angular position measurement

Hi all, I created this repository with two intentions, to store my past work and to provide a comprehensive guide on how to configure and use incremental rotary encoders for engineering students.

The rotary encoder model used for my past project was the RE30E-500-213-1, you may find the datasheet attached below.

For simple encoders, aside from power rating, there are properties you should be aware of:
1. Resolution (pulse/revolution, P/R)
2. Phase difference between the encoder outputs (The two main output wire, in my case, OutA and OutB)
3. How many changes in both encoder outputs is equivalent to a period of pulse

Usually the pulse is depicted as a square/rectangular pulse in the datasheet and one pulse period includes the pulse and the duration before the start of another pulse. Based on the datasheet, there are 4 changes in encoder output (sum of both outputs) which make up one pulse period.





RE30E-500-213-1 Datasheet:
https://www.digchip.com/datasheets/parts/datasheet/4413/RE30E-500-213-1-pdf.php
