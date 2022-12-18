#ifndef TMR0_H_
#define TMR0_H_

#define DIV_CLK_1		1
#define DIV_CLK_8		2
#define DIV_CLK_64		3
#define DIV_CLK_256		4
#define DIV_CLK_1024	5


static inline void TMR0_CTC_Interrupt_Init(void){
	/// 1.- Clear a previous configuration
	TCCR0A &= ~((1<<WGM01)|(1<<WGM00));
	TCCR0B &= ~((1 << WGM02));
	/// 2.- Set TMR1 Mode as CTC on OCR1A
	TCCR0B |= (1 << WGM02);	
	/// 3.- Enable interrupt on compare match
	TIMSK0 |= (1 << OCIE0A);			
}

static inline void TMR0_CTC_Init(void){
	/// 1.- Clear a previous configuration
	TCCR0A &= ~((1<<WGM01)|(1<<WGM00));
	TCCR0B &= ~((1 << WGM02));
	/// 2.- Set TMR1 Mode as CTC on OCR1A
	TCCR0A |= (1 << WGM01);

	/// 3.- Enable interrupt on compare match
	TIMSK0 |= (1 << OCIE0A);;
}

static inline void TMR0_CTC_enaInterrupt(){
	/// 3.- Enable interrupt on compare match
	TIMSK0 |= (1 << OCIE0A);
}

static inline void TMR0_CTC_disInterrupt(){
	/// 3.- Enable interrupt on compare match
	TIMSK0 &= ~(1 << OCIE0A);
}


static inline void TMR0_CTC_Start(uint8_t divClock){
	// 1.- Clear the flag (not necessary in cTC with ISR)
	 TIFR0 |= (1<<OCF0A);
	 TCNT0=0;
	// 2.- Set the prescaler and start
	TCCR0B |= (divClock << CS00);
}


static inline void TMR0_CTC_Stop(void){
	TCCR0B &= ~((1 << CS02)|(1 << CS01)|(1 << CS00));
}

static inline void TMR0_CTC_Set(uint8_t valueCounterA){
	/// 1.- Set the matching value in OCR1A
	OCR0A = valueCounterA; 	
}

static inline void TMR0_HW_toogleOC0A(){
	//1.- It is mandatory set OC1A as output (Pin PB1)
	DDRB	|=(1<<DDB1);			
	//2.- Set Toggle as the hardware output in OC1A 
	TCCR0A	|= (1 << COM0A0);		// Toggle OC1A on Compare Match.
	TCCR0A	&= ~(1 << COM0A1);		// Toggle OC1A on Compare Match.
	//3.- Set the mode CTC for using the Hw generator waveform
	TCCR0B	|= (1 << WGM02);		// Mode CTC
	TCCR0A &= ~((1 << WGM01)|(1 << WGM00));

}

#endif