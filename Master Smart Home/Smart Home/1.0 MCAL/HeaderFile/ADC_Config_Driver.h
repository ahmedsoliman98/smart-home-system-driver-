/*
 * ADC_Config_Driver.h
 *
 * Created: 12/5/2020 2:41:35 PM
 *  Author: ahmedsoliman
 *
 ********************* Internal Structure *********************
 *
 * The Analog To Digital Converter in The ATmega32 features a 10-bit successive approximation ADC. 
 * The ADC is connected to an 8-channel Analog Multiplexer which allows 8 single-ended voltage inputs constructed from the
 * pins of Port A. The single-ended voltage inputs refer to 0V (GND).
 *
 ***************** Operating Mode *****************************
 *
 * The device also supports 16 differential voltage input combinations. Two of the differential inputs (ADC1, ADC0 and ADC3, ADC2) are equipped with a programmable gain stage
 * The ADC contains a Sample and Hold circuit which ensures that the input voltage to the ADC isheld at a constant level during conversion
 * 10-bit Resolution, The ADC has a separate analog supply voltage pin, AVCC. AVCC must not differ more than ±0.3V from VCC
 * Internal reference voltages of nominally 2.56V or AVCC are provided On-chip.
 * The voltage reference may be externally decoupled at the AREF pin by a capacitor for better noise performance
 *
 **************** ******** Pin Input **************************************
 * 
 * It Have 8 Input pin Can Get The Analog Signal To it From PinA0 - PinA7 
 * This Input To The Multiplexer That controlled by a five terminal to select which of them will enter the sample and hold circuit
 * AVCC connect to the VCC of the microcontroller or difference by 0.3 only
 *  
 ***************** ADC Register ***********************
 * It Have Four Register 
 *  1- ADCMUX 
 *     bit0 - bit4 MUX selection bit i function to choose the bin from the port A to enter to the sample circuit
 *     bit5 ADLAR  ADC Left adjust bit it caused the ADCH hold the all bit expect the bit ADC0 and ADC1 it be in the bit 6/7 in ADCL
 *     bit6 and bit7 REF0 , REF1 it decide from where get the value of the Volt Refrence 
 *        
 *     REF0     REF1
 *      0        0    AREF is the Vrefrence
 *      0        1    AVCC become the Vrefrence and AREF connect to the capacitor 10U to ground 
 *      1        0     -
 *      1        1     the Vrefrence became the internal voltage 2.56V and AREF connect to the capacitor 10U to ground 
 *
 *    
 *
 *  2- ADCSRA is the statues and control register
 *    from Bit0 - Bit2 ADPS0 - ADPS2 it is the prescaler bits that select the value of the prescaler that divide to the F_CPU to get the frequency of the clock input to the ADC
 *    Bit3 ADIE   interrupt enable bit
 *    Bit4 ADIF   interrupt flag bit 
 *    bit5 ADATE  auto trigger enable 
 *    bit6 ADSC   start conversion bit used in the single conversion mode 
 *    bit7 ADEN   enable ADC 
 *
 * 
 */ 

#ifndef ADC_CONFIG_DRIVER_H_
#define ADC_CONFIG_DRIVER_H_


	typedef enum
	{
		ADC_INT_DISABLE,
		ADC_INT_ENABLE,
	}ADC_INT_STATE;

	typedef enum
	{
		SINGLE_CONV,
		FREE_RUNNING,
		EX_INT_REQ,
		TIMERCO0_COMPMATCH,
		TIMERCO0_OF,
		TIMERCO1_COMMATCHB,
		TIMERCO1_OF,
		TIMERCO0_CAPEVENT,
	}ADC_CONVERSIN;

	typedef enum
	{
		AVCC,
		AREF,
		INTERNV,
	}ADC_VREFRENCE;

	typedef enum
	{
		FCPU_DIV128,
		FCPU_DIV64,
		FCPU_DIV32,
		FCPU_DIV16,
		FCPU_DIV8,
		FCPU_DIV4,
		FCPU_DIV2,
	}ADC_PRESCALER;
	
	typedef enum
	{
		ADJUST_RIGHT,
		ADJUST_LEFT,
	}ADC_DATA_SORT;

	typedef struct
	{
		pinNumber ADC_PIN;
		ADC_VREFRENCE REF_Voltage;
		ADC_INT_STATE INT ;
		ADC_PRESCALER ADC_CLK_In;
		ADC_CONVERSIN Conv_Type;
		ADC_DATA_SORT ADC_SORT;
	}ANALOG_DATATYPE;

		void ADC_INTIATE(ANALOG_DATATYPE ADC_signal);
		int analogRead(ANALOG_DATATYPE ADC_signal);


#endif /* ADC_CONFIG_DRIVER_H_ */