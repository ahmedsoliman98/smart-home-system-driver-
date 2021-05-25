/*
 * ATmega32A_USART.c
 *
 * Created: 9/17/2020 12:29:44 PM
 *  Author: ahmedsoliman
 */ 



#include "ATmega32A_Config.h"
#include "ATmega32A_DIO_Config.h"
#include "ATmega32A_Interrupt.h"
#include "ATmega32A_USART.h"


/* if we have multi USART we can make it on the array and make the config function on the for loop */

/* the best way to set the value than put all in 0 is to make 
                     USART0 = { USART.enableMode = USART_Asyn_DoupleSpeed,
						            .,
									.,
									.,
					            }
*/									
USART_Configuration USART0 = {  0,
	                           /* we make sure that if the user does not point the pointer to any function it will point to 0 instead random adderss */
                               .RXC_InterruptCall = NULL,
							   .TXC_InterruptCall = NULL,
							   .UDRE_InterruptCall = NULL
							 };
		/* ISR mean the interrupt service routine we write it to inform the compiler that is a interrupt function
		 * we write the address of the interrupt from the table of the vector 
		 * so it should write as ISR(_vector(13)) but this is define in the AVR/Interrupt 
		*/ 					 
							 
	/* interrupt function by the RXC */						 
	 ISR (USART_RXC_vect)
	 {
		 if (USART0.RXC_InterruptCall != NULL)
		 {
			 /* if it not point to the zero that mean it point to the interrupt function so we call it using call Back */
			 USART0.RXC_InterruptCall();
		 }
		 else
		 {
			 /* that mean that the interrupt is activate and no function implement 
			  * if the user take the project it is his fault so we keep that else empty 
			  * if you in stage of implementation you should handle the error massage 
			 */
		 }			 
	 }
	 
	 
	 /* interrupt function by the RXC */						 
	 ISR (USART_TXC_vect)
	 {
		 if (USART0.TXC_InterruptCall != NULL)
		 {
			 /* if it not point to the zero that mean it point to the interrupt function so we call it using call Back */
			 USART0.TXC_InterruptCall();
		 }
		 else
		 {
			 /* that mean that the interrupt is activate and no function implement 
			  * if the user take the project it is his fault so we keep that else empty 
			  * if you in stage of implementation you should handle the error massage 
			 */
		 }			 
	 }
	 
	 
	 /* interrupt function by the UDRE */						 
	 ISR (USART_UDRE_vect)
	 {
		 if (USART0.UDRE_InterruptCall != NULL)
		 {
			 /* if it not point to the zero that mean it point to the interrupt function so we call it using call Back */
			 USART0.UDRE_InterruptCall();
		 }
		 else
		 {
			 /* that mean that the interrupt is activate and no function implement 
			  * if the user take the project it is his fault so we keep that else empty 
			  * if you in stage of implementation you should handle the error massage 
			 */
		 }			 
	 }
	
	  void USART_Intia(void)
	  {
		  unsigned char UCSRA_Temp = 0;
		  unsigned char UCSRB_Temp = 0;
		  unsigned char UCSRC_Temp = 0;
		  float   UBRR_Temp = 0.0;
		  
		  switch (USART0.enableMode)
		  {
			  case USART_Disable:
			    
			  break;
			  case USART_Rx_Only:
			       UCSRB_Temp |= (1<<RXEN);
			  break;
			  case USART_Tx_Only:
			       UCSRB_Temp |= (1<<TXEN);
			  break;
			  case USART_TxRx_Enable:
			       UCSRB_Temp |= (1<<RXEN) | (1<<TXEN);
			  break;
			  default:
			  break;
		  }	
		  
		  switch(USART0.communicationMode)
		  {
			  case USART_Asyn_DoupleSpeed:
			       UCSRA_Temp |= (1<<U2X);
				   UBRR_Temp = (((float)F_CPU) / (8.0 * USART0.baudRate)) - 0.5; //to make sure that the output above o.5 will be 1 so we add 0.5 to -1-> in the equation
			  break;
			  
			  case USART_Asyn_SingleSpeed:
			       UBRR_Temp = (((float)F_CPU) / (16.0 * USART0.baudRate)) - 0.5;
			  break;
			  
			  case USART_Sync:
			       UCSRC_Temp |= (1<<UMSEL);
				   UBRR_Temp = (((float)F_CPU) / (2.0 * USART0.baudRate)) - 0.5;
				   switch (USART0.clockPolarity)
				   {
				    case USART_SampleOnFaling:
				   	break;
				    case USART_SampleOnRising:
					     UCSRC_Temp |= (1<<UCPOL);
					break;
					default:
					break;
				   }
			 break;
			  default:
			  break;
		  }
		  
		  switch(USART0.communicationTerminal)
		  {
			  case USART_SingleProcessor:
			  break;
			  case USART_MultiProcessor:
			       UCSRA_Temp |= (1<<MPCM);
			  break;
			  default:
			  break;
		  }
		  
		  switch (USART0.interruptSource)
		  {
		    case USART_InterruptsDisable:
		  	break;
			case USART_RxComInt_Enable:
			     UCSRB_Temp |= (1<<RXCIE);
			break;
			case USART_TxComInt_Enable:
			     UCSRB_Temp |= (1<<TXCIE);
			break;
			case USART_UDRInt_Enable:
			     UCSRB_Temp |= (1<<UDRIE);
			break;
			case USART_RxTxComInt_Enable:
			     UCSRB_Temp |= (1<<RXCIE) | (1<<TXCIE);
			break;
			case USART_RxComUDRInt_Enable:
			     UCSRB_Temp |= (1<<RXCIE) | (1<<UDRIE);
			break;
			case USART_TxComUDRInt_Enable:
			     UCSRB_Temp |= (1<<TXCIE) | (1<<UDRIE);
			break;
			case USART_InterruptsEnable:
			     UCSRB_Temp |= (1<<TXCIE) | (1<<UDRIE) | (1<<RXCIE);
			break;
			default:
			break;
		  }
		  
		  
		  switch(USART0.dataFrame)
		  {
			  case USART_5bitData:
			       
			  break;
			  case USART_6bitData:
			       UCSRC_Temp |= (1<<UCSZ0);
			  break;
			  case USART_7bitData:
			       UCSRC_Temp |= (1<<UCSZ1);
			  break;
			  case USART_8bitData:
			       UCSRC_Temp |= (1<<UCSZ0) | (1<<UCSZ1);
			  break;
			  case USART_9bitData:
			       UCSRC_Temp |= (1<<UCSZ0) | (1<<UCSZ1);
				   UCSRB_Temp |= (1<<UCSZ2);
			  break;
			  default:
			  break;
		  }
		  
		  switch(USART0.frameControl)
		  {
			  case USART_ParityDisable_1Stop:
			  break;
			  case USART_ParityDisable_2Stop:
			       UCSRC_Temp |= (1<<USBS);
			  break;
			  case USART_ParityEven_1Stop:
			       UCSRC_Temp |= (1<<UPM1);
			  break;
			  case USART_ParityEven_2Stop:
			       UCSRC_Temp |= (1<<USBS) | (1<<UPM1);
			  break;
			  case USART_ParityOdd_1Stop:
			       UCSRC_Temp |= (1<<UPM0) | (1<<UPM1);
			  break;
			  case USART_ParityOdd_2Stop:
			       UCSRC_Temp |= (1<<USBS) | (1<<UPM0) | (1<<UPM1);
			  break;
			  default:
			  break;
		  }
		  
		  
		  UCSRA = UCSRA_Temp;
		  UCSRC = UCSRB_Temp;
		  UBRRH = ((unsigned short)UBRR_Temp)>>8;
		  UBRRL = ((unsigned char)UBRR_Temp);
		  UCSRB = UCSRB_Temp; //put in the last because on it the enable bit of the UART
		  		  
	  }
	  
	  void USART_SendByte_Blocking(unsigned short Data)
	  {
		  while ((UCSRA & (1<<UDRE)) == 0)
		  {
			  /* this to blocking on the bit UDRE until it change to 1 to start transmit*/
		  }
		  if (USART0.dataFrame == USART_9bitData)
		  {
			  /*
			   * UCSRB & 1111 1110 to make sure the bit 0 is reset to hold the new value because it does not mention in data sheet
			   * we need to take the bit 9  in the data and hold it in the bit 0  in the UCSRB so we & the data with 8 to get 
			   *  and shift it again to put in the position of the bit 0
			   */ 
			  UCSRB = (UCSRB & 0xFE) | ((Data & (1<<8))>>8);
		  }
		  /* casting the data to char to get only the 8 bit */
		  UDR = (unsigned char) Data;
	  }
	  
	  /* this function is use in case called by interrupt */
	  void USART_SendByte_NoneBlocking(unsigned short Data)
	  {
		  if ((UCSRA & (1<<UDRE)) != 0)
		  {
			
			  if (USART0.dataFrame == USART_9bitData)
			  {
				  /*
				   * UCSRB & 1111 1110 to make sure the bit 0 is reset to hold the new value because it does not mention in data sheet
				   * we need to take the bit 9  in the data and hold it in the bit 0  in the UCSRB so we & the data with 8 to get 
					   and shift it again to put in the position of the bit 0
				  */ 
				  UCSRB = (UCSRB & 0xFE) | ((Data & (1<<8))>>8);
			  }
			  /* casting the data to char to get only the 8 bit */
			  UDR = (unsigned char) Data;
		  }		  		  		    
		
	  }
	  
	  unsigned short USART_ReadByte_Blocking(void)
	  {
		  /* this variable to hold the 9bit data */
		  unsigned short RxData = 0x00;
		  
		  while ((UCSRA & (1<<RXC)) == 0)
		  {
			  /* this flag set when there was unread data in the receive buffer so we blocking until it set */ 
		  }
		  
		  if (UCSRA & ((1<<FE) | (1<<DOR) | (1<<PE)))
		  {
			  /* error handle as you wish */
			  if(UCSRA & (1<<FE))
			  {
				  USART0.errorType = USART_FrameError;
			  }	
			  else if(UCSRA & (1<<DOR))
			  {
				  USART0.errorType = USART_OverRunError;
			  }
			  else if(UCSRA & (1<<PE))
			  {
				  USART0.errorType = USART_ParityError;
			  }
			  			  
		  }
		  
		  if(USART0.dataFrame == USART_9bitData)
		  {
			  /* get the 9bit from the bit 1 in the UCSRB then shift it to left by 7 to hold in 9bit */
			  RxData = ((UCSRB & (1<<RXB8)) << 7);
		  }
		  
		  RxData |= UDR;
		  return RxData;
		  
	  }
	  
	  
	  unsigned short USART_ReadByte_NoneBlocking(void)
	  {
		  /* this variable to hold the 9bit data */
		  unsigned short RxData = 0x00;
		  
		  if ((UCSRA & (1<<RXC)) != 0)
		  {
		  
			  if (UCSRA & ((1<<FE) | (1<<DOR) | (1<<PE)))
			  {
				  /* error handle as you wish */
				  if(UCSRA & (1<<FE))
				  {
					  USART0.errorType = USART_FrameError;
				  }
				  else if(UCSRA & (1<<DOR))
				  {
					  USART0.errorType = USART_OverRunError;
				  }
				  else if(UCSRA & (1<<PE))
				  {
					  USART0.errorType = USART_ParityError;
				  }
			  
			  }
		  
			  if(USART0.dataFrame == USART_9bitData)
			  {
				  /* get the 9bit from the bit 1 in the UCSRB then shift it to left by 7 to hold in 9bit */
				  RxData = ((UCSRB & (1<<RXB8)) << 7);
			  }
		  }			
		  
			RxData |= UDR;
			return RxData;
		 	  
		  
	  }