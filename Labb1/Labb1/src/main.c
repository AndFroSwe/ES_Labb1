/* Labb 1 Task 1: Light all leds */
#include <asf.h>

#define switch1 88

volatile int vol_state = 1;

__attribute__((__interrupt__)) static void interrupt(void)
{
	if (vol_state == 1)
	{
		vol_state = 2;
	}
	else if (vol_state == 2)
	{
		vol_state = 1;
	}
	
	gpio_clear_pin_interrupt_flag(switch1);
}



void initLED (int port, int bit)
{
	AVR32_GPIO.port[port].gpers = 1 << bit;
	AVR32_GPIO.port[port].oders = 1 << bit;
}

void lightLED (int port, int bit)
{
	AVR32_GPIO.port[port].ovrc = 1 << bit;
}

void closeLED (int port, int bit)
{
	AVR32_GPIO.port[port].ovrs = 1 << bit;
}

void part1 ()
{
	// Light all leds
	int light[] = {27, 28, 29, 30, 19, 20, 21, 22};
	for(int i=0; i<8; ++i)
	{
		lightLED(1, light[i]);
	}
}

void part2()
{
	// Turn off one when pressing a button
	while(1)
	{
		int i=(AVR32_GPIO.port[2].pvr >> 24) & 0x01;
		
		if(i==1)
		{
			lightLED(1, 22);
		}
		else if (i==0)
		{
			closeLED(1, 22);
		}
	}
	
}

void part3()
{
//Change state of led with interupt
	// Interrupt initiation
	INTC_init_interrupts();
	INTC_register_interrupt(&interrupt, (AVR32_GPIO_IRQ_0+88/8), AVR32_INTC_INT0);
	// Set response time for switch
	gpio_enable_pin_glitch_filter(switch1);
	// Enable a pin and define type
	gpio_enable_pin_interrupt(switch1, GPIO_FALLING_EDGE);
	// Enable global interrupts
	Enable_global_interrupt();

	// Initial state
	vol_state = 1;
	while(1)
	{
		int i=(AVR32_GPIO.port[2].pvr >> 24) & 0x01;
		

		if (vol_state == 1)
		{
			lightLED(1, 20);
			closeLED(1, 19);
		}
		else if (vol_state == 2)
		{
			lightLED(1, 19);
			closeLED(1, 20);
		}
		
	}
	
}

void part4()
{
//Change state of led with interupt
	// Interrupt initiation
	INTC_init_interrupts();
	INTC_register_interrupt(&interrupt, (AVR32_GPIO_IRQ_0+88/8), AVR32_INTC_INT0);
	// Set response time for switch
	gpio_enable_pin_glitch_filter(switch1);
	// Enable a pin and define type
	gpio_enable_pin_interrupt(switch1, GPIO_RISING_EDGE);
	// Enable global interrupts
	Enable_global_interrupt();

	// Initial state
	vol_state = 1;
	while(1)
	{
		int i=(AVR32_GPIO.port[2].pvr >> 24) & 0x01;
		

		if (vol_state == 1)
		{
			lightLED(1, 20);
			closeLED(1, 19);
		}
		else if (vol_state == 2)
		{
			lightLED(1, 19);
			closeLED(1, 20);
		}
		
	}
	
}



int main ()
{
	board_init();
	//part1();
	//part2();
	//part3();
	part4();

	return 0;

}
