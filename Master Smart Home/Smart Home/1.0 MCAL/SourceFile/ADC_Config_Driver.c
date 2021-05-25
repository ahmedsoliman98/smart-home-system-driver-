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
#include "ATmega32A_Config.h"
#include "ATmega32A_DIO_Config.h"
#include "StandardDataType.h"
#include "ATmega32A_Interrupt.h"
#include "ADC_Config_Driver.h"


#define LEVEL_NUM    (1024)


void ADC_INTIATE(ANALOG_DATATYPE ADC_signal)
{
	char ADCSRA_temp = 0x00;
	char ADCMUX_temp = 0x00;
	
	/* Set The Clock input Frequency */
	switch(ADC_signal.ADC_CLK_In)
	{
		case FCPU_DIV2:
		     /* it the default case when all the bit became 0*/
		break;
		case FCPU_DIV4:
		     SET_Bit(ADCSRA_temp,ADPS1);
		break;
		case FCPU_DIV8:
		     SET_Bit(ADCSRA_temp,ADPS0);
			 SET_Bit(ADCSRA_temp,ADPS1);
		break;
		case FCPU_DIV16:
			 SET_Bit(ADCSRA_temp,ADPS2);
		break;
		case FCPU_DIV32:
		     SET_Bit(ADCSRA_temp,ADPS0);
		     SET_Bit(ADCSRA_temp,ADPS2);
		break;
		case FCPU_DIV64:
		     SET_Bit(ADCSRA_temp,ADPS1);
		     SET_Bit(ADCSRA_temp,ADPS2);
		break;
		case FCPU_DIV128:
		     SET_Bit(ADCSRA_temp,ADPS0);
			 SET_Bit(ADCSRA_temp,ADPS1);
		     SET_Bit(ADCSRA_temp,ADPS2);
		break;
	}
	
	/* Set The Configuration of The Pin As An Input Pin */
	DIO_pinConfiguration(GPIOA, ADC_signal.ADC_PIN, InputFloat);
	
	/* Set the pin of the Multiplexer to make it sample */
	switch(ADC_signal.ADC_PIN)
	{
		case PIN0:
		     /* it The Default State */
		break;
		case PIN1:
		     SET_Bit(ADCMUX_temp, MUX0);
		break;
		case PIN2:
		     SET_Bit(ADCMUX_temp, MUX1);
		break;
		case PIN3:
		     SET_Bit(ADCMUX_temp, MUX0);
			 SET_Bit(ADCMUX_temp, MUX1);
		break;
		case PIN4:
		     SET_Bit(ADCMUX_temp,MUX2);
		break;
		case PIN5:
		     SET_Bit(ADCMUX_temp, MUX0);
			 SET_Bit(ADCMUX_temp,MUX2);
		break;
		case PIN6:
		     SET_Bit(ADCMUX_temp, MUX1);
			 SET_Bit(ADCMUX_temp,MUX2);
		break;
		case PIN7:
		     SET_Bit(ADCMUX_temp, MUX0);
			 SET_Bit(ADCMUX_temp, MUX1);
			 SET_Bit(ADCMUX_temp,MUX2);
		break;
	}
	
	/* Interrupt State */
	switch(ADC_signal.INT)
	{
	   case ADC_INT_DISABLE:
	        /* It The Default State */
	   break;
	   case ADC_INT_ENABLE:
	        SET_Bit(ADCSRA_temp, ADIE);
	   break;
	}
	
	/* Set The Voltage Reference Of The ADC */
	switch(ADC_signal.REF_Voltage)
	{
		case AREF:
		     /* it The Default State The 2 Bits Is 0 */
		break;
		case AVCC:
		/* Note at This Case the AREF Connect With a capacitor to Ground */
		     SET_Bit(ADCMUX_temp,REF0);
		break;
		case INTERNV:
		/* The Value Of The iternal Voltage is 2.56 V */
		    SET_Bit(ADCMUX_temp,REF0);
			SET_Bit(ADCMUX_temp,REF1);
		break;
	}
	
	/* The Data Sort In The ADCL , ADCH Register State */
	switch(ADC_signal.ADC_SORT)
	{
		case ADJUST_RIGHT:
		/* it The Default State The 2 Bits Is 0 */
		break;
		case ADJUST_LEFT:
		     SET_Bit(ADCMUX_temp,ADLAR);
			 /* The Data Will Sort In The ADCH expect The bit ADC0, and ADC1 will Be In the ADCL */
		break;
	}
	
	/* The Conversion Mode */
	switch(ADC_signal.Conv_Type)
	{
		case SINGLE_CONV:
		break;
		case FREE_RUNNING:
		break;
		case EX_INT_REQ :
		break;
		case TIMERCO0_COMPMATCH:
		break;
		case TIMERCO0_OF:
		break;
		case TIMERCO1_COMMATCHB:
		break;
		case TIMERCO1_OF:
		break;
		case TIMERCO0_CAPEVENT:
		break;
		/* it Will Handle When it Needed */
	}
	
	ADCMUX = ADCMUX_temp;
	ADCSRA = ADCSRA_temp;
	/* Enable The ADC Bit */
	SET_Bit(ADCSRA, ADEN);
}




int analogRead(ANALOG_DATATYPE signal)
{
	unsigned int DataRead = 0x00;
	/*  as A default We in the Single Conversion Mode */
	/* Set Bit ADSC to Start The Conversion */
	SET_Bit(ADCSRA, ADSC); 
	while (READ_Bit(ADCSRA,ADSC) == 0);
	/* it Must in THe Right Adjust Mode Read The ADCL register Before The ADCH */
	DataRead = ADCL; 
	DataRead |= (ADCH << 8);
	
	return DataRead;
	
}