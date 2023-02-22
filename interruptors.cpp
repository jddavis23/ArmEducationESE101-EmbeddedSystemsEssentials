#include "mbed.h"

#define ADULT p5
#define CHILD p6
#define FIRE p7


#define c1 p8
#define c2 p9
#define c3 p10
#define c4 p11
#define c5 p12
#define c6 p13
#define c7 p14
#define c8 p15
#define lm p16
#define b1 p17
#define b2 p18
#define b3 p19
#define CLOCK p20


//Define outputs
// DigitalOut l1(c1);
// DigitalOut l2(c2);
// DigitalOut l3(c3);
// DigitalOut l4(c4);
// DigitalOut l5(c5);
// DigitalOut l6(c6);
// DigitalOut l7(c7);
// DigitalOut l8(c8);
DigitalOut limit(lm);
DigitalOut bb1(b1);
DigitalOut bb2(b2);
DigitalOut bb3(b3);
DigitalOut clk(CLOCK);
BusOut  ledin(c1, c2, c3, c4, c5, c6, c7, c8);
BusOut  bab(b1, b2, b3);

 


//Define interrupt inputs
InterruptIn ad(ADULT);
InterruptIn chd(CHILD);
InterruptIn fir(FIRE);


//Define counters
static volatile unsigned int count1;
static volatile unsigned int countmax = 8;
static volatile unsigned int chldcount;
static volatile unsigned int adcount;
static volatile unsigned int barbers;
// static volatile unsigned int barber2;
// static volatile unsigned int barber3;


void handle_barbers()
{
  int i;

  i = 0;
  if ((!bb1 || !bb2) && adcount && adcount - chldcount > 0)
  {
    if (!bb1)
    {
      bb1 = 1;
      --adcount;
      ++barbers;
        ++i;
    }
    else if (!bb2)
    {
      bb2 = 1;
      --adcount;
      ++barbers;
      ++i;
    }
  }
  if (!bb3 && chldcount)
  {
    bb3 = 1;
    chldcount--;
    ++barbers;
    ++i;
  }
  count1 -= i;
}

void updateLEDs()
{
  handle_barbers();
  switch (count1)
  {
      case 0:
        ledin = 0b00000000;
        break ;
      case 1:
        ledin = 0b00000001;
        break ;
      case 2:
        ledin = 0b00000011;
        break;
      case 3:
        ledin = 0b00000111;
        break;
      case 4:
       ledin = 0b00001111;
        break;
      case 5:
        ledin = 0b00011111;
        break;
      case 6:
        ledin = 0b00111111;
        break;
      case 7:
        ledin = 0b01111111;
        break;
      case 8:
        ledin = 0b11111111;
        break;
  }
}


//Define ISRs for the interrupts
void adult_handler(){
	
	if (count1 < countmax)
	{
	    count1++;
	    adcount++;
	    printf("this count %i\n", count1);
	}
	updateLEDs();
	//Write your code here
	
}

void child_handler()
{
	if (count1 < countmax - 1)
	{
	    chldcount++;
	    adcount++;
	    count1 += 2;
	}
	updateLEDs();
	//Write your code here
}

void fire_handler(){
	count1 = 0;
	bab = 0b000;
    adcount = chldcount = 0;
    barbers = 0;
	updateLEDs();
	//Write your code here
	
}


/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
		
	//Initially turn off all LEDs and set all the counters to 0
    updateLEDs();
    int i;

	//Interrupt handlers
	ad.rise(&adult_handler);
	chd.rise(&child_handler);
	fir.rise(&fire_handler);

	
	//Write your code here

	//wait 100 ms
	while(1)
	{
	    if (i == 24)
	    {	            printf("barbers %i\n", barbers);

	        bab = 0;
	        barbers = 0;
	        i = 0;
	        clk = 1;
	        wait_ms(100);
	        updateLEDs();
	        clk = 0;
	    }
	    printf("count = %i\n", count1);
		wait_ms(100);
		++i;
		
	}
}