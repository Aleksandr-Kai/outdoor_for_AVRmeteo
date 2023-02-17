#include "conf.c"
#include "sleep.h"

#define DEBUG

#define ENABLE_RADIO PORTD.2 = 1;
#define DESABLE_RADIO PORTD.2 = 0;
#define ENABLE_CHARGING DDRC = 0x0E;PORTC.1 = 1;
#define DESABLE_CHARGING DDRC = 0x0C;PORTC.1 = 0;
#define DISCHARGE DDRC = 0x0E;delay_ms(5);DDRC = 0x0C;

void main(void)
{
   int temp = 0;
   init();

   DISCHARGE

   temp = read_adc(0);   
   
   #ifdef DEBUG
   putchar(temp >> 8);
   putchar(temp & 0xFF);
   delay_ms(10);
   #endif

   if (temp < 10){
      ENABLE_CHARGING
      ENABLE_RADIO
      temp = ds18b20_temperature(0) * 10;

      putchar(0x88);
      putchar(temp >> 8);
      putchar(temp & 0xFF);
      
      delay_ms(20);
      DESABLE_RADIO
      DESABLE_CHARGING
   }

   sleep_enable();
   #asm("wdr")
   powerdown();
}
