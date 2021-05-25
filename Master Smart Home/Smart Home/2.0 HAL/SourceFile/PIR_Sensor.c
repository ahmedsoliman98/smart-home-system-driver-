/*
 * PIR_sensor.c
 *
 * Created: 7/15/2020 12:02:20 PM
 *  Author: ahmedsoliman
 */ 

 #include <ATmega32A_Config.h>
 #include <ATmega32A_DIO_Config.h>
 #include <StandardDataType.h>
 #include <PIR_sensor.h>
 
 
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
 
 void ErrorIndication(Errortype type)
 {
	  /* 
	  * switch  <Errortype>
	  *
	  *case invalidArgument
	  *
	  */
	 switch (type)
	 {
		 case invalidArgument:
		      break;
		default:
		       break;
	 }
 }
 
 
 
 void PIR_setup(PIR_dataType PIR)
 {
	 /* Configuration The Pin Of The Sensor As an Input Float  Pin So It default Is LOW */
	 DIO_pinConfiguration(PIR.PIRport, PIR.PIRpin, InputFloat);
 }
 
 
 
 DigitalValue PIR_operate (PIR_dataType PIR)
 {
	 /* read The Pin State Refer To The Condition Of The sensor If It Indicate Will return High Else Will Return Low */
	 return ( DIO_pinRead(PIR.PIRport, PIR.PIRpin) );	
 }
 