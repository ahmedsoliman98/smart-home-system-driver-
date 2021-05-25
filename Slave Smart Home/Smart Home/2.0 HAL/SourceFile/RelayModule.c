/*
 * RelayModule.c
 *
 * Created: 7/14/2020 4:36:20 PM
 *  Author: ahmedsoliman
 */ 

   #include <ATmega32A_Config.h>
   #include <ATmega32A_DIO_Config.h>
   #include <StandardDataType.h>
   #include <RelayModule.h>
   
 /*
  *
  * @brief <Led_ErrorIndication>
  *
  * <this function is to indicate that there is be an error arrgument that not define as a led state>
  *
  * @const Errortype  <enum>       <Should Pass a type of error  >
  *
  *
  * @return < void>
  */
   static void errorIndication(Errortype type)
   {
	 /* 
	  * switch  <Errortype>
	  *
	  *case invalidArgument
	  *
	  */
	   switch (type)
	   {
		   case invalidArgument :
		   default:
		   break;
	   }
   }
   
   
   
   
  void Relay_SETUP (Relay_dataType relay)
  {
	  // if the relay is reversed NO and NC that mean it operate a micro sec then stop because the initial condition of Output is 0 
	  DIO_pinConfiguration(relay.signalPort, relay.signalPin, Output); 
	  /* represent The Relay Intial Value */ 
	  DIO_pinWrite(relay.signalPort, relay.signalPin, relay.intialeValue);
  }
  
  
  
  
  void Relay_Operate(Relay_dataType relay, RELAY_STATE signal)
  {
	  /* 
	  * switch  <RELAY_STATE>
	  *
	  *case <standardNO, RevNC>     <in this two case is the different in the connection of the Relay with the Mc but it the same in the Mc deal with in the 2 case it output LOW>
	  *case <standardNC, RevNO>     <in this two case is the different in the connection of the Relay with the Mc but it the same in the Mc deal with in the 2 case it output HIGH>
	  *case <invalidArrgument>      <in this case the Mc can not define the state send to him so it print an error massege >
	  *
	  */
	  switch (signal)
	  {
		  case HIGH :
		  case LOW  :
		       DIO_pinWrite(relay.signalPort, relay.signalPin, signal);
		       break; 
		  default: 
		       errorIndication(invalidArgument);  
			   break;
	  }	
  }

