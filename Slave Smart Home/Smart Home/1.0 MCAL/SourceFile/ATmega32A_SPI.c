/*
 * ATmega32A_SPI.c
 *
 * Created: 9/25/2020 2:04:47 PM
 *  Author: ahmedsoliman
 */ 

#include "ATmega32A_SPI.h"
#include "ATmega32A_Config.h"
#include "ATmega32A_DIO_Config.h"
#include <avr/interrupt.h>
#include <avr/io.h>




#define SS     PIN4
#define MOSI   PIN5
#define MISO   PIN6
#define SCK    PIN7


/* if we have multi SPI we can make it on the array and make the config function on the for loop */

/* the best way to set the value than put all in 0 is to make 
                     SPI0 = { SPI.enableMode = SPI_Enable,
						            .,
									.,
									.,
					            }
*/

SPI_Configuration SPI0 = {.SPI_TransferInterrupCall = NULL};


ISR (SPI_STC_vect)
{
	if (SPI0.SPI_TransferInterrupCall != NULL)
	{
		SPI0.SPI_TransferInterrupCall();
	}
}


void SPI_Intiat(void)
{
	/* at the First We Make The 2 Reg Of The SPI All 0 */
	SPCR = 0;
	SPSR = 0;
	switch (SPI0.EnableControl)
	{
		case SPI_Disable :
		/* In this Case We Should Put Bit Of the SPE In SPCR 0 And We Already Make All the Reg By 0 */
		break;
		case SPI_Enable :
		/* Configure The SPI Communication Setting */
		switch (SPI0.ModeSelect)
		{
			case SPI_SLAVE :
			/* Make The Pin MISO As Output */
			//DDRB |= (1<<MISO);
			DIO_pinConfiguration(GPIOB, MISO, Output);
			DIO_pinConfiguration(GPIOB, MOSI, InputFloat);
			DIO_pinConfiguration(GPIOB, SS, InputFloat);
			break;
			case SPI_MASTER :
			/* Set the Bit MSTR In The Reg SPCR */
			//SPCR |= (1<<MSTR);
			SET_Bit(SPCR,MSTR);
			/* Make The Default Pin SCK , SS , MOSI an Output */
			//DDRB |= (1<<MOSI) | (1<<SS) | (1<<SCK);
			DIO_pinConfiguration(GPIOB, MOSI, Output);
			DIO_pinConfiguration(GPIOB, SS, Output);
			DIO_pinConfiguration(GPIOB, SCK, Output);
			/* Make The Pins MOSI, SS  As Default State HIGH */
			//PORTB |= (1<<SS) | (1<<MOSI); 
			DIO_pinWrite(GPIOB, MOSI, HIGH);
			DIO_pinWrite(GPIOB, SS, HIGH);
			break;
		}
		switch (SPI0.DataOreder)
		{
			case SPI_MSB :
			/* In this Case We Should Put Bit Of the DORD In SPCR 0 And We Already Make All the Reg By 0 */
			break;
			case SPI_LSB :
			//SPCR |= (1<<DORD);
			SET_Bit(SPCR, DORD);
			break;
		}
		switch (SPI0.InterruptState)
		{
			case SPI_InterruptDisable:
			/* In this Case We Should Put Bit Of the SPIE In SPCR 0 And We Already Make All the Reg By 0 */
			break;
			case SPI_InterruptEnable:
			//SPCR |= (1<<SPIE);
			SET_Bit(SPCR, SPIE);
			break;
		}
		switch (SPI0.ClkMode)
		{
			/* Get From The Table 59 In The Page 139 In the Data Sheet */
			/* Sample(L) On Rising Setup(T) On the Falling */
			case SPI_ClkMode0:
			/* In this Case We Should Put Bit Of the CPOL,CPHA In SPCR 0 And We Already Make All the Reg By 0 */
			break;
			/* Setup(L) On Rising Sample On The Falling(T) */
			case SPI_ClkMode1:
			//SPCR |= (1<<CPHA);
			SET_Bit(SPCR, CPHA);
			break;
			/* Sample(T) On Rising Setup(L) On the Falling */
			case SPI_ClkMode2:
			//SPCR |= (1<<CPOL);
			SET_Bit(SPCR, CPOL);
			/* 
			 * Note : if Used SPI Mode 3 or Mode 2 (CLK IDLE STATE = HIGH)
			 * in Some MicroControllers we must Explicitly State that The Default clk pin state is High 
			 * By Setting the pin to Output with a High Value 
			 */
			//PORTB |= (1<<SCK);
			DIO_pinWrite(GPIOB, SCK, HIGH);
			break;
			/* Setup(T) On Rising Sample On The Falling(L) */
			case SPI_ClkMode3:
			//SPCR |= (1<<CPHA) | (1<<CPOL);
			SET_Bit(SPCR, CPHA);
			SET_Bit(SPCR, CPOL);
			//PORTB |= (1<<SCK);
			DIO_pinWrite(GPIOB, SCK, HIGH);
			break;
		}
		switch (SPI0.SCKFreq)
		{
			/* Get From The Table 58 In Page 137 In Data sheet */
			case SPI_FCPU_By_2:
			//SPSR |= (1<<SPI2X);
			SET_Bit(SPSR, SPI2X);
			break;
			case SPI_FCPU_By_4:
			/* In this Case We Should Put Bit Of the SPR0,SPR1,SPI2X In SPCR 0 And We Already Make All the Reg By 0 */
			break;
			case SPI_FCPU_By_8:
			//SPSR |= (1<<SPI2X);
			//SPCR |= (1<<SPR0);
			SET_Bit(SPSR, SPI2X);
			SET_Bit(SPCR, SPR0);
			break;
			case SPI_FCPU_By_16:
			//SPCR |= (1<<SPR0);
			SET_Bit(SPCR, SPR0);
			break;
			case SPI_FCPU_By_32:
			//SPSR |= (1<<SPI2X);
			//SPCR |= (1<<SPR1);
			SET_Bit(SPSR, SPI2X);
			SET_Bit(SPCR, SPR1);
			break;
			case SPI_FCPU_By_64:
			//SPCR |= (1<<SPR1);
			SET_Bit(SPCR, SPR1);
			break;
			case SPI_FCPU_By_128:
			//SPCR |= (1<<SPR0) | (1<<SPR1);
			SET_Bit(SPCR, SPR0);
			SET_Bit(SPCR, SPR1);
			break;
		}
		/* Enable SPI Communication */
		SPCR |= (1<<SPE);		
		break;
	}
}


unsigned char Exchange_Byte_Blocking(unsigned char Data)
{
	/* Transmit Data Using SPI */
	SPDR = Data;
	
	/* Chick If The Write Collision Error Occurred */
	if ((READ_Bit(SPSR, WCOL)) != 0)
	{
		SPI0.ErrorType = SPI_WriteColisionError;
	}
	
	/* Stuck Until The Transmission Is End */
	while ((READ_Bit(SPSR,SPIF)) == 0) {};
	
	/* Return Rx Data */
	return SPDR ;
}	
unsigned char Exchange_Byte_NoneBlocking(unsigned char Data)
{
	/* Transmit Data Using SPI */
	SPDR = Data;
	
	/* Chick If The Write Collision Error Occurred */
	if ((READ_Bit(SPSR, WCOL)) != 0)
	{
		SPI0.ErrorType = SPI_WriteColisionError;
	}
	
	/* Return Rx Data */
	return SPDR ;
}
