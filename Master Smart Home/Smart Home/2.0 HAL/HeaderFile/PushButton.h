/*
 *
 * @file <PushButtom.h>
 * @brief <This is a Header File for the Push Buttom Which Eanbles User to Control Push Bottom state>
 *
 * @APIS
 *					  PIR_setup()		< Setup PIR sensor port and pin via MCAL >
 *						returns     void 
 *						Takes	  PIR_dataType
 *					  PIR_operate()		<this function to read the sensor detction state>
 *                      return      void
 *                       Takes      PIR_dataType             ,     PIR_detection
 * 	
 * @authors <ahmedsoliman>
 * @date <7/15/2020 12:02:04 PM>
 *
 */


#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_

#define Push_Bouncing_Periode_mS (50)

     typedef enum
     {
	     PUSH_NOT_PRESSED,
	     PUSH_PRESSED,
	     PUSH_RELEASED,
     }PUSH_States;
     
	 
	 /*
	 *
	 * @brief <PushButtom>
	 *		  GPIO *		IO_PORT < Should assign Port Address to it >
	 *        pinNumber     IO_PIN  <should assign pin Address to it >
	 *        pinMode       InputMode < should assign Input Mode AS OutPut Or Input >
	 *        DigitalValue  PREV_Level < should assign th Previous State Of The Pin >
	 */     
     typedef struct
     {
	     GPIO * IO_PORT;
	     pinNumber IO_PIN;
	     pinMode  InputMode;
	     DigitalValue  PREV_Level;
     }PushButton_datatype;
	 
	 
	 
	 /*
	 *
	 * @brief <PushButton_Setup>
	 *
	 * <this function is to setup Push Button with the microcontroller to be able to define it port and pin and it is input or output>
	 *
	 * @const PushButtom_datatype  <struct>       <Should Pass a predefined PushButtom_datatype Variable which has the Internal Values Filled >
	 *
	 *
	 * @return < void>
	 */

     void PushButton_setup(PushButton_datatype *Pswitch);
	 
	 
	 /*
	 *
	 * @brief <PushButton_read>
	 *
	 * <this function is  to read it is state>
	 *
	 * @const PushButtom_datatype  <struct>       <Should Pass a predefined PushButtom_datatype Variable which has the Internal Values Filled >
	 *
	 *
	 * @return < PUSH_States>
	 */
     PUSH_States PushButton_read(PushButton_datatype *Pswitch);


#endif /* PUSHBUTTON_H_ */