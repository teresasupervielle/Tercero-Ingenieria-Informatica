#ifndef LED_BUTTON_H_
#define LED_BUTTON_H_

#define LED_TOGGLE(ADDRESS,BIT)		ADDRESS ^=	(1<<BIT)
#define LED_ON(ADDRESS,BIT)			ADDRESS |=	(1<<BIT)
#define LED_OFF(ADDRESS,BIT)		ADDRESS &=	~(1<<BIT)

#define	IS_PIN_ZERO(ADDRESS,BIT)	!(ADDRESS &(1<<BIT))	// Flag=0 --> TRUE
#define	READ_BUTTON(ADDRESS,BIT)	(ADDRESS &(1<<BIT))		// Check the button state

#define BUTTON_PRESSED				0
#define BUTTON_NOT_PRESSED			1

//PARÁMETROS

#define DEBOUNCE_TIME	100
#define BLINK_TIME 100

#endif /* LED_BUTTON_H_ */
