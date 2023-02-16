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

//Define outputs
DigitalOut l1(c1);
DigitalOut l2(c1);
DigitalOut l3(c1);
DigitalOut l4(c1);
DigitalOut l5(c1);
DigitalOut l6(c1);
DigitalOut l7(c1);
DigitalOut l8(c1);
 


//Define interrupt inputs
InterruptIn ad(ADULT);
InterruptIn chd(CHILD);
InterruptIn fir(FIRE);


//Define counters
static volatile unsigned int count1;
static volatile unsigned int countmax;


void updateLEDs(){
  l1 = 0;
  l2 = 0;
  l3 = 0;
  l4 = 0;
  l5 = 0;
  l6 = 0;
  l7 = 0;
  l8 = 0;
  countmax = 8;
  
  switch (count1)
  {
      case 1:
        l1 =1;
        break ;
      case 2:
            printf("here\n");
        l1 = 1;
        l2 = 1;
        break;
      case 3:
        l1 = l2 = l3 = 1;
        break;
      case 4:
        l1 = l2 = l3 = l4 = 1;
        break;
      case 5:
        l1 = l2 = l3 = l4 = l5 = 1;
        break;
      case 6:
        l1 = l2 = l3 = l4 = l5 = l6 = 1;
        break;
      case 7:
        l1 = l2 = l3 = l4 = l5 = l6 = l7 = 1;
        break;
      case 8:
        l1 = l2 = l3 = l4 = l5 = l6 = l7 = l8 = 1;
        break;
  }
}


//Define ISRs for the interrupts
void adult_handler(){
	
	if (count1 < countmax)
	    count1++;
	updateLEDs();
	//Write your code here
	
}

void child_handler(){
	if (count1 < countmax - 1)
	    count1 += 2;
	updateLEDs();
	//Write your code here
	
}

void fire_handler(){
	count1 = 0;
	updateLEDs();
	//Write your code here
	
}


/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
		
	//Initially turn off all LEDs and set all the counters to 0
    updateLEDs();

	//Interrupt handlers
	ad.rise(&adult_handler);
	chd.rise(&child_handler);
	fir.rise(&fire_handler);

	
	//Write your code here

	//wait 100 ms
	while(1)
	{
	    printf("count = %i\n", count1);
		wait_ms(100);
	}
}
