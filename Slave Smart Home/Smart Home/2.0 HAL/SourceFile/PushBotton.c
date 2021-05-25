/*
 * PushButton.c
 *
 * Created: 7/20/2020 8:22:37 PM
 *  Author: ahmedsoliman
 */ 
   #include <ATmega32A_Config.h>
   #include <ATmega32A_DIO_Config.h>
   #include <StandardDataType.h>
   #include <util/delay.h>
   #include <PushButton.h>
  
   /* use This Variable To note any change in the Button Pushed Or Released */
   static DigitalValue Push_default_State;



  void PushButton_setup(PushButton_datatype *Pswitch)
  {
	  /* Configuration The Pin Of The Push Button As User State Set  */
	  DIO_pinConfiguration(Pswitch->IO_PORT, Pswitch->IO_PIN, Pswitch->InputMode);
	  /* Setup The TH Previous State Of The Push Button As A Current State When It Just Configure */
	  Pswitch->PREV_Level = DIO_pinRead(Pswitch->IO_PORT,Pswitch->IO_PIN);
	  //setup the default state of the button to know when it pressed or released 
	  Push_default_State = Pswitch->PREV_Level;  
  }
  
  
  
  
  PUSH_States PushButton_read(PushButton_datatype *Pswitch)
  {
	  /* If The User do Not Change The PREV_Level that Mean It Do not press The PushButton Yet So It Will Return It Not Pressed State*/ 
	  PUSH_States returnState = PUSH_NOT_PRESSED;
	  if (Pswitch->PREV_Level != DIO_pinRead(Pswitch->IO_PORT,Pswitch->IO_PIN))
	  {
		  // the average pressed of the human is 500 ms to make sure it not ripple 
		  _delay_ms(Push_Bouncing_Periode_mS);       
		  // to make sure that is not a mess signal
		   if (Pswitch->PREV_Level != DIO_pinRead(Pswitch->IO_PORT,Pswitch->IO_PIN)) 
		   {
			   Pswitch->PREV_Level = DIO_pinRead(Pswitch->IO_PORT,Pswitch->IO_PIN);
			   if (Pswitch->PREV_Level != Push_default_State)
			   {
				   returnState = PUSH_PRESSED;
			   }
			   else
			   {
				   /* If The PREV_Leve(Pin Current Read ) equal The Default State That Mean That The Push ButtonWas Pressed And Released */
				   returnState = PUSH_RELEASED;
			   }				   
		   }
	  }
	  return returnState;
  }