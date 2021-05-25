/*
 * ATmega32_SPI.h
 *
 * Created: 9/25/2020 2:04:23 PM
 *  Author: ahmedsoliman
 */ 


#ifndef ATMEGA32A_SPI_H_
#define ATMEGA32A_SPI_H_

  
  
typedef enum
{
	SPI_InterruptDisable,
	SPI_InterruptEnable,
}SPI_InterruptState;

typedef enum
{
	SPI_Disable,
	SPI_Enable,
}SPI_Control;

typedef enum
{
	SPI_MSB,
	SPI_LSB,
}SPI_DataOrder;

typedef enum
{
	SPI_SLAVE,
	SPI_MASTER,
}SPI_ModeSelect;

typedef enum
{
	SPI_ClkMode0,
	SPI_ClkMode1,
	SPI_ClkMode2,
	SPI_ClkMode3,
}SPI_ClockModes;

typedef enum
{
	SPI_FCPU_By_2,
	SPI_FCPU_By_4,
	SPI_FCPU_By_8,
	SPI_FCPU_By_16,
	SPI_FCPU_By_32,
	SPI_FCPU_By_64,
	SPI_FCPU_By_128,
}SPI_SCK_Freq;

typedef enum
{
	SPI_NoError,
	SPI_WriteColisionError,
}SPI_Errors;

typedef struct  
{
	SPI_Control                        EnableControl;
	SPI_ModeSelect                     ModeSelect;
	SPI_InterruptState                 InterruptState;
	SPI_DataOrder                      DataOreder;
	SPI_ClockModes                     ClkMode;
	void (*SPI_TransferInterrupCall) (void);
	/* For Slave Mode --- SCK_Freq Should not Be Select */
	SPI_SCK_Freq                       SCKFreq;
	/* This Bit Does Not Cleared It Self --- Check It Before Using Data And Erase The Error Your Self By assign It To SPI_NoError */
	SPI_Errors                         ErrorType;
}SPI_Configuration;


extern SPI_Configuration SPI0 ;

void SPI_Intiat(void);
unsigned char Exchange_Byte_Blocking(unsigned char Data);
unsigned char Exchange_Byte_NoneBlocking(unsigned char Data);


#endif /* ATMEGA32A_SPI_H_ */