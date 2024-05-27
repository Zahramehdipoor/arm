#include "lpc17xx_gpio.h"

const uint8_t segmentTable[]={0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

//const uint8_t segmentTable1[]={0x6F,0x7F,0x07,0x7D,0x6D,0x66,0x4F,0x5B,0x06}; R

void Delay()
{
   for(uint16_t count=0;count<UINT16_MAX;count++)
      for(uint8_t count2=0;count2<150;count2++)
       {
         
       }
}

int main()
{  
  FIO_ByteSetDir(0,2,0xFF,1);
  
while(1)
{  
  for(uint8_t count=0;count<10;count++)
  {
    FIO_ByteSetValue(0,2,segmentTable[count]);
    FIO_ByteClearValue(0,2,~segmentTable[count]);
  //  FIO_ByteSetValue(0,2,segmentTable1[count]); //R
  //  FIO_ByteClearValue(0,2,~segmentTable1[count]); //R
    Delay();
  }
}
  
}