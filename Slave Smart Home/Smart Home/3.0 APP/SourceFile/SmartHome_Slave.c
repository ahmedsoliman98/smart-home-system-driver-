/*
 * SmartHome_Slave.c
 *
 * Created: 4/14/2021 9:37:45 PM
 *  Author: ahmedsoliman
 */ 
#include "ATmega32A_Config.h"
#include "ATmega32A_DIO_Config.h"
#include "ATmega32A_SPI.h"
#include "ATmega32A_Timers_Config.h"
#include "ADC_Config_Driver.h"
#include "SmartHome_Slave.h"


ANALOG_DATATYPE analog_signal = {PIN1, INTERNV}; 
volatile unsigned short temperture = 0;

unsigned char SPI_DataRx = 0;
volatile unsigned char TEMP_LEVEL = 0;

volatile unsigned char count = 0;

/* Set The Timer Number We Used And Its Mode */
TIMER_DATATYPE counter = {Timer0,Timer_CTC_Mode, Timer_Fcpu_Div1024, Timer_TopCTC_Interrupt};

void HomeSlave_INT(void)
{
		
	/* Temperature sensor setup */
	ADC_INTIATE(analog_signal);
	
	/* set up the SPI communication to send and receive the data from the Slave */
	SPI_communcation.EnableControl = SPI_Enable;
	SPI_communcation.DataOreder = SPI_MSB;
	SPI_communcation.ModeSelect = SPI_SLAVE;
	SPI_communcation.ClkMode = SPI_ClkMode0;
	//SPI_communcation.InterruptState = SPI_InterruptDisable;
	//SPI_communcation.SCKFreq = SPI_FCPU_By_2;
	SPI_Intiat();
	
	/* operate the count of the Timer */
	TIMER_INTIATE(counter);
	/* set up the CTC top value on it is register */
	TIMER_DELAY(counter, TOP_CTC_VALUE);
	
	/* Rooms 1,2,3,4 LED's setup on the pin 4,5,6,7 port D */
	DIO_pinConfiguration(ROOMs_PORT, ROOM1_PIN, Output);
	DIO_pinConfiguration(ROOMs_PORT, ROOM2_PIN, Output);
	DIO_pinConfiguration(ROOMs_PORT, ROOM3_PIN, Output);
	DIO_pinConfiguration(ROOMs_PORT, ROOM4_PIN, Output);
	
	/* TV setup */
	DIO_pinConfiguration(TV_PORT, TV_PIN, Output);
	
	/* Air condition setup */
	DIO_pinConfiguration(AIRCOND_PORT, AIRCOND_PIN, Output);
	
	
	
	/* the initial state is the air condition off so we reset the global interrupt to stop the temperature check */
	GLOBAL_INT_DISABLE();
}
void HomeSlave_OPR(void)
{
	SPI_DataRx = Exchange_Byte_Blocking(Dummy);
	switch(SPI_DataRx)
	{
		case ROOM1:
		if (DIO_pinRead(ROOMs_PORT,ROOM1_PIN) == HIGH)
		{
			Exchange_Byte_Blocking(ON);
		}
		else
		{
			Exchange_Byte_Blocking(OFF);
		}
		break;
		case ROOM2:
		if (DIO_pinRead(ROOMs_PORT,ROOM2_PIN) == HIGH)
		{
			Exchange_Byte_Blocking(ON);
		}
		else
		{
			Exchange_Byte_Blocking(OFF);
		}
		break;
		case ROOM3:
		if (DIO_pinRead(ROOMs_PORT,ROOM3_PIN) == HIGH)
		{
			Exchange_Byte_Blocking(ON);
		}
		else
		{
			Exchange_Byte_Blocking(OFF);
		}
		break;
		case ROOM4:
		if (DIO_pinRead(ROOMs_PORT,ROOM4_PIN) == HIGH)
		{
			Exchange_Byte_Blocking(ON);
		}
		else
		{
			Exchange_Byte_Blocking(OFF);
		}
		break;
		case TV:
		if (DIO_pinRead(TV_PORT,TV_PIN) == HIGH)
		{
			Exchange_Byte_Blocking(ON);
		}
		else
		{
			Exchange_Byte_Blocking(OFF);
		}
		break;
		case AirCondition:
		if (DIO_pinRead(AIRCOND_PORT,AIRCOND_PIN) == HIGH)
		{
			Exchange_Byte_Blocking(ON);
		}
		else
		{
			Exchange_Byte_Blocking(OFF);
		}
		break;
		case Temp_Mode:
		TEMP_LEVEL = Exchange_Byte_Blocking(Dummy);
		Exchange_Byte_Blocking(Temp_Mode);
		break;
		/*********************************** Turn ON & OFF Command ********************************************/
		case ROOM1_ON:
		     DIO_pinWrite(ROOMs_PORT, ROOM1_PIN, HIGH);
			 break;
		case ROOM1_OFF:
		DIO_pinWrite(ROOMs_PORT, ROOM1_PIN, LOW);
		break;
		case ROOM2_ON:
		DIO_pinWrite(ROOMs_PORT, ROOM2_PIN, HIGH);
		break;
		case ROOM2_OFF:
		DIO_pinWrite(ROOMs_PORT, ROOM2_PIN, LOW);
		break;
		case ROOM3_ON:
		DIO_pinWrite(ROOMs_PORT, ROOM3_PIN, HIGH);
		break;
		case ROOM3_OFF:
		DIO_pinWrite(ROOMs_PORT, ROOM3_PIN, LOW);
		break;
		case ROOM4_ON:
		DIO_pinWrite(ROOMs_PORT, ROOM4_PIN, HIGH);
		break;
		case ROOM4_OFF:
		DIO_pinWrite(ROOMs_PORT, ROOM4_PIN, LOW);
		break;
		case TV_ON:
		DIO_pinWrite(TV_PORT, TV_PIN, HIGH);
		break;
		case TV_OFF:
		DIO_pinWrite(TV_PORT, TV_PIN, LOW);
		break;
		case AirCond_ON:
		/* enable the temperature check value */
		GLOBAL_INT_ENABLE();
		DIO_pinWrite(AIRCOND_PORT, AIRCOND_PIN, HIGH);
		break;
		case AirCond_OFF:
		GLOBAL_INT_DISABLE();
		DIO_pinWrite(AIRCOND_PORT, AIRCOND_PIN, LOW);
		break;
	}
}


/* this definition we get from the ATmega32A_intrrupt Library we implement */
ISR (TIMER0_COMP_vect)
{
	count++;
	if (count >= 10)
	{
		/* Reset the count value */
		count = 0;
		
	/* we want to return the value of the minimum volt equivalent to the volt read from the analog signal 
	 *
	 *  Vref      ---->    1024  (the value of the 2 power 8 )
	 *  Equ Volt  ---->    READ_VALUE  
	 *
	 *  Equ Volt = ( Vref * READ_VALUE ) / 1024  but we know that Vref/ 1024 equal the Step (Resolution ) Value 
	 * So Equ Volt = Step * READ_VALUE
	 * In This Case 
	 *  value 1C° for 10mV
	 * 2.56 /1024 * 1000 (convert to mV) /10(because 1C° for 10mV) = 0.25
	 */
	temperture = analogRead(analog_signal) * 0.25 ; 
		if (temperture > TEMP_LEVEL)
		{
			DIO_pinWrite(AIRCOND_PORT,AIRCOND_PIN,HIGH);
		}
		else
		{
			DIO_pinWrite(AIRCOND_PORT,AIRCOND_PIN,HIGH);
		}
	}
}
