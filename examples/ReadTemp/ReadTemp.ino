#include <BetaTemp.h>

BetaTemp temp1(A0, 10000);

void setup() 
{
   Serial.begin(9600);
}

void loop() 
{
  Serial.println(temp1.get_temp());
  delay(1000);
}
