/*
 *
 * @file <BUZZER.h>
 * @brief <This is a Header File for the buzzer ehich enable the user to control the buzzer state>
 *
 * @APIS
 *					  BUZZER_setup()		< Setup BUZZER Port and Pin via MCAL >
 *						returns   void 
 *						Takes	  BUZZER_dataType
 *					  BUZZER_operate()		<this function is resboncible to operate the buzzer in alarm condition >
 *                      return  void
 *                      Takes              BUZZER_dataType     
 *
 * @authors <ahmedsoliman>
 * @date <7/18/2020 3:56:23 PM>
 *
 */


#ifndef BUZZER_H_
#define BUZZER_H_


 /*
  *
  * @brief <BUZZER_datatype>
  *		  GPIO *		buzzerPORT < Should assign Port Address to it >
  *        pinNumber     buzzerPIN  <should assign pin Address to it >
  *       
  */       
  typedef struct
  {
	  GPIO * buzzerPORT;
	  pinNumber buzzerPIN;
  }BUZZER_dataType;
  
  
  	/*
	 *
	 * @brief <BUZZER_Setup>
	 *
	 * <this function is to setup BUZZER with the microcontroller to be able to define it port and pin and it is input or output>
	 *
	 * @const BUZZER_datatype  <struct>       <Should Pass a predefined BUZZER_dataType Variable which has the Internal Values Filled >
	 *
	 *
	 * @return < void>
	 */
  
  void BUZZER_Setup (BUZZER_dataType buz);
  
    /*
	 *
	 * @brief <BUZZER_ALARM>
	 *
	 * <this function is to operate the buzzer like alarm sound>
	 *
	 * @const BUZZER_datatype  <struct>       <Should Pass a predefined LedDatatype Variable which has the Internal Values Filled >
	 *
	 *
	 * @return < void>
	 */
  void BUZZER_ALARM(BUZZER_dataType buz);
  





#endif /* BUZZER_H_ */