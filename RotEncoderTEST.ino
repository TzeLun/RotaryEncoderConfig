/*****************************************************************************************/
/*** Author : Lok Tze Lun                                                              ***/
/*** Date : 1/9/2020 (Last Revised)                                                    ***/
/*** Title : Configuration of incremental rotary encoder for angular position tracking ***/
/*** Model : RE30E_500_213_1, two outputs                                              ***/
/*** NOTE : Code should be usable for other incremental rotary encoder                 ***/
/*****************************************************************************************/


/*** res is the resolution of the encoder with unit, this model is rated at 500 pulse/revolution  ***/
/*** one pulse == 0.72 deg, a period of one pulse will trigger 4 ISR in theory based on datasheet ***/
/*** Hence, this encoder has 0.18 degree per count. Change this value based on your model         ***/
#define res 0.18

/*** For Arduino UNO, must use pin 2 and 3 as they are interrupt pins      ***/
/*** Check the datasheet for other Arduino boards regarding interrupt pins ***/
/*** Otherwise, consider other options for defining interrupt pins         ***/
int outA = 2;
int outB = 3; 
int count = 0;

// Change the polarity of decrement and increment of count in the ISR to your preferred direction
// Note that the count polarity in the if-conditions for both ISR are opposite each other
// Additional conditions can be added to track if one revolution is completed - up to user

void setup() {
  Serial.begin(9600);
  pinMode(outA, INPUT);
  pinMode(outB, INPUT);
  attachInterrupt(digitalPinToInterrupt(outA), ISR_A, CHANGE);
  attachInterrupt(digitalPinToInterrupt(outB), ISR_B, CHANGE);
}

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
}

void loop() {
  Serial.print("encoder (deg) : ");
  Serial.println(count*res); //using defined macro -> res, output should be in degrees instead of counts
  delay(50);
}
