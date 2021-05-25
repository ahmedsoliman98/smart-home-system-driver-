/*
 *
 * @file <LED.h>
 * @brief <This is a Header File for the LED Driver Which Eanbles User to Control an LED state>
 *
 * @APIS
 *					  led_Setup()		< Setup Led port and pin via MCAL >
 *						returns   void 
 *						Takes	  Led_datatype 
 *					  led_operation()	 <allow the user to control the led state>	
 *                      returns   void
 *                      Takes                 Led_datatype            ,     Led_StateType
 * 	
 * @authors <ahmedsoliman>
 * @date <7/14/2020 2:35:48 PM>
 *
 */




#ifndef LED_H_
#define LED_H_

  #define Toggle (3)
  
   typedef enum
   {
	   Led_FW_OFF = LOW,
	   Led_FW_ON = HIGH,
	   Led_RV_OFF = HIGH,
	   Led_RV_ON = LOW,
	   Led_TOGGLE = Toggle
   }Led_StateType;

    /*
	 *
	 * @brief <Led_datatype>
	 *		  GPIO *		LedPort < Should assign Port Address to it >
	 *        pinNumber     ledPin  <should assign pin Address to it >
	 *        Led_StateType  ledIntialValue < shouid assign intial value to it
	 */       
	
   typedef struct 
   {
	   GPIO * ledPort;
	   pinNumber ledPin;
	   Led_StateType ledIntialValue;
   }Led_dataType;
   
   /* Function Prototype */
	
	
	/*
	 *
	 * @brief <Led_Setup>
	 *
	 * <this function is to setup led with the microcontroller to be able to define it port and pin and it is input or output>
	 *
	 * @const Led_datatype  <struct>       <Should Pass a predefined LedDatatype Variable which has the Internal Values Filled >
	 *
	 *
	 * @return < void>
	 */
  

  void Led_Setup (Led_dataType led);
  
    /*
     *
	 * @brief <Led_operation>
	 *
	 * <this function to operate the led by it is state to make it turn ON / OFF>
	 *
	 * @const Led_datatype  <struct>       <Should Pass a predefined LedDatatype Variable which has the Internal Values Filled >
	 *        Ledd_StateType <enum>        < should pass a state of the led>
	 *
	 * @return < void>
	 */
  void Led_operation(Led_dataType led, Led_StateType State);




#endif /* LED_H_ */