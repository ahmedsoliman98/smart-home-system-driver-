/*
 *
 * @file <RelayModule.h>
 * @brief <This is a Header File for the relay module Which Eanbles User to Control the state of the relay>
 *
 * @APIS
 *					  Relay_SETUP()		< Setup relay module port and pin via MCAL >
 *						returns     void 
 *						Takes	  Relay_dataType
 *					  Relay_Operate()		<this function to operat the relay function depend on the state send>
 *                      return      void
 *                       Takes      Relay_dataType             ,     RELAY_STATE
 * 	
 * @authors <ahmedsoliman>
 * @date&time <7/14/2020 4:36:57 PM>
 *
 */


#ifndef RELAYMODULE_H_
#define RELAYMODULE_H_



 typedef enum
  {
	  standardNO = LOW,
	  standardNC = HIGH,
	    RevNO    = HIGH,
		RevNC    = LOW,
  }RELAY_STATE;
  
    /*
	 *
	 * @brief <Relay_dataType>
	 *		  GPIO *		signalPort < Should assign Port Address to it >
	 *        pinNumber     signalPin  <should assign pin Address to it >
     *        RELAY_STATE   intialValue <should assign the intial value of the relay>
	 */
  
   typedef struct
   {
	   GPIO * signalPort;
	   pinNumber signalPin;
	   RELAY_STATE intialeValue;
   }Relay_dataType;
   
    /*
	 *
	 * @brief <Relay_SETUP>
	 *
	 * <this function is to setup the Relay Module PORT and PIN and to define to the Mc that this pin is OUTPUT>
	 *
	 * @const Relay_dataType  <struct>       <Should Pass a predefined Relay_dataType Variable which has the Internal Values Filled >
	 *
	 *
	 * @return < void>
	 */
  void Relay_SETUP (Relay_dataType relay);
  
   /*
	 *
	 * @brief <Relay_Operate>
	 *
	 * <this function is to operat the relay function as a switch depend on the state send from user>
	 *
	 * @const Relay_dataType  <struct>       <Should Pass a predefined Relay_dataType Variable which has the Internal Values Filled >
	 *        RELAY_STATE signal <enum>       < should pass the state of the signal send to the relay module>
	 *
	 * @return < void>
	 */
  void Relay_Operate(Relay_dataType relay, RELAY_STATE signal);


#endif /* RELAYMODULE_H_ */