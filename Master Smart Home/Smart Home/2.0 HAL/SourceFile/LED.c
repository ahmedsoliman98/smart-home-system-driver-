/*
 * LED.c
 *
 * Created: 7/14/2020 2:36:00 PM
 *  Author: ahmedsoliman
 */ 


  #include <ATmega32A_Config.h>
  #include <ATmega32A_DIO_Config.h>
  #include <StandardDataType.h>
  #include <LED.h>
  
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
  static void Led_ErrorIndicatio (Errortype error)
  {
	 /* 
	  * switch  <Errortype>
	  *
	  *case invalidArgument
	  *
	  */
	  switch (error)
	  {
		  case invalidArgument :
		  default:
		  break;
	  }		  
  }
  
  
  
  void Led_Setup (Led_dataType Led)
  {
	  /* configure The LED pin As An Output Pin */
	  DIO_pinConfiguration(Led.ledPort, Led.ledPin, Output);
	  /* represent The Initial State Of The LED to Make Portability If The User Connect It Fw / Rv */ 
	  DIO_pinWrite(Led.ledPort, Led.ledPin, Led.ledIntialValue);
  }
  void Led_operation(Led_dataType led, Led_StateType State)
  {
	 /* 
	  * switch  <Led_StateType>
	  *
	  *case <FW_OFF, Rev_ON>     <in this two case is the different in the connection of the LED with the Mc but it the same in the Mc deal with in the 2 case it output LOW>
	  *case <FW_ON, Rev_OFF>     <in this two case is the different in the connection of the LED with the Mc but it the same in the Mc deal with in the 2 case it output HIGH>
	  *case <Led_TOGGLE>         < in this case the led is toggling it is state so it read it intial state and toggle it >
	  *case <invalidArrgument>  < in this case the Mc can not define the state send to him so it print an error massege >
	  *
	  */
	  switch(State)
	  {
		  
	  
	     case HIGH :
	     case LOW  :
	   
	          DIO_pinWrite(led.ledPort, led.ledPin, State);
	          break;
	     case Led_TOGGLE :
		 /* Here We Toggle The State Of The Pin */
	          DIO_pinWrite(led.ledPort, led.ledPin, !DIO_pinRead(led.ledPort, led.ledPin));
	     default : Led_ErrorIndicatio(invalidArgument);
		       break;
	  }	
  }