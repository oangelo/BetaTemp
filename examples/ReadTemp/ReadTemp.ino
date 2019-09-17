#include <BetaTemp.h>

BetaTemp T1(A0, 10000);

void setup() 
{
   Serial.begin(9600);
}

void loop() 
{
  Serial.println(T1.get_temp());
  delay(1000);
}
