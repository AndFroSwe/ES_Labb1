#include <asf.h>

void part1()
{
	unsigned int pin;
	unsigned int LEDs[] = {59, 60, 61, 62, 51, 52, 53, 54};
	for (int i = 0; i < 8; ++i )
	{
		pin = LEDs[i];
		gpio_enable_gpio_pin(pin);
		gpio_clr_gpio_pin(pin);
	}
	
}

void part2()
{
	unsigned int LEDPin = 59;
	unsigned int buttonPin = 88;
	unsigned int buttonVal = 0;
	
	gpio_enable_gpio_pin(buttonPin);
	gpio_enable_gpio_pin(LEDPin);
	
	while(1)
	{
		buttonVal = gpio_get_pin_value(buttonPin);
		
		if(buttonVal == 0)
		{
			gpio_clr_gpio_pin(LEDPin);
		}
		else if(buttonVal == 1)
		{
			gpio_set_gpio_pin(LEDPin);
		}
	}
	
}

void part3()
{
	unsigned int green = 51;
	unsigned int red = 52;
	unsigned int buttonPin = 88;
	unsigned int buttonVal = 0;
	int old = 1;
	
	gpio_enable_gpio_pin(buttonPin);
	gpio_enable_gpio_pin(green);
	gpio_enable_gpio_pin(red);
	
	// Set initial state
	unsigned int LEDVal = 0;
	gpio_clr_gpio_pin(green);
	gpio_set_gpio_pin(red);	
	
	// State loop
	while (1)
	{
		buttonVal = gpio_get_pin_value(buttonPin);
		
		// Detect falling edge
		if (buttonVal < old)
		// Detect rising edge
		//if (buttonVal > old)
		
		{		
			if (LEDVal == 1)
			{
				gpio_clr_gpio_pin(green);
				gpio_set_gpio_pin(red);
				LEDVal = 0;
			}
			else if (LEDVal == 0)
			{
				gpio_clr_gpio_pin(red);
				gpio_set_gpio_pin(green);
				LEDVal = 1;
			}
			
		} 
		old = buttonVal;
	}
	
}

void part4()
{
	/*
	left = PA25 = GPIO25
	up = PA26 = GPIO26
	right = PA27 = GPIO27
	down = PA28 = GPIO28
	button = PA20 = GPIO20	 
	*/
	int buttonVal = 1;	
	int up = 26;
	int right = 27;
	int down = 28;
	int left = 25;
	int button = 20;
	int l1 = 59;
	int l2 = 60;
	int l3 = 61;
	int l4 = 62;
	int all[] = {51, 52, 53, 54};
	
	gpio_enable_gpio_pin(up);
	gpio_enable_gpio_pin(l1);
	while (1)
	{
		if (!gpio_get_pin_value(up))
		{
			gpio_clr_gpio_pin(l1);
		}
		else if (!gpio_get_pin_value(right))
		{
			gpio_clr_gpio_pin(l2);
		}
		else if (!gpio_get_pin_value(down))
		{
			gpio_clr_gpio_pin(l3);
		}
		else if (!gpio_get_pin_value(left))
		{
			gpio_clr_gpio_pin(l4);
		}
		else if (!gpio_get_pin_value(button))
		{
			for (int i = 0; i < 4; ++i)
				{
					gpio_clr_gpio_pin(all[i]);
				}
		}
		else
		{	
			gpio_set_gpio_pin(51);
			gpio_set_gpio_pin(52);
			gpio_set_gpio_pin(53);
			gpio_set_gpio_pin(54);
			gpio_set_gpio_pin(59);
			gpio_set_gpio_pin(60);
			gpio_set_gpio_pin(61);
			gpio_set_gpio_pin(62);
		}
	}
}

void part31()
{
	int buttonPin = 88;
	int buttonVal = 1;
	int old = 1;
	int LED = 0x01;
		
	gpio_enable_gpio_pin(buttonPin);
	
	while (1)
	{
		buttonVal = gpio_get_pin_value(buttonPin);
		
		if (buttonVal < old)
		{
			// With display
			//LED_Display(LED);
			// With LED_On/Off
			LED_On(LED);
			
			// Shift led
			if (LED <= 0x80)
			{
				LED = (LED << 1);
			}
			else
			{
				LED = 0x01;
				// With LED_On()
				for (int i = 0; i < 8; ++i)
				{
					LED_Off(0x01 << i);
				}
			}
		}
		old = buttonVal;	
		
	}
	LED_Display(LED0);
	
	
}



int main (void)
{
	board_init();
	//part1();
	//part2();
	//part3();
	//part4();
	part31();
}
