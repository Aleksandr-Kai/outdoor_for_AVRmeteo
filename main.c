#include "conf.c"
#include "sleep.h"

void main(void)
{
   int temp = 0;
   init();

   sleep_enable();

   while (1){
      temp = ds18b20_temperature(0)*10;
      PORTA.7 = 1;
      delay_ms(10);
      putchar(0x88);
      putchar(temp >> 8);
      putchar(temp & 0xFF);
      delay_ms(10);
      PORTA.7 = 0;
      #asm("wdr")
      powerdown();
   }
}
