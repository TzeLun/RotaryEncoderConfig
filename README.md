# RotaryEncoderConfig
Simple Arduino code to configure an incremental rotary encoder for angular position measurement

Hi all, I created this repository with two intentions:
1. To store my past work
2. To provide a comprehensive guide on how to configure and use incremental rotary encoders for engineering students.

The rotary encoder model used for my past project was the RE30E-500-213-1, you may find the datasheet attached below.

For simple encoders, aside from power rating, there are other properties you should be aware of:
1. Resolution (pulse/revolution, P/R)
2. Phase difference between the encoder outputs (The two main output wire, in my case, OutA and OutB)
3. How many changes in both encoder outputs is equivalent to a period of pulse

Usually the pulse is depicted as a square/rectangular pulse in the datasheet and one pulse period includes the pulse and the duration before the start of next pulse. Based on the given datasheet, there are a total of 4 changes in encoder output (2 for Output A and 2 for Output B) to make up one pulse period. The diagram is given below for easy reference:

![Encoder Output](https://github.com/TzeLun/RotaryEncoderConfig/blob/master/Encoder%20Output.PNG)

This encoder model is rated at 500 P/R and phase difference of 90 deg. That means 1 pulse is equivalent to 0.72 deg.

Interrupt service routine (ISR) can be used to track any changes to each encoder output as its faster and more accurate than looping if statements. Each change can be recorded with a "count" variable. To establish a clockwise/counter-clockwise rotation, apply a decrement or increment on the count value. Using the diagram of output pulseform in the given datasheet or that above, by shifting your position along the pulse by a quarter of a period in any lateral direction, you will notice both outputs change state alternatively (one changes while the other stays). After the shift, the current states of both outputs are either equal or opposite. Depending on the position shift you take, comparison of both output states is used to describe the direction of rotation. 

With that, whenever ISR is triggered, use a simple condition to check if both output states are similar or not then increase or decrease the count based on your own conventions. This is done via the code below:

```C++
void ISR_A()
{
  if (digitalRead(outA) != digitalRead(outB))
  {
    count--;
  }
  else
  {
    count++;
  }
}

void ISR_B()
{
  if (digitalRead(outB) != digitalRead(outA))
  {
    count++;
  }
  else
  {
    count--;
  }
 ```

Lastly, since there sould be 4 ISR triggers for 1 pulse, the resolution here is 0.18 degree per count. Your angular position measured by the encoder is just the product of count and resolution (unit in degrees).

There are definitely many posts or codes out there regarding this topic, but to whoever reading this I hope this gives you a rigid understanding on getting started with your incremental rotary encoders.

[RE30E-500-213-1 Datasheet](https://www.digchip.com/datasheets/parts/datasheet/4413/RE30E-500-213-1-pdf.php)
