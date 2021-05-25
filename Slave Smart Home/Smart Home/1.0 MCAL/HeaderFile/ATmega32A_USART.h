/*
 * ATmega32A_USART.h
 *
 * Created: 9/17/2020 12:30:14 PM
 *  Author: ahmedsoliman
 */ 


#ifndef ATMEGA32A_USART_H_
#define ATMEGA32A_USART_H_

   typedef enum 
   {
	   USART_Asyn_DoupleSpeed,
	   USART_Asyn_SingleSpeed,
	   USART_Sync,
   }USART_CommunicationMode;
   
   typedef enum
   {
	   USART_SingleProcessor,
	   USART_MultiProcessor,
   }USART_CommunicationTerminal;
   
   typedef enum 
   {
	   USART_Disable,
	   USART_Tx_Only,
	   USART_Rx_Only,
	   USART_TxRx_Enable,
   }USART_EnableMode;
   
   typedef enum
   {
	   USART_InterruptsDisable,
	   USART_RxComInt_Enable,
	   USART_TxComInt_Enable,
	   USART_UDRInt_Enable,
	   USART_RxTxComInt_Enable,
	   USART_RxComUDRInt_Enable,
	   USART_TxComUDRInt_Enable,
	   USART_InterruptsEnable,
   }USART_InterruptSources;
   
   typedef enum
   {
	  USART_5bitData,
	  USART_6bitData,
	  USART_7bitData,
	  USART_8bitData,
	  USART_9bitData, 
   }USART_DataFrame;
   
   typedef enum
   {
	   USART_ParityDisable_1Stop,
	   USART_ParityDisable_2Stop,
	   USART_ParityEven_1Stop,
	   USART_ParityEven_2Stop,
	   USART_ParityOdd_1Stop,
	   USART_ParityOdd_2Stop,
   }USART_FrameControl;
   
   typedef enum
   {
	   USART_NoError,
	   USART_ParityError,
	   USART_OverRunError,
	   USART_FrameError,
   }USART_ErroreType;
   
   
  typedef enum
  {
	  USART_SampleOnFaling,
	  USART_SampleOnRising,
  }USART_ClockPolarity;
  
  typedef struct  
  {
	  /*please refer to Upper Enum for detail on what to select */
	  USART_EnableMode                           enableMode;
	  USART_CommunicationMode                    communicationMode;
	  USART_CommunicationTerminal                communicationTerminal;
	  USART_InterruptSources                     interruptSource;
	  USART_DataFrame                            dataFrame;
	  USART_FrameControl                         frameControl;
	  /* only use in case of Synchronous communication */ 
	  USART_ClockPolarity                        clockPolarity;
	  /* read this flag before using data returned by read function , clear flag your self */
	  USART_ErroreType                           errorType;
	  unsigned long                             baudRate;
	  /* call Back Member */
	  /* Make the Pointer Point to Function you wish to be Called by the RXC interrupt */
	  void (*RXC_InterruptCall)(void); 
	  /* Make the Pointer Point to Function you wish to be Called by the TXC interrupt */
	  void (*TXC_InterruptCall)(void);
	  /* Make the Pointer Point to Function you wish to be Called by the UDRE interrupt */
	  void (*UDRE_InterruptCall)(void);
  }USART_Configuration;
  
  
  /* this to make it global the user in main can call "USART0" and change it value */
  extern USART_Configuration USART0;
 
  
  void USART_Intia(void);
  
  void USART_SendByte_Blocking(unsigned short Data);
  void USART_SendByte_NoneBlocking(unsigned short Data);
  unsigned short USART_ReadByte_Blocking(void);
  unsigned short USART_ReadByte_NoneBlocking(void);


#endif /* ATMEGA32A_USART_H_ */