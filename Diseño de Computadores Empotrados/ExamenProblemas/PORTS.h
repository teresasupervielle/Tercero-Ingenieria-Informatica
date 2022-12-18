#ifndef PORTS_H_
#define PORTS_H_
///MCU Port where the LED is connected. Mode Configuration register.
#define GPIO_D_MODE		DDRD
///Pin where every LED is connected.
#define LED_MODE			PORTD2
#define BOMBILLA			PORTD3
///MCU port where the LED is connected.
#define GPIO_D_OUT		PORTD
///MCU port where the PUSHBUTTON is connected.
#define GPIO_D_IN		PIND
///Pin where the BUTTON is connected.
#define BUTTON_INTRO_PIN		PIND6
#define BUTTON_MODE_PIN			PIND7
///Pull-up for PUSHBUTTON
#define BUTTON_INTRO	PORTD6
#define BUTTON_MODE		PORTD7
//POT y LDR
#define ADC_OUT		PINC
#define ADC_PORT	PORTC1
#define LED_LIGHT	PORTC2

/**---------  FUNCTIONS -------------------------*/
/// Pin and ports configuration function.
static inline void configPorts(void){
	/// 1) LED as output
	GPIO_D_MODE |= ((1 << LED_MODE) | (1 << BOMBILLA));
	/// 2) Enable Pull-up for Pushbutton
	GPIO_D_OUT	|= (1 << BUTTON_INTRO) | (1 << BUTTON_MODE);
	
	//ADC_OUT &= ~((1 << ADC_PORT) | (1 << LED_LIGHT));
}

#endif /* PORTS_H_ */
