#include "conf.c"
#include "sleep.h"

// #define DEBUG

#define ENABLE_RADIO PORTD.2 = 1;
#define DESABLE_RADIO PORTD.2 = 1;
#define ENABLE_CHARGING DDRC = 0x0E;PORTC.1 = 1;
#define DESABLE_CHARGING DDRC = 0x0C;PORTC.1 = 0;
#define DISCHARGE DDRC = 0x0E;delay_ms(10);DDRC = 0x0C;

#ifdef DEBUG
void send(int data)
{
   putchar(data >> 8);
   putchar(data & 0xFF);
   delay_ms(500);
}
#endif

void discharge(int current){
   int t = 19-(current-10)/55;
   DDRC = 0x0E;
   while(--t>0) delay_ms(1);
   DDRC = 0x0C;
}

void main(void)
{
   int temp = 0;
   init();

   temp = read_adc(0);   
   
   #ifdef DEBUG
   send(temp);
   #endif

   discharge(temp); // use current charge for calc discharge impulse

   if (temp < 5){
      ENABLE_CHARGING
      ENABLE_RADIO

      temp = ds18b20_temperature(0) * 10;
      putchar(0x88);
      putchar(temp >> 8);
      putchar(temp & 0xFF);
      
      delay_ms(500);
      DESABLE_RADIO
      DESABLE_CHARGING
   }

   sleep_enable();
   #asm("wdr")
   powerdown();
}
