/*
 *
 * @file <PIR_sensor.h>
 * @brief <This is a Header File for the PIR sensor Which Eanbles User to Control an PIR sensor state>
 *
 * There are a different type in the IR sensor it was a sensor used the light signal to detect obstacle 
 * the different between IR and PIR sensor that the IR sensor has a Tx and Rx so it send signal and wait it reflection to decide there was an obstacle or not 
 * the PIR sensor it only has a Rx it detect the radiation of the body like human body then it decide if there was an obstacle or not 
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


#ifndef PIR_SENSOR_H_
#define PIR_SENSOR_H_



 typedef enum
  {
	 PIR_detect = HIGH, 
	 PIR_notdetect = LOW,
  }PIR_detection;
  
    /*
	 *
	 * @brief <Led_datatype>
	 *		  GPIO *		PIRport < Should assign Port Address to it >
	 *        pinNumber     PIRpin  <should assign pin Address to it >
	 */ 
  
  typedef struct
  {
	 GPIO * PIRport;
	 pinNumber PIRpin; 
  }PIR_dataType;
  
    /*
	 *
	 * @brief <PIR_setup>
	 *
	 * <this function is to setup the PIR sensor PORT and PIN and to define to the Mc that this pin is input>
	 *
	 * @const PIR_dataType  <struct>       <Should Pass a predefined PIR_dataType Variable which has the Internal Values Filled >
	 *
	 *
	 * @return < void>
	 */
  
  void PIR_setup(PIR_dataType PIR);
  
   /*
	 *
	 * @brief <PIR_operate>
	 *
	 * <this function is to read the sensor state and re>
	 *
	 * @const PIR_dataType  <struct>       <Should Pass a predefined PIR_dataType Variable which has the Internal Values Filled >
	 *
	 *
	 * @return < void>
	 */
  DigitalValue PIR_operate (PIR_dataType PIR);
 




#endif /* PIR_SENSOR_H_ */